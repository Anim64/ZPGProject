#pragma once

#include "stdafx.h"
#include "Texture.h"
#include <GL\glew.h>
#include <vector>
#include<glm/glm.hpp>


static class TextureLoader
{
public:
	static Texture* loadTexture(std::string path, std::string description);
	static Texture* loadSkyBoxTextures(std::vector<std::string> paths);
};
