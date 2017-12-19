#include "stdafx.h"

#include "AssimpObject.h"

AssimpObject::AssimpObject(std::string fileName, int shaderKey, int textureKey): Object(fileName, shaderKey, textureKey)
{
	return;
}

float AssimpObject::getVerticesCount()
{
	return this->getIndicesCount();
}