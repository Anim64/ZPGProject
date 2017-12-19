#pragma once
#include "stdafx.h"
#include <vector>

#include "Observer.h"


class Subject {
public:
	
	
	void addObserver(Observer*);
	void removeObserver();
	void notify(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::vec3 eye);
	void notify(glm::vec3 lightPosition);


protected:
	std::vector<Observer*> observers;

};