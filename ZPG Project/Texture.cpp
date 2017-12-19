#include "stdafx.h"

#include "Texture.h"

Texture::Texture(GLuint textureID, std::string description)
{

	this->textureID = textureID;
	this->description = description;
	
}

GLuint Texture::getTextureID()
{
	return this->textureID;
}