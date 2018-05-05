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
	class RenderEngine;
	class Model;

	class RenderEngine {
		GLuint Texture;
		GLuint TextureID;
		GLuint VertexArrayID;
		GLuint programID;
		GLuint MatrixID;
		GLuint ViewMatrixID;
		GLuint ModelMatrixID;
		GLuint LightID;
		glm::mat4 MVP;
		glm::vec3 lightPos;
		public:
			std::vector<glm::vec3> triangles;
			std::vector<glm::vec2>   uvdata;
			std::vector<glm::vec3>  normals;
			GLuint vertexbuffer, uvbuffer, normalbuffer;
			int render();
			RenderEngine();
			~RenderEngine();
			void loop();
	};
	struct Model {
		Model(const char* modelid);
		std::vector<glm::vec3> triangles;
		std::vector<glm::vec2>   uvdata;
		std::vector<glm::vec3>  normals;
	};
}
#endif