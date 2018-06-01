#ifndef RENDERER_HPP
#define RENDERER_HPP
#include <vector>
#include <string>
#include <iostream>
#include "common/primitives.hpp"
#include "common/delta.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <GL/glew.h>
#include <glm/glm.hpp>
namespace render {
	class RenderEngine; //Fuck C++
	struct Model {
		Model(const char* modelid);
		std::vector<glm::vec4> triangles;
		std::vector<glm::vec2>   uvdata;
		std::vector<glm::vec4>  normals;
	};
}
#include "physics.hpp"

class render::RenderEngine {
	GLuint Texture;
	GLuint TextureID;
	GLuint VertexArrayID;
	GLuint programID;
	GLuint MatrixID;
	GLuint ModelID;
	GLuint ViewMatrixID;
	GLuint ModelMatrixID;
	GLuint LightID;
	glm::mat4 MVP;
	glm::vec3 lightPos;
	void sendBufferData();
	public:
		// std::vector<glm::vec4> triangles;
		// std::vector<glm::vec2> uvdata;
		// std::vector<glm::vec4> normals;
		Physics::Factory* physics = 0;
		bool dataHasUpdated = false;
		GLuint vertexbuffer, uvbuffer, normalbuffer;
		int render(double* delta, int* frames, int* framerate, bool* menu);
		RenderEngine();
		~RenderEngine();
		void loop();
};
#endif
