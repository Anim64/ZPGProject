#pragma once
#include "Scene.h"
#include "Application.h"

class Renderer
{
public:
	Renderer(GLFWwindow&);
	void renderScene(Scene&);
private:
	GLFWwindow* window;
	void renderSkyBox(Scene& scene);
	void renderObjects(Scene&);
	void activateObjectTexture(Scene&, int);
};