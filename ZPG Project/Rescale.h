#pragma once
#include "stdafx.h"

#include "Component.h"

class Rescale : public Component
{
public:
	Rescale(float);
	glm::mat4 transform(glm::mat4);

private:
	glm::vec3 rescaleVec;


};
