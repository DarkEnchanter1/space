#include "renderer.hpp"
using namespace render;


// Include standard headers
#include <stdio.h>
#include <cstring>
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
#include "rendering/utils/text2D.hpp"
#include "common/controls.hpp"
#include "common/objloader.hpp"


#define RESET   "\033[0m"
#define BLACK   0      /* Black */
#define RED     1      /* Red */
#define GREEN   2      /* Green */
#define YELLOW  3      /* Yellow */
#define BLUE    4      /* Blue */
#define MAGENTA 5      /* Magenta */
#define CYAN    6      /* Cyan */
#define WHITE   7      /* White */
const char* colorTable[] = {"\033[30m", "\033[31m", "\033[32m", "\033[33m", "\033[34m", "\033[35m", "\033[36m", "\033[37m"};
void printColor (unsigned int clr, const char* string) {
	std::cerr << colorTable[clr] << string << RESET;
}

void printCondition (int level, const char* string) {
	if (level == GL_DEBUG_SEVERITY_HIGH_ARB) 
		printColor(RED, string);
	else if (level == GL_DEBUG_SEVERITY_MEDIUM_ARB)
		printColor(YELLOW, string);
	else if (level == GL_DEBUG_SEVERITY_LOW_ARB)
		std::cout << string;
	else
		printColor(CYAN, string);
}

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
	window = glfwCreateWindow( 1024, 768, "Space Game", NULL, NULL);
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
void openGlSetup(GLuint* VertexArrayID, GLuint* programID, GLuint* MatrixID, GLuint* ModelID, GLuint* ViewMatrixID, GLuint* ModelMatrixID, GLuint* LightID) {	// Dark blue background
	glClearColor(0.3f, 0.3f, 0.7f, 1.0f);
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
	(*ModelID) = glGetUniformLocation(*programID, "ModelPos");
	//(*ViewMatrixID) = glGetUniformLocation(*programID, "V");
	//(*ModelMatrixID) = glGetUniformLocation(*programID, "M");
	//(*LightID) = glGetUniformLocation(*programID, "LightPosition_worldspace");
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
	std::cout << '\r' << string << std::flush;
}
void clearAndPrint(std::string string) {
	std::cout << '\r';
	for (int i = 0; i < width; i++)
		std::cout << '_';
	std::cout << '\r' << string << std::flush;
}
void RenderEngine::sendBufferData() {
	physics->sendAllModels();
	dataHasUpdated = false;
	std::cout << "Resent Buffer Data" << std::endl;
}
uint vallength = 5;
void RenderEngine::loop() {
	double lastTime = glfwGetTime();
 	int nbFrames = 0;
	int framerate = 0;
	glfwSwapInterval(0);
	sendBufferData();
	do {
		if (dataHasUpdated)
			sendBufferData();
		render(&lastTime, &nbFrames, &framerate);
	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS);
	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteProgram(programID);
	glDeleteTextures(1, &Texture);
	glDeleteVertexArrays(1, &VertexArrayID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();
}

void APIENTRY DebugOutputCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam){
	if(severity == GL_DEBUG_SEVERITY_HIGH_ARB)              printCondition(severity, "SERIOUS ");
	else if(severity == GL_DEBUG_SEVERITY_MEDIUM_ARB)       printCondition(severity, "Dangerous ");
	else if(severity == GL_DEBUG_SEVERITY_LOW_ARB)          printCondition(severity, "Moderate ");
	else                                                    printCondition(severity, "Unknown ");
	printCondition(severity, "OpenGL ");
	if(type == GL_DEBUG_TYPE_ERROR_ARB)                     printCondition(severity, "Error ");
	else if(type == GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB)  printCondition(severity, "Deprecated Behavior Warning ");
	else if(type == GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB)   printCondition(severity, "Undefined Behavior Warning ");
	else if(type == GL_DEBUG_TYPE_PORTABILITY_ARB)          printCondition(severity, "Unportable Functionality Warning ");
	else if(type == GL_DEBUG_TYPE_PERFORMANCE_ARB)          printCondition(severity, "Impl-dependent Performance Warning ");
	else if(type == GL_DEBUG_TYPE_OTHER_ARB)                printCondition(severity, "Warning ");
	else                                                    printCondition(severity, "Non-Standard-Compliant Error ");
	printCondition(severity, "from ");
	if(source == GL_DEBUG_SOURCE_API_ARB)                   printCondition(severity, "the API: ");
	else if(source == GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB)    printCondition(severity, "the Window System: ");
	else if(source == GL_DEBUG_SOURCE_SHADER_COMPILER_ARB)  printCondition(severity, "the Shader Compiler: ");
	else if(source == GL_DEBUG_SOURCE_THIRD_PARTY_ARB)      printCondition(severity, "a Third Party: ");
	else if(source == GL_DEBUG_SOURCE_APPLICATION_ARB)      printCondition(severity, "the Application: ");
	else if(source == GL_DEBUG_SOURCE_OTHER_ARB)            printCondition(severity, "something unknown: ");
	else                                                    printCondition(severity, "a Non-Standard-Compliant Source: ");
	printCondition(severity, message);
	if (message[strlen(message) - 1] != '\n') printCondition(severity, "\n\n");
	else printCondition(severity, "\n");
}

