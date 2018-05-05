#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>
#include <iostream>

#include <glm/glm.hpp>

#include "objloader.hpp"

// Very, VERY simple OBJ loader.
// Here is a short list of features a real function would provide : 
// - Binary files. Reading a model should be just a few memcpy's away, not parsing a file at runtime. In short : OBJ is not very great.
// - Animations & bones (includes bones weights)
// - Multiple UVs
// - All attributes should be optional, not "forced"
// - More stable. Change a line in the OBJ file and it crashes.
// - More secure. Change another line and you can inject code.
// - Loading from memory, stream, etc


// Include AssImp
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

bool loadAssImp(
	const char * path, 
	std::vector<unsigned short> & indices,
	std::vector<glm::vec3> & vertices,
	std::vector<glm::vec2> & uvs,
	std::vector<glm::vec3> & normals
){

	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(path, 0/*aiProcess_JoinIdenticalVertices | aiProcess_SortByPType*/);
	if( !scene) {
		fprintf( stderr, importer.GetErrorString());
		getchar();
		return false;
	}
	for (unsigned int mn = 0; mn < scene->mNumMeshes; mn++) {
	const aiMesh* mesh = scene->mMeshes[mn]; // In this simple example code we always use the 1rst mesh (in OBJ files there is often only one anyway)
	//std::cout << "Starting mesh " << mn << std::endl;
	// Fill vertices positions
	vertices.reserve(mesh->mNumVertices);
	for(unsigned int i=0; i<mesh->mNumVertices; i++){
		aiVector3D pos = mesh->mVertices[i];
		vertices.push_back(glm::vec3(pos.x, pos.y, pos.z));
	}
	//std::cout << "vertices positions set" << std::endl;
	// Fill vertices texture coordinates
	uvs.reserve(mesh->mNumVertices);	
	//std::cout << mesh->GetNumUVChannels() << std::endl;
	//std::cout << mesh->mNumUVComponents << std::endl;
	//	std::cout << "Done with vertices for mesh, UV total coords is " << mesh->mNumUVComponents[0] << mn << std::endl;

	for(unsigned int i=0; i<mesh->mNumVertices; i++){
		aiVector3D UVW;
		if (mesh->GetNumUVChannels() != 0)
			UVW = mesh->mTextureCoords[0][i]; // Assume only 1 set of UV coords; AssImp supports 8 UV sets.
	//	std::cout << "Pushing data on to vector " << i << std::endl;
		uvs.push_back(glm::vec2(UVW.x, UVW.y));
	}
	//	std::cout << "Done with UV for mesh " << mn << std::endl;
	//std::cout << "Texture coords loaded" << std::endl;
	// Fill vertices normals
	normals.reserve(mesh->mNumVertices);
	for(unsigned int i=0; i<mesh->mNumVertices; i++){
		aiVector3D n = mesh->mNormals[i];
		normals.push_back(glm::vec3(n.x, n.y, n.z));
	}
	//	std::cout << "Done with normals for mesh " << mn << std::endl;
	//	std::cout << "Normals loaded" << std::endl;
	// Fill face indices
	indices.reserve(3*mesh->mNumFaces);
	for (unsigned int i=0; i<mesh->mNumFaces; i++){
		// Assume the model has only triangles.
	//	std::cout << "Indices in face" << i << ": " << mesh->mFaces[i].mNumIndices << std::endl;
		indices.push_back(mesh->mFaces[i].mIndices[0]);
		indices.push_back(mesh->mFaces[i].mIndices[1]);
		indices.push_back(mesh->mFaces[i].mIndices[2]);
	}
	//std::cout << "Ending mesh " << mn << std::endl;
	}
	// The "scene" pointer will be deleted automatically by "importer"
	return true;
}

