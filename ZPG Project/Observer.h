#pragma once

#include "stdafx.h"
#include <GL\glew.h>
#include <vector>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

class Observer {
public:
	virtual void update(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::vec3 eye) = 0;

};