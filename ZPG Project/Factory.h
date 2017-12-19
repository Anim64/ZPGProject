#pragma once
#include "stdafx.h"

#include <GL\glew.h>
#include<glm/glm.hpp>
#include "Camera.h"
#include "Object.h"

class Factory
{
public:
	Camera* createCamera(glm::vec3 eye, glm::vec3 target, glm::vec3 up);
	Light createDirectionalLight(glm:: vec3 position, glm::vec3 intensities, float ambientCoefficient);
	Light createPointLight(glm::vec3 position, glm::vec3 intensities, float attenuation,  float ambientCoefficient);
	Light createSpotLight(glm::vec3 position, glm::vec3 intensities, float attenuation, float ambientCoefficient, float coneAngle, glm::vec3 coneDirection);

	//Object * createObjectWithTexture(int shaderKey,)
	Object* createAssimpObject(std::string pathToModel, int shaderKey, int textureKey);
	

};
