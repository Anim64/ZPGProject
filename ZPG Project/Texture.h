#pragma once
#include "stdafx.h"

#include <SOIL2.h>

#include <GL\glew.h>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>

#include <string>

class Texture
{
public:
	Texture(GLuint textureID, std::string description);

	GLuint getTextureID();

private:
	GLuint textureID;
	std::string description;
};
