#pragma once

#include "stdafx.h"

#include "Object.h"

class AssimpObject : public Object
{
public:
	AssimpObject(std::string, int, int);
	float getVerticesCount();
};
