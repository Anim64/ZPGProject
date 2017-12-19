#pragma once

#include "stdafx.h"

class Model
{
public:
	const int getVerticesCount();
	const int getIndicesCount();
	const float* getMesh();
	//unsigned int getMeshSize();
	
protected:
	static const int verticesCount;
	static const int indicesCount;
	static const float mesh[];

};

