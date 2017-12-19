#include "stdafx.h"

#include "Rescale.h"

Rescale::Rescale(float rescaleValue)
{
	this->rescaleVec = glm::vec3(rescaleValue);
}

glm::mat4 Rescale::transform(glm::mat4 modelMatrix)
{
	return glm::scale(modelMatrix, this->rescaleVec);
}