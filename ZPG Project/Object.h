#pragma once
#include <GL\glew.h>
#include <vector>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>


#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <SOIL2.h>
#include "Shader.h"

#include "Translate.h"
#include "Rescale.h"
#include "Rotate.h"
#include "Composite.h"



struct Vertex
{
	float Position[3];
	float Normal[3];
	float Texture[2];
	float Tangent[3];
	float BiTangent[3];
};


class Object
{

public:
	Object(std::vector<float>, int);
	Object(const float[], int, int, glm::vec4);
	Object(const float vertices[], int shaderKey, int textureKey, int size);
	Object(std::string fileName, int shaderKey, int textureKey);
	

	~Object();

	

	GLuint getVAO();
	glm::mat4 getModelMatrix();
	glm::vec4 getColour();
	int getShaderKey();
	int getTextureKey();
	int getIndicesCount();
	bool isRendered();

	int getID();
	void setID(int ID);


	void initTransformation(glm::vec3 translateVector, float scaleVector);
	void rotate(float angle, glm::vec3 rotationVector);
	void translate(glm::vec3 translateVector);
	void scale(float scale);
	

	virtual float getVerticesCount() = 0;

	void deleteObject(int index);
	
	
private:
	int ID;
	glm::mat4 modelMatrix;
	GLuint VAO, VBO, IBO;
	
	glm::vec4 objectColour;
	int indicesCount;

	int shaderKey;
	int textureKey;

	bool existsInWorld;


	
};