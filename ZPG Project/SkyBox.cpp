#include "stdafx.h"

#include "SkyBox.h"

SkyBox::SkyBox(std::string fileName, int shaderKey, int textureKey) : Object(fileName, shaderKey, textureKey)
{
	this->position = glm::vec3(0);
}

float SkyBox::getVerticesCount()
{
	return this->getIndicesCount();
}

glm::vec3 SkyBox::getPosition()
{
	return this->position;
}

void SkyBox::setPosition(glm::vec3 newPos)
{
	this->position = newPos;
}