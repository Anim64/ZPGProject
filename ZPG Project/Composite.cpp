#include "stdafx.h"

#include "Composite.h"



void Composite::add(Component * comp)
{
	this->transfomations.push_back(comp);
}

glm::mat4 Composite::transform(glm::mat4 modelMatrix)
{

	glm::mat4 tempModelMatrix = modelMatrix;
	for (int i = 0; i < this->transfomations.size(); i++)
	{
		tempModelMatrix = transfomations[i]->transform(tempModelMatrix);
	}

	return tempModelMatrix;
}

Composite::~Composite()
{
	for (int i = 0; i < transfomations.size(); i++)
	{
		delete transfomations.at(i);
	}
}