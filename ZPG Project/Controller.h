#pragma once

#include "stdafx.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <vector>
#include "Camera.h"

class Controller
{
public:
	Controller(GLFWwindow*);
	


	void cursor_pos_callback(GLFWwindow* window, double mouseX, double mouseY);
	void error_callback(int error, const char* description);
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void window_size_callback(GLFWwindow* window, int width, int height);
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	void window_focus_callback(GLFWwindow* window, int focused);
	void window_iconify_callback(GLFWwindow* window, int iconified);

private:
	double actualXPosition;
	double actualYPosition;
	GLFWwindow*	window;

};
