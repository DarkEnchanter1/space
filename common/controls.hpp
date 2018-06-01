#ifndef CONTROLS_HPP
#define CONTROLS_HPP

void computeMatricesFromInputs(GLFWwindow* window, bool* menu);
glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();

#endif