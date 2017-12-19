// ZPG Project.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//Include GLEW
#include <GL/glew.h>
//Include GLFW 
#include <GLFW/glfw3.h>
#include "Application.h"
#include "sphere.h"
#include "Plain.h"
#include "AssimpObject.h"
#include "Translate.h"
#include "Rescale.h"



int main()
{

	


	


	
	

	Application * applic = Application::getInstance();

	

	applic->createScene("Scene", NULL);
	

	

	


	

	//Texture* texture = new Texture("terrain.jpg");

	//Sphere* sphereObject1 = new Sphere(2, glm::vec4(1.0, 0.8, 0.0, 1.0));
	//Sphere* sphereObject2 = new Sphere(1, glm::vec4(0.0, 1.0, 0.0, 1.0));//Sphere* sphereObject3 = new Sphere(1, glm::vec3(1.0, 0.0, 0.0));
	//Sphere* sphereObject4 = new Sphere(1, glm::vec3(0.0, 0.0, 1.0));


	
	//sphereObject1->initTransformation(glm::vec3(1.0f, 0.0f, 0.0f), 0.2f);
	//sphereObject2->initTransformation(glm::vec3(-1.0f, 0.0f, 0.0f), 0.2f);
	//sphereObject1->scale(0.2f);
	//sphereObject2->scale(0.2f);
	//sphereObject3->scale(glm::vec3(0.2f));
	//sphereObject4->scale(glm::vec3(0.2f));

	//sphereObject1->translate(glm::vec3(4.0f, 0.0f, 0.0f));
	//sphereObject2->translate(glm::vec3(-4.0f, 0.0f, 0.0f));
	//sphereObject3->translate(glm::vec3(0.0f, 4.0f, 0.0f));
	//sphereObject4->translate(glm::vec3(0.0f, -4.0f, 0.0f));

	Plain * plainObject = new Plain(1,2);

	plainObject->scale(100.0f);

	//plainObject->translate(glm::vec3(0.0f, 0.0f, 0.0f));

	AssimpObject* asObj = new AssimpObject("./Models/House/test.obj", 1, 1);

	//asObj->translate(glm::vec3(0, 5, 0));
	
	//Object* floorObject = new Object(floorPoints, 1);
	//triangleObject->rotate(1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	//triangleObject->translate(glm::vec3(1.0f, 0.0f, 0.0f));
	//triangleObject->scale(glm::vec3(0.5f));

	//asObj->translate(glm::vec3(0.0f, 0.0f, 0.0f));
	//applic->getCurrentScene()->addObject(sphereObject1);
	//applic->getCurrentScene()->addObject(sphereObject2);
	//applic->getCurrentScene()->addObject(sphereObject3);
	//applic->getCurrentScene()->addObject(sphereObject4);
	applic->getCurrentScene()->addObject(plainObject);
	applic->getCurrentScene()->addObject(asObj);
	
	//applic->getCurrentScene()->addObject(floorObject);
	applic->renderCurrentScene();
	

	delete applic;




    return 0;
}

