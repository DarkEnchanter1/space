#include <vector>
#include <cstring>
#include <map>
#include <iostream>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "rendering/utils/shader.hpp"
#include "rendering/utils/texture.hpp"
#include "common/jsonreader.hpp"
using json = nlohmann::json;

json fontData;
/// Stores the data for characters in a table with the characters ASCII value as the key
std::map<int, json> charData;
#include "text2D.hpp"

unsigned int Text2DTextureID;
unsigned int Text2DVertexBufferID;
unsigned int Text2DUVBufferID;
unsigned int Text2DShaderID;
unsigned int Text2DUniformID;

unsigned int tTexHeight,tTexWidth;

void initText2D(const char* texturePath, const char* jsonPath){
	fontData = func(jsonPath);
	for (json element : fontData.value("/symbols"_json_pointer, json())) {
		charData[element.value("/id"_json_pointer, 0)] = element;
	}
	tTexHeight = fontData.at("/config"_json_pointer).at("/textureHeight"_json_pointer);
	tTexWidth = fontData.at("/config"_json_pointer).at("/textureWidth"_json_pointer);
	// Initialize texture
	Text2DTextureID = loadDDS(texturePath);

	// Initialize VBO
	glGenBuffers(1, &Text2DVertexBufferID);
	glGenBuffers(1, &Text2DUVBufferID);

	// Initialize Shader
	Text2DShaderID = LoadShaders( "resources/text.vs", "resources/text.fs" );

	// Initialize uniforms' IDs
	Text2DUniformID = glGetUniformLocation( Text2DShaderID, "myTextureSampler" );

}

void printText2D(const char * text, int x, int y, int size){

	unsigned int length = strlen(text);

	// Fill buffers
	std::vector<glm::vec2> vertices;
	std::vector<glm::vec2> UVs;
	for ( unsigned int i=0 ; i<length ; i++ ){
		
		glm::vec2 vertex_up_left    = glm::vec2( x+i*size     , y+size ); //Top    left  coord
		glm::vec2 vertex_up_right   = glm::vec2( x+i*size+size, y+size ); //Top    right coord
		glm::vec2 vertex_down_right = glm::vec2( x+i*size+size, y      ); //Bottom right coord
		glm::vec2 vertex_down_left  = glm::vec2( x+i*size     , y      ); //Bottom left coord

		vertices.push_back(vertex_up_left   );
		vertices.push_back(vertex_down_left );
		vertices.push_back(vertex_up_right  );

		vertices.push_back(vertex_down_right);
		vertices.push_back(vertex_up_right);
		vertices.push_back(vertex_down_left);

		char character = text[i];
		float uv_x = ((float)charData[(int)character].value("/x"_json_pointer, 0))/(float)tTexWidth;
		float uv_y = ((float)charData[(int)character].value("/y"_json_pointer, 0))/(float)tTexHeight;
		float uv_w = uv_x+((float)charData[(int)character].value("/width"_json_pointer, 0))/(float)tTexWidth;
		float uv_h = (uv_y + ((float)charData[(int)character].value("/height"_json_pointer, 0))/(float)tTexHeight);
//		float uv_x = (character%16)/16.0f;
//		float uv_y = (character/16)/16.0f;
		glm::vec2 uv_up_left    = glm::vec2( uv_x, uv_y);
		glm::vec2 uv_up_right   = glm::vec2( uv_w, uv_y);
		glm::vec2 uv_down_right = glm::vec2( uv_w, uv_h);
		glm::vec2 uv_down_left  = glm::vec2( uv_x, uv_h);
		UVs.push_back(uv_up_left   );
		UVs.push_back(uv_down_left );
		UVs.push_back(uv_up_right  );

		UVs.push_back(uv_down_right);
		UVs.push_back(uv_up_right);
		UVs.push_back(uv_down_left);
	}
	glBindBuffer(GL_ARRAY_BUFFER, Text2DVertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, Text2DUVBufferID);
	glBufferData(GL_ARRAY_BUFFER, UVs.size() * sizeof(glm::vec2), &UVs[0], GL_STATIC_DRAW);

	// Bind shader
	glUseProgram(Text2DShaderID);

	// Bind texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Text2DTextureID);
	// Set our "myTextureSampler" sampler to use Texture Unit 0
	glUniform1i(Text2DUniformID, 0);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, Text2DVertexBufferID);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 );

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, Text2DUVBufferID);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 );

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Draw call
	glDrawArrays(GL_TRIANGLES, 0, vertices.size() );

	glDisable(GL_BLEND);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

}

void cleanupText2D(){

	// Delete buffers
	glDeleteBuffers(1, &Text2DVertexBufferID);
	glDeleteBuffers(1, &Text2DUVBufferID);

	// Delete texture
	glDeleteTextures(1, &Text2DTextureID);

	// Delete shader
	glDeleteProgram(Text2DShaderID);
}
