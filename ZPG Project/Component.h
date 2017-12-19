#pragma once
#include "stdafx.h"
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

class Component
{
public:
	virtual glm::mat4 transform(glm::mat4) = 0;
};
