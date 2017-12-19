#pragma once
#include <GL\glew.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include "ShaderLoader.h"
#include "Observer.h"
#include "Light.h"







class Shader : public ShaderLoader, public Observer
{
public:
	Shader(const char* vertex_shader, const char* fragment_shader);
	~Shader();
	void setModelMatrix(glm::mat4 modelMatrix);
	
	void setShader();
	void setObjectColor(glm::vec4);
	void setTexture(GLuint textureID);
	void setNormalMapTexture(GLuint textureID);
	void setAllLights(vector<Light> lights);

	void update(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::vec3 eye);
	

private:
	GLuint shaderProgram;

	GLuint ModelTransform;
	GLuint ViewTransform;
	GLuint ProjectionTransform;



	GLuint cameraPosition;

	GLuint objectColor;

	GLuint texture;

	



	
};
