#include "Model.h"

const int Model::getIndicesCount()
{
	return this->indicesCount;
	
}

const int Model::getVerticesCount()
{
	return this->verticesCount;
}

const float* Model::getMesh()
{
	return mesh;
}

/*unsigned int Model::getMeshSize()
{
	return sizeof(this->mesh);
}*/