#include "stdafx.h"
#include "Object.h"



Object::Object(std::vector<float> vector, int shaderKey)
{
	modelMatrix = glm::mat4(1.0f);

	existsInWorld = true;

	indicesCount = 0;

	this->shaderKey = shaderKey;

	size_t vecSize = vector.size() * sizeof(float);

	this->VBO = 0;
	glGenBuffers(1, &this->VBO); // generate the this->VBO
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, vecSize, vector.data(), GL_STATIC_DRAW);

	//vertex attribute object(VAO)
	this->VAO = 0;
	glGenVertexArrays(1, &this->VAO); //generate the this->VAO
	glBindVertexArray(this->VAO); //bind the this->VAO
	glEnableVertexAttribArray(0); //enable vertex attributes
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}

Object::Object(const float vertices[], int shaderKey, int size, glm::vec4 objectColour)
{
	ID = -1;

	indicesCount = 0;
	existsInWorld = true;

	this->objectColour = objectColour;

	modelMatrix = glm::mat4(1.0f);

	this->shaderKey = shaderKey;
	this->textureKey = -1;
	this->VAO = 0;
	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	this->VBO = 0;
	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*) (3 * sizeof(float)));
	glBindVertexArray(0);

	//vertex attribute object(VAO)
	
}

Object::Object(const float vertices[], int shaderKey, int textureKey, int size)
{


	existsInWorld = true;
	ID = -1;
	indicesCount = 0;
	this->shaderKey = shaderKey;
	this->textureKey = textureKey;
	modelMatrix = glm::mat4(1.0f);
	this->VAO = 0;
	this->VBO = 0;
	this->IBO = 0;
	
	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	
	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(6 * sizeof(float)));
	glBindVertexArray(0);

	

	
	//vertex attribute object(VAO)

}


Object::Object(string fileName, int shaderKey, int textureKey)
{
	existsInWorld = true;
	ID = -1;
	indicesCount = 0;
	this->shaderKey = shaderKey;
	this->textureKey = textureKey;
	modelMatrix = glm::mat4(1.0f);
	this->VAO = 0;
	this->VBO = 0;
	this->IBO = 0;

	Assimp::Importer importer;
	unsigned int importOptions = aiProcess_Triangulate
		| aiProcess_OptimizeMeshes              // slouèení malých plošek
		| aiProcess_JoinIdenticalVertices       // NUTNÉ jinak hodnì duplikuje
		| aiProcess_Triangulate                 // prevod vsech ploch na trojuhelniky
		| aiProcess_CalcTangentSpace;           // vypocet tangenty, nutny pro spravne pouziti normalove mapy


												//aiProcess_GenNormals/ai_Process_GenSmoothNormals - vypocet normal s jemnych prechodem v pripade, ze objekt neobsahuje normaly

	const aiScene* scene = importer.ReadFile(fileName, importOptions);

	if (scene) { //pokud bylo nacteni uspesne
		printf("scene->mNumMeshes = %d\n", scene->mNumMeshes);
		printf("scene->mNumMaterials = %d\n", scene->mNumMaterials);

		for (unsigned int i = 0; i < scene->mNumMaterials; i++)                       //Materials
		{
			const aiMaterial* mat = scene->mMaterials[i];

			aiString name;
			mat->Get(AI_MATKEY_NAME, name);
			printf("Material [%d] name %s\n", i, name.C_Str());

			aiColor4D d;

			//glm::vec4 diffuse = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
			if (AI_SUCCESS == aiGetMaterialColor(mat, AI_MATKEY_COLOR_DIFFUSE, &d))
				objectColour = glm::vec4(d.r, d.g, d.b, d.a);


		}

		for (unsigned int i = 0; i < scene->mNumMeshes; i++)                      //Objects
		{
			aiMesh* mesh = scene->mMeshes[i];

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


			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &IBO);

			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);

			glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)* mesh->mNumVertices, pVertices, GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(0));
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(GLfloat)));
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(6 * sizeof(GLfloat)));
			glEnableVertexAttribArray(3);
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(8 * sizeof(GLfloat)));
			

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)* mesh->mNumFaces * 3, pIndices, GL_STATIC_DRAW);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(VAO);

			GLuint err = glGetError();
			if (err != GL_NO_ERROR)
			{
				std::cout << "GL ERROR: " << err << std::endl; return;
			}
			indicesCount = mesh->mNumFaces * 3;

			delete[] pVertices;
			delete[] pIndices;
		}
	}
	else {
		printf("Error during parsing mesh from %s : %s \n", fileName.c_str(), importer.GetErrorString());
	}
	glBindVertexArray(0);

	
}


Object::~Object()
{
	this->VAO = 0;
	this->VBO = 0;
}

GLuint Object::getVAO()
{
	return this->VAO;
}

int Object::getShaderKey()
{
	return this->shaderKey;
}

int Object::getTextureKey()
{
	return this->textureKey;
}


void Object::initTransformation(glm::vec3 translateVector, float scaleVector)
{
	Composite comp;
	comp.add(new Translate(translateVector));
	comp.add(new Rescale(scaleVector));

	this->modelMatrix = comp.transform(this->modelMatrix);
	
}

//Rotate an object
void Object::rotate(float angle, glm::vec3 rotationVector)
{
	Rotate rotate(rotationVector, angle);
	this->modelMatrix = rotate.transform(this->modelMatrix);
	return;
}

//Translate an object
void Object::translate(glm::vec3 translateVector)
{

	Translate trans(translateVector);
	this->modelMatrix = trans.transform(this->modelMatrix);
	
	return;

}

//Rescale an object
void Object::scale(float scale)
{
	Rescale rescale(scale);
	this->modelMatrix = rescale.transform(this->modelMatrix);
	return;
}

void Object::setID(int ID)
{
	this->ID = ID;
}

int Object::getID()
{
	return this->ID;
}


glm::mat4 Object::getModelMatrix()
{
	return this->modelMatrix;
}

glm::vec4 Object::getColour()
{
	return this->objectColour;
}



int Object::getIndicesCount()
{
	return this->indicesCount;
}

void Object::deleteObject(int index)
{
	existsInWorld = false;
}

bool Object::isRendered()
{
	return existsInWorld;
}

