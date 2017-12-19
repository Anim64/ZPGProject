#pragma once
#include "stdafx.h"

#include "Component.h"


class Translate: public Component
{
public:
	Translate(glm::vec3);
	glm::mat4 transform(glm::mat4);

private:
	glm::vec3 shiftVec;

};
