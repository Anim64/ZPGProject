#include "stdafx.h"

#include "PlainModel.h"

const int PlainModel::indicesCount = 0;
const int PlainModel::verticesCount = 2880;



const float PlainModel::mesh[] = {
	1.0f, 0.0f,  1.0f,   0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, -1.0f,   0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	-1.0f, 0.0f, -1.0f,   0.0f, 1.0f, 0.0f, 1.0f, 1.0f,

	-1.0f, 0.0f,  1.0f,   0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	1.0f, 0.0f,  1.0f,   0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, -1.0f,   0.0f, 1.0f, 0.0f, 1.0f, 1.0f

};