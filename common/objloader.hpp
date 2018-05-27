#ifndef OBJLOADER_H
#define OBJLOADER_H

bool loadAssImp(
	const char * path, 
	std::vector<unsigned short> & indices,
	std::vector<glm::vec4> & vertices,
	std::vector<glm::vec2> & uvs,
	std::vector<glm::vec4> & normals
);

#endif
