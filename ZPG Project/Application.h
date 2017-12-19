#pragma once

#include <vector>
#include "Renderer.h"
#include "Scene.h"
#include "Texture.h"

typedef std::map<int, Shader*> ShaderDict;
typedef std::map<int, Texture*> TextureDict;


class Renderer;

class Application
{
public:
	

	
	

	GLFWwindow& getWindow();
	static Application* getInstance();

	
	~Application();

	//Scene
	void createScene(char* sceneName, Shader* shader);
	void renderCurrentScene();
	Scene* getCurrentScene();
	void recalculateSkyBoxPosition();

	//Texture
	void addTexture(std::string path, std::string desription);
	void addTextureWithNormalMap(std::string pathToTexture, std::string desriptionTexture, std::string pathToNormalMap, std::string descriptionNormalMap);
	GLuint getTextureID(int textureKey);
	GLuint getNormalMapTextureID(int textureKey);

	


	//Handlers
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void error_callback(int error, const char* description);
	void window_size_callback(GLFWwindow* window, int width, int height);
	void cursor_pos_callback(GLFWwindow* window, double mouseX, double mouseY);
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	void window_focus_callback(GLFWwindow* window, int focused);
	void window_iconify_callback(GLFWwindow* window, int iconified);
	
	
	

	

private:

	GLFWwindow*	window;
	Scene* currentScene;
	int resolutionX;
	int resolutionY;

	double actualMousePositionX;
	double actualMousePositionY;

	std::vector<Scene*>* scenes;

	
	Renderer * renderer;


	

	TextureDict textureDict;
	TextureDict normalMapTextureDict;
	Texture* normalMap;
	
	
	

	Application();


	


};

