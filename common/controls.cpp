// Include GLFW
#include <GLFW/glfw3.h>
extern GLFWwindow *window; // The "extern" keyword here is to access the variable "window" declared in tutorialXXX.cpp. This is a hack to keep the tutorials simple. Please avoid this.

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "controls.hpp"
#include <iostream>

glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;

glm::mat4 getViewMatrix()
{
	return ViewMatrix;
}
glm::mat4 getProjectionMatrix()
{
	return ProjectionMatrix;
}
//Defines the rotation to apply to left/right translations.
//Super long to allow for maximum accuracy... after all, it only needs precision up to 2^3!
const float rot90 = 1.570796326794896619231321691639751442098584699687552910487f;

// Initial position : on +Z
glm::vec3 position = glm::vec3(4, 2, 5);
// Initial horizontal angle : toward -Z
float horizontalAngle = -2.34751f;
// Initial vertical angle : none
float verticalAngle = 0.0f;
// Initial Field of View
float initialFoV = 45.0f;

float speed = 3.0f; // 3 units / second
float mouseSpeed = 0.005f;

bool firstTime = true;
bool firstPress = true;
void computeMatricesFromInputs(GLFWwindow *window, bool* menuMode)
{
	if (horizontalAngle > 6.28318)
		horizontalAngle -= 6.28318;
	if (horizontalAngle < 0)
		horizontalAngle += 6.28318;
	// glfwGetTime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	// Get mouse position
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	// Reset mouse position for next frame
	if (!*menuMode)
	{
		glfwSetCursorPos(window, 1024 / 2, 768 / 2);
		if (!firstTime)
		{
			// Compute new orientation
			horizontalAngle += mouseSpeed * float(1024 / 2 - xpos) / 2;
			float tvert = verticalAngle + (mouseSpeed * float(768 / 2 - ypos) / 2);
			if (tvert > -1.57079 && tvert < 1.57079)
				verticalAngle = tvert;
		}
		else
			firstTime = false;
	}
	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle));

	// Right vector
	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f / 2.0f),
		0,
		cos(horizontalAngle - 3.14f / 2.0f));

	// Up vector
	glm::vec3 up = glm::cross(right, direction);
	if (!*menuMode)
	{
		float modSpeed = speed;
		if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
		{
			modSpeed /= 4;
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		{
			modSpeed *= 4;
		}
		// Move forward
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			position += /*direction*/ glm::vec3(sin(horizontalAngle), 0, cos(horizontalAngle)) * deltaTime * modSpeed;
		}
		// Move backward
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			position -= /*direction*/ glm::vec3(sin(horizontalAngle), 0, cos(horizontalAngle)) * deltaTime * modSpeed;
		}
		// Strafe right
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			position -= /*direction*/ glm::vec3(sin(horizontalAngle + rot90), 0, cos(horizontalAngle + rot90)) * deltaTime * modSpeed;
		}
		// Strafe left
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			position += /*direction*/ glm::vec3(sin(horizontalAngle + rot90), 0, cos(horizontalAngle + rot90)) * deltaTime * modSpeed;
		}
		// Fly up
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			position += /*direction*/ glm::vec3(0, 1, 0) * deltaTime * modSpeed;
		}
		// Fly down
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			position -= /*direction*/ glm::vec3(0, 1, 0) * deltaTime * modSpeed;
		}
	}
	// Open a 'menu'
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		if (firstPress)
		{
			if (*menuMode)
			{
				glfwSetCursorPos(window, 1024 / 2, 768 / 2);
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			}
			else
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			*menuMode = !*menuMode;
			firstPress = false;
		}
	}
	else
		firstPress = true;

	float FoV = initialFoV; // - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.

	// Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	ProjectionMatrix = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 300.0f);
	// Camera matrix
	ViewMatrix = glm::lookAt(
		position,			  // Camera is here
		position + direction, // and looks here : at the same position, plus "direction"
		up					  // Head is up (set to 0,-1,0 to look upside-down)
	);

	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;
}
