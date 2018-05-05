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
#include "common/objloader.hpp"
void setWindowHints() {
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1); 
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
void RenderEngine::loop() {
	do {
		render();
	} while (glfwGetKey(window, GLFW_KEY_R) != GLFW_PRESS);
}
// The ARB_debug_output extension, which is used in this tutorial as an example,
// can call a function of ours with error messages.
// This function must have this precise prototype ( parameters and return value )
// See http://www.opengl.org/registry/specs/ARB/debug_output.txt , "New Types" : 
//	The callback function that applications can define, and
//	is accepted by DebugMessageCallbackARB, is defined as:
//	
//	    typedef void (APIENTRY *DEBUGPROCARB)(enum source,
//	                                          enum type,
//	                                          uint id,
//	                                          enum severity,
//	                                          sizei length,
//	                                          const char* message,
//	                                          void* userParam);
void APIENTRY DebugOutputCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam){

	printf("OGL ERROR : ");

	if(source == GL_DEBUG_SOURCE_API_ARB)					printf("SRC : API; ");
	else if(source == GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB)	printf("SRC : WINDOW_SYSTEM; ");
	else if(source == GL_DEBUG_SOURCE_SHADER_COMPILER_ARB)	printf("SRC : SHADER_COMPILER; ");
	else if(source == GL_DEBUG_SOURCE_THIRD_PARTY_ARB)		printf("SRC : THIRD_PARTY; ");
	else if(source == GL_DEBUG_SOURCE_APPLICATION_ARB)		printf("SRC : APPLICATION; ");
	else if(source == GL_DEBUG_SOURCE_OTHER_ARB)			printf("SRC : OTHER; ");

	if(type == GL_DEBUG_TYPE_ERROR_ARB)						printf("T : ERROR; ");
	else if(type == GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB)	printf("T : DEPRECATED_BEHAVIOR; ");
	else if(type == GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB)	printf("T : UNDEFINED_BEHAVIOR; ");
	else if(type == GL_DEBUG_TYPE_PORTABILITY_ARB)			printf("T : PORTABILITY; ");
	else if(type == GL_DEBUG_TYPE_PERFORMANCE_ARB)			printf("T : PERFORMANCE; ");
	else if(type == GL_DEBUG_TYPE_OTHER_ARB)				printf("T : OTHER; ");

	if(severity == GL_DEBUG_SEVERITY_HIGH_ARB)				printf("Sev : HIGH; ");
	else if(severity == GL_DEBUG_SEVERITY_MEDIUM_ARB)		printf("Sev : MEDIUM; ");
	else if(severity == GL_DEBUG_SEVERITY_LOW_ARB)			printf("Sev : LOW; ");

	// You can set a breakpoint here ! Your debugger will stop the program,
	// and the callstack will immediately show you the offending call.
	printf("Message : %s\n", message);
}

RenderEngine::RenderEngine()
{
	initGLFW();
	initGLEW();
	setInputMode();
	openGlSetup(&VertexArrayID, &programID, &MatrixID, &ViewMatrixID, &ModelMatrixID, &LightID);

	// Projection matrix : 45 degree Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
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
	if ( GLEW_ARB_debug_output ){
		printf("The OpenGL implementation provides debug output. Let's use it !\n");
		glDebugMessageCallbackARB(&DebugOutputCallback, NULL);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB); 
	}else{
		printf("ARB_debug_output unavailable. You have to use glGetError() and/or gDebugger to catch mistakes.\n");
	}
	glGenBuffers(1, &vertexbuffer);
	glGenBuffers(1, &uvbuffer);
	glGenBuffers(1, &normalbuffer);

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

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, triangles.size() * 3, &triangles, GL_STATIC_DRAW);
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
	glBufferData(GL_ARRAY_BUFFER, uvdata.size() * 2, &uvdata, GL_STATIC_DRAW);	
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
	glBufferData(GL_ARRAY_BUFFER, normals.size() * 3, &normals, GL_STATIC_DRAW);	
	glVertexAttribPointer(
    	 2,                                // attribute
	     3,                                // size
    	 GL_FLOAT,                         // type
	     GL_FALSE,                         // normalized?
	     0,                                // stride
	     (void*)0                          // array buffer offset
	 );
	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, triangles.size()); // 12*3 indices starting at 0 -> 12 triangles
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	return 0;
};
Model::Model(const char* modelid) {
	std::vector<unsigned short> indices; //TODO: Support indices
	std::cout << "Adding model!" << std::endl;
	loadAssImp(modelid, indices, triangles, uvdata, normals);
}