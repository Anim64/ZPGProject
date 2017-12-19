#include "stdafx.h"
#include "Plain.h"

const float Plain::pocetPrvku = 6;

/*const float Plain::plain[] = {
	1.0f, 0.0f,  1.0f,   0.0f, 1.0f, 0.0f,
	1.0f, 0.0f, -1.0f,   0.0f, 1.0f, 0.0f,
	-1.0f, 0.0f, -1.0f,   0.0f, 1.0f, 0.0f,

	-1.0f, 0.0f,  1.0f,   0.0f, 1.0f, 0.0f,
	1.0f, 0.0f,  1.0f,   0.0f, 1.0f, 0.0f,
	-1.0f, 0.0f, -1.0f,   0.0f, 1.0f, 0.0f,

};*/

const float Plain::plain[] = {
	1.0f, 0.0f,  1.0f,   0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, -1.0f,   0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	-1.0f, 0.0f, -1.0f,   0.0f, 1.0f, 0.0f, 1.0f, 1.0f,

	-1.0f, 0.0f,  1.0f,   0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	1.0f, 0.0f,  1.0f,   0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, -1.0f,   0.0f, 1.0f, 0.0f, 1.0f, 1.0f

};

Plain::Plain(int shaderKey, glm::vec4 objectColour) : Object(plain, shaderKey, sizeof(plain), objectColour)
{
	return;
}

Plain::Plain(int shaderKey,int textureKey) : Object(plain, shaderKey, textureKey, sizeof(plain))
{
	return;
}

float Plain::getVerticesCount()
{
	return this->pocetPrvku;
}