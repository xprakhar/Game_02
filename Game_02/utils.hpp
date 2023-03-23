#pragma once

#include <vulkan/vulkan.h>

#include <string>
#include <iostream>

std::string EIV_GetMessageSeverity(VkDebugUtilsMessageSeverityFlagBitsEXT severity) {
    switch (severity) {
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
        return "Error";
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
        return "Warning";
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
        return "Info";
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
        return "Verbose";
    }

    return "";
}

std::string EIV_GetMessageTypes(VkDebugUtilsMessageTypeFlagsEXT types) {
    std::string out;
    if (types & VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT) {
        out = out.length() > 0 ? out + "General" : out + " | General";
    }
    if (types & VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT) {
        out = out.length() > 0 ? out + "Performace" : out + " | Performace";
    }
    if (types & VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT) {
        out = out.length() > 0 ? out + "Validation" : out + " | Validation";
    }

    return out;
}

static VKAPI_ATTR VkBool32 VKAPI_CALL Eagle_DebugCallack(
	VkDebugUtilsMessageSeverityFlagBitsEXT severity,
	VkDebugUtilsMessageTypeFlagsEXT types,
	const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
	void* pUserData
) {

#if !defined( NDEBUG )

    if (pCallbackData->messageIdNumber == 648835635)
    {
        // UNASSIGNED-khronos-Validation-debug-build-warning-message
        return VK_FALSE;
    }
    if (pCallbackData->messageIdNumber == 767975156)
    {
        // UNASSIGNED-BestPractices-vkCreateInstance-specialuse-extension
        return VK_FALSE;
    }
#endif
    std::cerr << EIV_GetMessageSeverity(severity) << ": "
        << EIV_GetMessageTypes(types) << ":\n";
    std::cerr << std::string("\t") << "messageIDName   = <" << pCallbackData->pMessageIdName << ">\n";
    std::cerr << std::string("\t") << "messageIdNumber = " << pCallbackData->messageIdNumber << "\n";
    std::cerr << std::string("\t") << "message         = <" << pCallbackData->pMessage << ">\n";
    if (0 < pCallbackData->queueLabelCount)
    {
        std::cerr << std::string("\t") << "Queue Labels:\n";
        for (uint32_t i = 0; i < pCallbackData->queueLabelCount; i++)
        {
            std::cerr << std::string("\t\t") << "labelName = <" << pCallbackData->pQueueLabels[i].pLabelName << ">\n";
        }
    }
    if (0 < pCallbackData->cmdBufLabelCount)
    {
        std::cerr << std::string("\t") << "CommandBuffer Labels:\n";
        for (uint32_t i = 0; i < pCallbackData->cmdBufLabelCount; i++)
        {
            std::cerr << std::string("\t\t") << "labelName = <" << pCallbackData->pCmdBufLabels[i].pLabelName << ">\n";
        }
    }
    if (0 < pCallbackData->objectCount)
    {
        std::cerr << std::string("\t") << "Objects:\n";
        for (uint32_t i = 0; i < pCallbackData->objectCount; i++)
        {
            std::cerr << std::string("\t\t") << "Object " << i << "\n";
            //std::cerr << std::string("\t\t\t") << "objectType   = " << vk::to_string(static_cast<vk::ObjectType>(pCallbackData->pObjects[i].objectType))
               // << "\n";
            std::cerr << std::string("\t\t\t") << "objectHandle = " << pCallbackData->pObjects[i].objectHandle << "\n";
            if (pCallbackData->pObjects[i].pObjectName)
            {
                std::cerr << std::string("\t\t\t") << "objectName   = <" << pCallbackData->pObjects[i].pObjectName << ">\n";
            }
        }
    }
    return VK_TRUE;
}