#pragma once

#include <volk.h>
#include <vulkan/vulkan.h>

#include <string>
#include <iostream>
#include <vector>
#include <cassert>


void check_vk_result(VkResult result);

//VkDebugUtilsMessengerCreateInfoEXT getDebugUtilsCreateInfo();

std::vector<const char*> gatherLayers(
    const char* const* requiredLayers,
    uint32_t requiredLayersCount,
    VkLayerProperties* availableLayers,
    uint32_t availableLayersCount
);

std::vector<const char*> gatherExtensions(
    const char* const* requiredExtensions,
    uint32_t requiredExtensionsCount,
    VkExtensionProperties* availableExtensions,
    uint32_t availableExtensionsCount
);

VkInstance createInstance(uint32_t layersCount, const char** layerNames,
    uint32_t extensionsCount, const char** extensionNames);

VkDebugUtilsMessengerEXT createDebugUtilsMessenger(VkInstance instance);