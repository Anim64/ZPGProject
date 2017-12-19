#include "stdafx.h"
#include "Shader.h"


Shader::Shader(const char* vertex_shader, const char* fragment_shader)
{
	
	shaderProgram = loadShader(vertex_shader, fragment_shader);
	ModelTransform = glGetUniformLocation(this->shaderProgram, "ModelMatrix");
	ViewTransform = glGetUniformLocation(this->shaderProgram, "viewMatrix");
	ProjectionTransform = glGetUniformLocation(this->shaderProgram, "projectionMatrix");


	cameraPosition = glGetUniformLocation(this->shaderProgram, "cameraPosition");

	objectColor = glGetUniformLocation(this->shaderProgram, "objectColour");

	texture = glGetUniformLocation(this->shaderProgram, "textura");

	


}


Shader::~Shader()
{
	deleteShader();
}

void Shader::setShader()
{
	glUseProgram(shaderProgram);
}

void Shader::setModelMatrix(glm::mat4 modelMatrix)
{
	
	glUniformMatrix4fv(ModelTransform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	
}


void Shader::update(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::vec3 eye)
{
	glUseProgram(shaderProgram);

	glUniformMatrix4fv(ViewTransform, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(ProjectionTransform, 1, GL_FALSE, glm::value_ptr(projectionMatrix));


	glProgramUniform3f(this->shaderProgram, cameraPosition, eye.x, eye.y, eye.z);


	
	
}



void Shader::setObjectColor(glm::vec4 objectColourVec)
{
	glProgramUniform4f(this->shaderProgram, objectColor, objectColourVec.x, objectColourVec.y, objectColourVec.z, objectColourVec.a);
}

void Shader::setTexture(GLuint textureID)
{
	
	glUniform1i(texture, textureID);
	
}

void Shader::setNormalMapTexture(GLuint textureID)
{

	glUniform1i(glGetUniformLocation(this->shaderProgram, "normalMapTex") , textureID);

}

void Shader::setAllLights(vector<Light> lightsVec)
{

	//glUniform1i(glGetUniformLocation(this->shaderProgram, "numberOfLights"), (int)lightsVec.size());
	
	glProgramUniform1i(this->shaderProgram, glGetUniformLocation(this->shaderProgram, "numberOfLights"), (int)lightsVec.size());


	string locationStr;
	
	
	

	for (size_t i = 0; i < lightsVec.size(); i++)
	{
		

		locationStr = "allLights[" + std::to_string(i) + "].position";
		glProgramUniform4f(this->shaderProgram, glGetUniformLocation(this->shaderProgram, locationStr.c_str()), lightsVec[i].getLightProperties().position.x, lightsVec[i].getLightProperties().position.y,lightsVec[i].getLightProperties().position.z,lightsVec[i].getLightProperties().position.w);

		locationStr = "allLights[" + std::to_string(i) + "].intensities";
		glProgramUniform3f(this->shaderProgram, glGetUniformLocation(this->shaderProgram, locationStr.c_str()), lightsVec[i].getLightProperties().intensities.x, lightsVec[i].getLightProperties().intensities.y, lightsVec[i].getLightProperties().intensities.z);

		locationStr = "allLights[" + std::to_string(i) + "].attenuation";
		glProgramUniform1f(this->shaderProgram, glGetUniformLocation(this->shaderProgram, locationStr.c_str()), lightsVec[i].getLightProperties().attenuation);

		locationStr = "allLights[" + std::to_string(i) + "].ambientCoefficient";
		glProgramUniform1f(this->shaderProgram, glGetUniformLocation(this->shaderProgram, locationStr.c_str()), lightsVec[i].getLightProperties().ambientCoefficient);

		locationStr = "allLights[" + std::to_string(i) + "].coneAngle";
		glProgramUniform1f(this->shaderProgram, glGetUniformLocation(this->shaderProgram, locationStr.c_str()), lightsVec[i].getLightProperties().coneAngle);

		locationStr = "allLights[" + std::to_string(i) + "].coneDirection";
		glProgramUniform3f(this->shaderProgram, glGetUniformLocation(this->shaderProgram, locationStr.c_str()), lightsVec[i].getLightProperties().coneDirection.x, lightsVec[i].getLightProperties().coneDirection.y, lightsVec[i].getLightProperties().coneDirection.z);

		

	}

	

}

