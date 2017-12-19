#include "stdafx.h"

#include "Translate.h"

Translate::Translate(glm::vec3 shiftVec)
{
	this->shiftVec = shiftVec;
}

glm::mat4 Translate::transform(glm::mat4 modelMatrix)
{
	glm::mat4 tmp = glm::translate(modelMatrix, this->shiftVec);
	return tmp;
}