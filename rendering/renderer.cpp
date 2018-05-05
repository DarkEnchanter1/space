#include "renderer.hpp"
using namespace render;


// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <iomanip>
#include <memory>
#include <chrono>
#include <thread>
#include <sstream>
// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Include local files
#include "rendering/utils/shader.hpp"
#include "rendering/utils/texture.hpp"
#include "common/controls.hpp"
void setWindowHints() {
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}
void increaseWindowPos(int x, int y) {
	int xpos, ypos;
	glfwGetWindowPos(window, &xpos, &ypos);
	glfwSetWindowPos(window, xpos + x, ypos + y);
}
int initGLFW() {
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		return -1;
	}
	setWindowHints();
	// Open a window and create its OpenGL context
	window = glfwCreateWindow( 1024, 768, "Tutorial 05 - Textured Cube", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		glfwTerminate();
		return -1;
	}
	increaseWindowPos(20, 20);
	glfwMakeContextCurrent(window);
	return 0;
}
int initGLEW() {
	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}
	return 0;
}
void setInputMode() {
	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	// Hide the mouse cursor
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}
void openGlSetup(GLuint* VertexArrayID, GLuint* programID, GLuint* MatrixID, GLuint* ViewMatrixID, GLuint* ModelMatrixID, GLuint* LightID) {	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS); 

	glGenVertexArrays(1, VertexArrayID);
	glBindVertexArray(*VertexArrayID);
		// Create and compile our GLSL program from the shaders
	(*programID) = LoadShaders( "resources/vertexshader.vs", "resources/fragshader.fs" );

	// Get a handle for our "MVP" uniform
	(*MatrixID) = glGetUniformLocation(*programID, "MVP");
	(*ViewMatrixID) = glGetUniformLocation(*programID, "V");
	(*ModelMatrixID) = glGetUniformLocation(*programID, "M");
	(*LightID) = glGetUniformLocation(*programID, "LightPosition_worldspace");
}
static int get_size(const int fd, int *const rows, int *const cols) {
	struct winsize sz;

	int result;

	do {
		result = ioctl(fd, TIOCGWINSZ, &sz);
	} while (result == -1 && errno == EINTR);
	if (result == -1)
		return errno;

	if (rows)
		*rows = sz.ws_row;

	if (cols)
		*cols = sz.ws_col;

	return 0;
}

int width;
int height;

void clearAndPrint(const char* string) {
	std::cout << '\r';
	for (int i = 0; i < width; i++)
		std::cout << ' ';
	std::cout << '\r' << string;
	fflush(stdout);
}
void clearAndPrint(std::string string) {
	std::cout << '\r';
	for (int i = 0; i < width; i++)
		std::cout << ' ';
	std::cout << '\r' << string;
	fflush(stdout);
}
RenderEngine::RenderEngine()
{
	initGLFW();
	initGLEW();
	setInputMode();
	openGlSetup(&VertexArrayID, &programID, &MatrixID, &ViewMatrixID, &ModelMatrixID, &LightID);

	// Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	// Camera matrix
	glm::mat4 View       = glm::lookAt(
								glm::vec3(12,6,6), // Camera is at (12,6,6), in World Space
								glm::vec3(0,0,0), // and looks at the origin
								glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
						   );
	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model      = glm::mat4(1.0f);
	// Our ModelViewProjection : multiplication of our 3 matrices
	MVP        = Projection * View * Model; // Remember, matrix multiplication is the other way around
	// Load the texture using any two methods
	//GLuint Texture = loadBMP_custom("uvtemplate.bmp");
	Texture = loadDDS("resources/textures/concrete.DDS");
	lightPos = glm::vec3(0,0,0);
	// Get a handle for our "myTextureSampler" uniform
	TextureID  = glGetUniformLocation(programID, "myTextureSampler");
}
RenderEngine::~RenderEngine() {
	// Cleanup VBO and shader
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &VertexArrayID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();
}


int RenderEngine::render() {		// Handles controls and view refactor
		computeMatricesFromInputs(window);
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(programID);
		
		//Recalculate view
			glm::mat4 Projection = getProjectionMatrix();
			// Camera matrix
			glm::mat4 View       = getViewMatrix();
			// Model matrix : an identity matrix (model will be at the origin)
			glm::mat4 Model      = glm::mat4(1.0f);
			// Our ModelViewProjection : multiplication of our 3 matrices
			MVP        = Projection * View * Model; // Remember, matrix multiplication is the other way around
		
		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &Model[0][0]);
		glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &View[0][0]);
		glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);

		// Cull triangles which normal is not towards the camera
		glEnable(GL_CULL_FACE);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture);
		// Set our "myTextureSampler" sampler to use Texture Unit 0
		glUniform1i(TextureID, 0);

	glm::mat4 tMat = glm::translate(glm::mat4(), glm::vec3(0, 0, 0));
	glm::mat4 rMat = glm::rotate((float)0, glm::vec3(0, 0, 1)) * glm::rotate((float)0, glm::vec3(0, 1, 0)) * glm::rotate((float)0, glm::vec3(1, 0, 0));
	glm::mat4 mat = tMat * rMat;
	//Loading buffer data for vertexes into GPU
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	//Same for UV data (texture mapping)
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	//...and for normal maps
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(
		1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);
	 // 3rd attribute buffer : normals
 	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glVertexAttribPointer(
    	 2,                                // attribute
	     3,                                // size
    	 GL_FLOAT,                         // type
	     GL_FALSE,                         // normalized?
	     0,                                // stride
	     (void*)0                          // array buffer offset
	 );
	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, triangles.size() * 3); // 12*3 indices starting at 0 -> 12 triangles
	GLenum err = glGetError();
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	return 0;
};
Model::Model(const char* modelid) {
	
}