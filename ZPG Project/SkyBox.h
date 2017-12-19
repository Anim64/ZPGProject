#pragma once

#include "stdafx.h"
#include "Object.h"

class SkyBox : public Object
{
public:
	SkyBox(std::string, int, int);
	float getVerticesCount();
	glm::vec3 getPosition();
	void setPosition(glm::vec3 newPos);

private:
	glm::vec3 position;
};
