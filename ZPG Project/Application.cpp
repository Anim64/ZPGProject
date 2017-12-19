#include "stdafx.h"
#include "Application.h"

static Application * instance;

GLFWwindow & Application::getWindow()
{
	return *window;
}

Application::Application()
{
	
	
	if (!glfwInit()) {

		fprintf(stderr, "ERROR: could not start GLFW3\n");
		throw std::exception("Could not init GLFW");
	}


	this->resolutionX = 800;
	this->resolutionY = 600;

	this->actualMousePositionX = this->resolutionX / 2;

	this->actualMousePositionY = this->resolutionY / 2;

	window = glfwCreateWindow(this->resolutionX, this->resolutionY, "ZPG", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		throw std::exception("Could not create window");
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();
	

	// get version info
	/*printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&amp; major, &amp; minor, &amp; revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);*/

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	float ratio = width / (float)height;
	glViewport(0, 0, width, height);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_STENCIL_TEST);
	glDepthFunc(GL_LEQUAL);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	scenes = new std::vector<Scene*>();

	renderer = new Renderer(*window);

	addTextureWithNormalMap("./Models/House/test.png", "HouseTexture", "./Models/House/test_normal.png", "NormalMapHouse");
	addTexture("./Models/terrain.jpg", "GrassTerrainTexture");

	//normalMap = TextureLoader::loadTexture("./Models/House/test_normal.png", "NormalMap");

	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) -> void {Application::getInstance()->key_callback(window, key, scancode, action, mods); });

	glfwSetErrorCallback([](int error, const char* description) -> void {Application::getInstance()->error_callback(error, description); });

	glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) -> void {Application::getInstance()->window_size_callback(window, width, height); });

	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double mouseXPos, double mouseYPos) -> void {Application::getInstance()->cursor_pos_callback(window, mouseXPos, mouseYPos); });

	glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) -> void {Application::getInstance()->mouse_button_callback(window, button, action, mods); });

	glfwSetWindowFocusCallback(window, [](GLFWwindow* window, int focused) -> void {Application::getInstance()->window_focus_callback(window, focused); });

	glfwSetWindowIconifyCallback(window, [](GLFWwindow* window, int iconified) -> void {Application::getInstance()->window_iconify_callback(window, iconified); });

	

	
}

Application* Application::getInstance()
{
	if (instance == NULL)
	{
		instance = new Application();
	}
	return instance;
}

Application::~Application()
{
	glfwDestroyWindow(window);
	glfwTerminate();

	for (int i = 0; i < scenes->size(); i++)
	{
		delete scenes->at(i);
	}

	/*for (int i = 1; i < textureDict.size(); i++)
	{
		delete textureDict.at(i);
	}

	for (int i = 1;  normalMapTextureDict.size(); i++)
	{
		delete normalMapTextureDict.at(i);
	}*/

	scenes->clear();
	delete scenes;
	
	delete renderer;
}

void Application::createScene(char* name, Shader* shader)
{
	Scene* scene = new Scene(name, shader);
	scenes->push_back(scene);

	currentScene = scene;


}

void Application::renderCurrentScene()
{
	renderer->renderScene(*currentScene);
	
}

Scene* Application::getCurrentScene()
{
	
	return currentScene;
}




void Application::addTexture(std::string path, std::string description)
{
	Texture* texture = TextureLoader::loadTexture(path, description);

	int key = textureDict.size() + 1;

	this->textureDict[key] = texture;
	this->normalMapTextureDict[key] = NULL;



}

void Application::addTextureWithNormalMap(std::string pathToTexture, std::string desriptionTexture, std::string pathToNormalMap, std::string descriptionNormalMap)
{
	Texture * texture = TextureLoader::loadTexture(pathToTexture, desriptionTexture);
	Texture * normalMap = TextureLoader::loadTexture(pathToNormalMap, descriptionNormalMap);

	int key = textureDict.size() + 1;
	this->textureDict[key] = texture;
	this->normalMapTextureDict[key] = normalMap;

	
}

GLuint Application::getTextureID(int textureKey)
{
	
	return this->textureDict.find(textureKey)->second->getTextureID();
}

GLuint Application::getNormalMapTextureID(int textureKey)
{

	if (this->normalMapTextureDict.find(textureKey)->second == NULL)
	{
		return UINT_MAX;
	}

	else 
	{
		return this->normalMapTextureDict.find(textureKey)->second->getTextureID();
	}
	
}

void Application::error_callback(int error, const char* description) {
	fputs(description, stderr);
}

void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	
	if (key == GLFW_KEY_A)
	{
		this->currentScene->getCamera()->strafeLeft();
		recalculateSkyBoxPosition();
	}
		

	if (key == GLFW_KEY_D)
	{
		this->currentScene->getCamera()->strafeRight();
		recalculateSkyBoxPosition();
		
	}

	if (key == GLFW_KEY_W)
	{
		this->currentScene->getCamera()->forward();
		recalculateSkyBoxPosition();
		
	}

	if (key == GLFW_KEY_S)
	{
		this->currentScene->getCamera()->backward();
		recalculateSkyBoxPosition();
		
	}

}

void Application::recalculateSkyBoxPosition()
{
	glm::vec3 cameraPosition = this->currentScene->getCamera()->getPosition();

	glm::vec3 skyBoxPosition = this->currentScene->getSkyBox()->getPosition();
	//Distance from camera to SkyBox
	glm::vec3 difference = (cameraPosition - skyBoxPosition);

	this->currentScene->getSkyBox()->translate(difference);

	this->currentScene->getSkyBox()->setPosition(cameraPosition);
}

void Application::window_size_callback(GLFWwindow* window, int width, int height) {
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}

void Application::cursor_pos_callback(GLFWwindow* window, double mouseX, double mouseY) {
	//printf("cursor_pos_callback %d, %d \n", (int)mouseX, (int)mouseY);

	this->actualMousePositionX = mouseX;
	this->actualMousePositionY = mouseY;

	this->currentScene->getCamera()->mouseUpdate(mouseX, mouseY);
	glfwSetCursorPos(window, this->resolutionX / 2, this ->resolutionY / 2);

}

void Application::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	//printf("mouse_button_callback %d, %d, %d \n", button, action, mods);

	GLbyte color[4];
	GLfloat depth;
	GLuint index;

	GLint x = (GLint)this->actualMousePositionX;
	GLint y = (GLint)this->actualMousePositionY;



	int newy = this->resolutionY - y;

	glReadPixels(x, newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
	glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
	glReadPixels(x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

	printf("Clicked on pixel %d, %d, color % 02hhx % 02hhx % 02hhx % 02hhx, depth %f, stencil index %u\n", x, y, color[0], color[1], color[2], color[3], depth, index);

	currentScene->deleteObject(index);

	//Application::getInstance()->getScene()->getRenderer()->setSelect(index-1);


	glm::vec3 screenX = glm::vec3(x, newy, depth);
	glm::mat4& view = Application::getInstance()->currentScene->getCamera()->getViewMatrix();
	glm::mat4& projection = Application::getInstance()->currentScene->getCamera()->getProjectionMatrix();

	glm::vec4& viewPort = glm::vec4(0, 0,
		this->resolutionX,
		this->resolutionY);
	glm::vec3 pos = glm::unProject(screenX, view, projection, viewPort);

	printf("unProject[%f, %f, %f]\n", pos.x, pos.y, pos.z);
}

void Application::window_focus_callback(GLFWwindow* window, int focused) {
	printf("window_focus_callback %d \n", focused);
}

void Application::window_iconify_callback(GLFWwindow* window, int iconified) {
	printf("window_iconify_callback %d \n", iconified);
}


