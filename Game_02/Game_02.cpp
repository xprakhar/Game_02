#include <iostream>

#include <vulkan/vulkan.h>
#include <volk.h>
#include <GLFW/glfw3.h>

static const int WIDTH		= 1280;
static const int HEIGHT		= 720;
static const char* APP_NAME = "Game_02";

int main()
{
	if (!glfwInit())
		return 1;

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, APP_NAME, nullptr, nullptr);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
