#include "stdafx.h"
#include "Light.h"

Light::Light(LightStruct lightStruct)
{
	this->light = lightStruct;
}

void Light::changePosition(float newX, float newY, float newZ)
{
	this->light.position.x = newX;
	this->light.position.y = newY;
	this->light.position.z = newZ;

	
}


void Light::rotateAroundPoint(glm::vec3 centrePoint, glm::vec3 rotateDirection)
{
	
}

LightStruct Light::getLightProperties()
{
	return this->light;
}

