#pragma once
#include "stdafx.h"
#include <vector>

#include "Component.h"

using namespace std;


class Composite : public Component
{

public:
	~Composite();
	void add(Component *);
	glm::mat4 transform(glm::mat4);
private:
	vector <Component *> transfomations;
	

};
