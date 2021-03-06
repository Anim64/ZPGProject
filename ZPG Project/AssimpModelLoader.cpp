#include "stdafx.h"
#include "AssimpModelLoader.h"

void AssimpModelLoader::loadModel(char* path)
{
	Assimp::Importer importer;
	unsigned int importOptions = aiProcess_Triangulate
		| aiProcess_OptimizeMeshes              // slou�en� mal�ch plo�ek
		| aiProcess_JoinIdenticalVertices       // NUTN� jinak hodn� duplikuje
		| aiProcess_Triangulate                 // prevod vsech ploch na trojuhelniky
		| aiProcess_CalcTangentSpace;


	const aiScene* scene = importer.ReadFile(path, importOptions);

	loadMaterials(scene);
	loadObject(scene);
		
}

void AssimpModelLoader::loadMaterials(const aiScene* scene)
{
	if (scene) { //pokud bylo nacteni uspesne
		printf("scene->mNumMeshes = %d\n", scene->mNumMeshes);
		printf("scene->mNumMaterials = %d\n", scene->mNumMaterials);

		for (unsigned int i = 0; i < scene->mNumMaterials; i++)                     
		{
			const aiMaterial* mat = scene->mMaterials[i];

			aiString name;
			mat->Get(AI_MATKEY_NAME, name);
			printf("Material [%d] name %s\n", i, name.C_Str());

			aiColor4D d;

			glm::vec4 diffuse = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
			if (AI_SUCCESS == aiGetMaterialColor(mat, AI_MATKEY_COLOR_DIFFUSE, &d))
				diffuse = glm::vec4(d.r, d.g, d.b, d.a);

		}
	}
}

void AssimpModelLoader::loadObject(const aiScene* scene)
{
	for (unsigned int i = 0; i < scene->mNumMeshes; i++)                      
	{
		mesh = scene->mMeshes[i];

		Vertex* pVertices = new Vertex[mesh->mNumVertices];
		std::memset(pVertices, 0, sizeof(Vertex)* mesh->mNumVertices);

		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			if (mesh->HasPositions())
			{
				pVertices[i].Position[0] = mesh->mVertices[i].x;
				pVertices[i].Position[1] = mesh->mVertices[i].y;
				pVertices[i].Position[2] = mesh->mVertices[i].z;
			}
			if (mesh->HasNormals())
			{
				pVertices[i].Normal[0] = mesh->mNormals[i].x;
				pVertices[i].Normal[1] = mesh->mNormals[i].y;
				pVertices[i].Normal[2] = mesh->mNormals[i].z;
			}
			if (mesh->HasTextureCoords(0))
			{
				pVertices[i].Texture[0] = mesh->mTextureCoords[0][i].x;
				pVertices[i].Texture[1] = mesh->mTextureCoords[0][i].y;
			}
			if (mesh->HasTangentsAndBitangents())
			{
				pVertices[i].Tangent[0] = mesh->mTangents[i].x;
				pVertices[i].Tangent[1] = mesh->mTangents[i].y;
				pVertices[i].Tangent[2] = mesh->mTangents[i].z;
			}

		}

		unsigned int* pIndices = nullptr;

		if (mesh->HasFaces())
		{

			pIndices = new unsigned int[mesh->mNumFaces * 3];
			for (unsigned int i = 0; i < mesh->mNumFaces; i++)
			{
				pIndices[i * 3] = mesh->mFaces[i].mIndices[0];
				pIndices[i * 3 + 1] = mesh->mFaces[i].mIndices[1];
				pIndices[i * 3 + 2] = mesh->mFaces[i].mIndices[2];
			}
		}
	}
}

void fillMesh(const aiScene* scene)
{



}
void fillIndices(const aiScene* scene)
{

}

