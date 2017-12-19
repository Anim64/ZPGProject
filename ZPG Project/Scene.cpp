#include "stdafx.h"
#include "Scene.h"
#include <stdexcpt.h>

Scene::Scene(char* sceneName, Shader* shader)
{
	factory = new Factory();

	this->sceneName = sceneName;

	//Shader * shaderColour = new Shader("./VertexShaderColour.glsl", "./FragmentShaderColour.glsl");
	Shader * shaderTexture = new Shader("./VertexShaderTexture.glsl", "./FragmentShaderTexture.glsl");
	Shader* skyBoxShader = new Shader("./VertexShaderSkybox.glsl", "./FragmentShaderSkybox.glsl");

	

	this->currentShader = skyBoxShader;
	currentShader->setShader();

	

	this->camera = factory->createCamera(glm::vec3(0,0,0), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));

	
	//addShader(shaderColour);
	addShader(shaderTexture);
	addShader(skyBoxShader);
	

	
	
	objects = new std::vector<Object*>();

	LightStruct spotlight;
	spotlight.position = glm::vec4(1, 7, 0, 1);
	spotlight.intensities = glm::vec3(2.0, 2.0, 2.0); //strong white light
	spotlight.attenuation = 0.1f;
	spotlight.ambientCoefficient = 0.0f; //no ambient light
	spotlight.coneAngle = 15.0f;
	spotlight.coneDirection = glm::vec3(0, -1, 0);

	LightStruct directionalLight;
	directionalLight.position = glm::vec4(1, 5, 0, 0); //w == 0 indications a directional light
	directionalLight.intensities = glm::vec3(0.4, 0.4, 0.4); //weak yellowish light
	directionalLight.ambientCoefficient = 1.0;
	
	Light light(spotlight);
	Light light2(directionalLight);

	addLight(light);
	addLight(light2);
	

	
	setAllLights();

	vector<std::string> pathsToSkyBoxImages;
	pathsToSkyBoxImages.push_back("./Models/Skybox/cubemap/posx.jpg");
	pathsToSkyBoxImages.push_back("./Models/Skybox/cubemap/negx.jpg");
	pathsToSkyBoxImages.push_back("./Models/Skybox/cubemap/posy.jpg");
	pathsToSkyBoxImages.push_back("./Models/Skybox/cubemap/negy.jpg");
	pathsToSkyBoxImages.push_back("./Models/Skybox/cubemap/posz.jpg");
	pathsToSkyBoxImages.push_back("./Models/Skybox/cubemap/negz.jpg");

	skyBoxTexture = TextureLoader::loadSkyBoxTextures(pathsToSkyBoxImages);
	skyBoxObject = new SkyBox("./Models/Skybox/skybox.obj", 2, skyBoxTexture->getTextureID());

	//skyBoxObject->scale(20.0f);

	//addObject(skyBoxObject);
	
}

Scene::~Scene()
{
	for (int i = 0; i < objects->size(); i++)
	{
		delete objects->at(i);
	}

	objects->clear();
	delete objects;
	delete currentShader;
	delete camera;
	delete factory;
	delete skyBoxObject;
	delete skyBoxTexture;

}

void Scene::addObject(Object* obj)
{
	
	obj->setID(objects->size() + 1);
	objects->push_back(obj);
}



/*void Scene::addObject(std::vector<float> vec, int shaderKey)
{
	objects->push_back(new Object(vec, shaderKey));
}*/

std::vector<Object*>* Scene::getObjects()
{
	return objects;
}

Shader * Scene::getShader()
{
	
	return this->currentShader;
}

Camera* Scene::getCamera()
{
	return this->camera;
}

void Scene::deleteObject(int index)
{
	for (int i = 0; i < objects->size(); i++)
	{
		if (objects->at(i)->getID() == index)
		{
			objects->at(i)->deleteObject(index);
		}
	}
}




void Scene::changeShader(int shaderKey)
{
	this->currentShader = this->shaderDictionary.find(shaderKey)->second;
	this->currentShader->setShader();
	
}


// Adds Shader to Shader dictionary
void Scene::addShader(Shader* shader)
{
	int key = this->shaderDictionary.size() + 1;

	this->shaderDictionary[key] = shader;
	this->camera->addObserver(shader);
	this->camera->forceNotify();
	//this->light->addObserver(shader);
	

}

void Scene::addLight(Light light)
{
	if (this->lights.size() >= 10)
	{
		printf("Svetla jsou plne");
		return;
	}
	this->lights.push_back(light);
}

void Scene::setAllLights()
{
	for (int i = 1; i <= this->shaderDictionary.size(); i++)
	{
		this->shaderDictionary.find(i)->second->setAllLights(this->lights);
	}
}

SkyBox* Scene::getSkyBox()
{
	return this->skyBoxObject;
}