RenderEngine::RenderEngine()
{
	
	get_size(STDOUT_FILENO, &height, &width);
	vallength = width / 32;
	initGLFW();
	initGLEW();
	initText2D("resources/textures/noto_sans_black_128.DDS", "resources/textures/noto_sans_black_128.json");
	setInputMode();
	openGlSetup(&VertexArrayID, &programID, &MatrixID, &ModelID, &ViewMatrixID, &ModelMatrixID, &LightID);

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
	Texture = loadDDS("resources/textures/concrete.DDS");
	lightPos = glm::vec3(0,0,0);
	// Get a handle for our "myTextureSampler" uniform
	TextureID  = glGetUniformLocation(programID, "tSampler");
	if ( GLEW_ARB_debug_output ){
		printColor(GREEN, "OpenGL Debug Callback is supported. Enabling advanced callback\n");
		glDebugMessageCallbackARB(&DebugOutputCallback, NULL);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB); 
	}else{
		printColor(YELLOW, "OpenGL Debug Callback not supported. Errors may be lost\n");
	}
	glGenBuffers(1, &vertexbuffer);
	glGenBuffers(1, &uvbuffer);
	//glGenBuffers(1, &normalbuffer);

}
RenderEngine::~RenderEngine() {
	// Close OpenGL window and terminate GLFW
	glfwTerminate();
}

void renderGui(int fps) {
	int w = 0;
	int h = 0;
	glfwGetWindowSize(window, &w, &h);
	printText2D(std::to_string(fps).c_str(), 0, h - 200, 16);
}


int RenderEngine::render(double* lastTime, int* nbFrames, int* framerate) {
	 // Measure speed
     double currentTime = glfwGetTime();
     (*nbFrames)++;
     if ( currentTime - *lastTime >= 1.0 ){ // If last prinf() was more than 1 sec ago
         // printf and reset timer
         printf("%f ms/frame\n", 1000.0/double(*nbFrames));
		 *framerate = *nbFrames;
         *nbFrames = 0;
         *lastTime += 1.0;
     }
	// Handles controls and view refactor
	computeMatricesFromInputs(window);
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS); 
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Use our shader
	glUseProgram(programID);
	
	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform
	glm::mat4 Model = glm::mat4(1.0f);
	glm::mat4 View = getViewMatrix();
	glm::mat4 Projection = getProjectionMatrix();
	MVP = Projection * View * Model;
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(ModelID, 1, GL_FALSE, &Model[0][0]);
	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	
		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture);
		// Set our "myTextureSampler" sampler to use Texture Unit 0
		glUniform1i(TextureID, 0);

		if (physics != 0) {
		std::lock_guard<std::mutex> lock(physics->objs_mutex);
		for (auto object : physics->objs) 
			object->render(ModelID);
		}
	// glEnableVertexAttribArray(0);
	// glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// //glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * triangles.size(), &triangles[0], GL_STATIC_DRAW);
	// glVertexAttribPointer(
	// 	0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
	// 	4,                  // size
	// 	GL_FLOAT,           // type
	// 	GL_FALSE,           // normalized?
	// 	0,                  // stride
	// 	(void*)0            // array buffer offset
	// );
	// glEnableVertexAttribArray(1);
	// glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	// //glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * uvdata.size(), &uvdata[0], GL_STATIC_DRAW);	
	// glVertexAttribPointer(
	// 	1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
	// 	2,                                // size
	// 	GL_FLOAT,                         // type
	// 	GL_FALSE,                         // normalized?
	// 	0,                                // stride
	// 	(void*)0                          // array buffer offset
	// );
	// // Draw the triangle !
	// glDrawArrays(GL_TRIANGLES, 0, triangles.size()); // Dynamic triangle count.
		// Swap buffers

	// Enable depth test
		glDisable(GL_DEPTH_TEST);
		renderGui(*framerate);
		glfwSwapBuffers(window);
		glfwPollEvents();
	glDisableVertexAttribArray(0);
	//glDisableVertexAttribArray(1);
	return 0;
};
Model::Model(const char* modelid) {
	std::vector<unsigned short> indices; //TODO: Support indices
	std::cout << "Adding model!" << std::endl;
	loadAssImp(modelid, indices, triangles, uvdata, normals);
}
