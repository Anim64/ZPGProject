#pragma once
#include "stdafx.h"
#include <assimp/Importer.hpp>

#include <assimp/scene.h>

#include <assimp/postprocess.h>

#include <GL\glew.h>
#include <vector>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

struct Vertex
{
	float Position[3];
	float Normal[3];
	float Texture[2];
	float Tangent[3];
};

class AssimpModelLoader
{
public:
	void loadModel(char*);
	void loadMaterials(const aiScene* scene);
	void loadObject(const aiScene* scene);
	void fillMesh(const aiScene* scene);
	void fillIndices(const aiScene* scene);

private:
	aiMesh* mesh;
	Vertex * pVertices;
	unsigned int* pIndices;

};
