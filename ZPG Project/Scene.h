#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <vector>
#include <map>

#include "Object.h"
#include "Shader.h"
#include "Camera.h"
#include "Light.h"
#include "Texture.h"
#include "TextureLoader.h"
#include "SkyBox.h"
#include "Factory.h"

//#include "Controller.h"


typedef std::map<int, Shader*> ShaderDict;

class Scene
{
public:
	char* sceneName;

	Scene(char*, Shader*);
	~Scene();

	Shader* getShader();
	std::vector<Object*>* getObjects();
	Camera* getCamera();
	SkyBox* getSkyBox();
	

	void changeShader(int);

	void addObject(Object*);
	//void addObject(std::vector<float>, int);

	void addLight(Light);
	void setAllLights();

	void addShader(Shader*);

	void deleteObject(int index);

private:
	std::vector<Object*>* objects;
	Shader* currentShader;
	Camera* camera;
	ShaderDict shaderDictionary;
	vector<Light> lights;
	Texture* skyBoxTexture;
	SkyBox * skyBoxObject;
	
	Factory * factory;
	
	
};