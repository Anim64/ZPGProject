#include "stdafx.h"

#include "Rotate.h"

Rotate::Rotate(glm::vec3 axisVec, float angle)
{
	
	this->axisVec = axisVec;
	this->angle = angle;
}

glm::mat4 Rotate::transform(glm::mat4 modelMatrix)
{
	return glm::rotate(modelMatrix, this->angle, this->axisVec);
}