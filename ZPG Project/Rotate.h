#pragma once

#include "stdafx.h"

#include "Component.h"

class Rotate : public Component
{
public:
	Rotate(glm::vec3, float);
	glm::mat4 transform(glm::mat4);

private:
	glm::vec3 axisVec;
	float angle;
};
