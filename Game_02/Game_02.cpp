#include <vulkan/vulkan.h>
#include <volk.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <iostream>
#include <cassert>

#include "utils.hpp"

static const int WIDTH		= 1280;
static const int HEIGHT		= 720;
static const char* APP_NAME = "Game_02";

GLFWwindow* Window						= nullptr;
VkInstance Instance						= VK_NULL_HANDLE;
VkDebugUtilsMessengerEXT DebugMessenger = VK_NULL_HANDLE;
VkPhysicalDevice PhysicalDevice			= VK_NULL_HANDLE;

static void glfw_error_callback(int code, const char* const description) {
	fprintf(stderr, "[glfw] %d : %s\n", code, description);
}

void SetupVulkan(uint32_t layersCount, const char** layerNames,
	uint32_t extensionsCount, const char** extensionNames) 
{
	Instance = createInstance(layersCount, layerNames, extensionsCount, extensionNames);
	DebugMessenger = createDebugUtilsMessenger(Instance);

	// Select Physical Device
	{
		uint32_t NumGPUs = 0;
		vkEnumeratePhysicalDevices(Instance, &NumGPUs, nullptr);
		std::vector<VkPhysicalDevice> GPUs(NumGPUs);
		vkEnumeratePhysicalDevices(Instance, &NumGPUs, GPUs.data());

		for (const auto& GPU : GPUs) {

			VkPhysicalDeviceProperties properties;

			vkGetPhysicalDeviceProperties(GPU, &properties);

			if (properties.deviceType & VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
				PhysicalDevice = GPU;
				break;
			}
		}

		if (PhysicalDevice == VK_NULL_HANDLE)
			PhysicalDevice = GPUs.front();
	
	}

	// Create Logical Device
	{

		



	}

}

int Init() {

	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
		return 1;

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	Window = glfwCreateWindow(WIDTH, HEIGHT, APP_NAME, nullptr, nullptr);
	if (!Window)
		return 1;

	uint32_t glfw_extension_count = 0;
	const char** glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extension_count);
	SetupVulkan(0, nullptr, glfw_extension_count, glfw_extensions);

	return 0;
}

void Update() {
	glfwPollEvents();
}

void Terminate() {

	if (Instance != VK_NULL_HANDLE) {
		if (DebugMessenger != VK_NULL_HANDLE) {
			vkDestroyDebugUtilsMessengerEXT(Instance, DebugMessenger, nullptr);
		}
		vkDestroyInstance(Instance, nullptr);
	}

	glfwDestroyWindow(Window);
	glfwTerminate();
}

int main()
{
	if (Init()) {
		Terminate();
		return EXIT_FAILURE;
	}

	while (!glfwWindowShouldClose(Window)) {
		Update();
	}

	Terminate();
	return EXIT_SUCCESS;
}
