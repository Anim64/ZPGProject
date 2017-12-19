
#include "stdafx.h"
#include "Controller.h"







void Controller::error_callback(int error, const char* description) {
	fputs(description, stderr);
}

void Controller::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}

void Controller::window_size_callback(GLFWwindow* window, int width, int height) {
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}

void Controller::cursor_pos_callback(GLFWwindow* window, double mouseX, double mouseY) {
	printf("cursor_pos_callback %d, %d \n", (int)mouseX, (int)mouseY);

}

void Controller::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	printf("mouse_button_callback %d, %d, %d \n", button, action, mods);
}

void Controller::window_focus_callback(GLFWwindow* window, int focused) {
	printf("window_focus_callback %d \n", focused);
}

void Controller::window_iconify_callback(GLFWwindow* window, int iconified) {
	printf("window_iconify_callback %d \n", iconified);
}



