#include "stdafx.h"
#include "Subject.h"

void  Subject::addObserver(Observer* obs)
{
	observers.push_back(obs);

}

void Subject::removeObserver()
{
	observers.pop_back();
}

void Subject::notify(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::vec3 eye)
{
	for (int i = 0; i < observers.size(); i++)
		observers[i]->update(viewMatrix, projectionMatrix,eye);
}


