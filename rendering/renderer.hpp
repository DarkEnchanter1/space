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
			std::vector<Triangle> triangles;
			std::vector<UVData>   uvdata;
			std::vector<Normals>  normals;
			GLuint vertexbuffer, uvbuffer, normalbuffer;
			int render();
			RenderEngine();
			~RenderEngine();
	};
	struct Model {
		Model(const char* modelid);
		std::vector<Triangle> triangles;
		std::vector<UVData>   uvdata;
		std::vector<Normals>  normals;
	};
}
#endif