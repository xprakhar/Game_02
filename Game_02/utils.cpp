#include "utils.hpp"


void check_vk_result(VkResult result) {
    if (result == 0)
        return;
    fprintf(stderr, "[vulkan] Error VkResult = %d", result);
    if (result < 0)
        abort();
}

static std::string messageSeverityToString(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity)
{
    switch (messageSeverity)
    {
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
        return "Verbose";
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
        return "Information";
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
        return "Warning";
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
        return "Error";
    default:
        return "Unknown";
    }
}


static std::string messageTypeToString(VkDebugUtilsMessageTypeFlagsEXT messageType)
{
    std::string result;
    if (messageType & VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT)
    {
        result += "General ";
    }
    if (messageType & VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT)
    {
        result += "Validation ";
    }
    if (messageType & VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT)
    {
        result += "Performance ";
    }
    return result;
}


static std::string objectTypeToString(VkObjectType objectType)
{
    switch (objectType)
    {
    case VK_OBJECT_TYPE_INSTANCE: return "Instance";
    case VK_OBJECT_TYPE_PHYSICAL_DEVICE: return "PhysicalDevice";
    case VK_OBJECT_TYPE_DEVICE: return "Device";
    case VK_OBJECT_TYPE_QUEUE: return "Queue";
    case VK_OBJECT_TYPE_SEMAPHORE: return "Semaphore";
    case VK_OBJECT_TYPE_COMMAND_BUFFER: return "CommandBuffer";
    case VK_OBJECT_TYPE_FENCE: return "Fence";
    case VK_OBJECT_TYPE_DEVICE_MEMORY: return "DeviceMemory";
    case VK_OBJECT_TYPE_BUFFER: return "Buffer";
    case VK_OBJECT_TYPE_IMAGE: return "Image";
    case VK_OBJECT_TYPE_EVENT: return "Event";
    case VK_OBJECT_TYPE_QUERY_POOL: return "QueryPool";
    case VK_OBJECT_TYPE_BUFFER_VIEW: return "BufferView";
    case VK_OBJECT_TYPE_IMAGE_VIEW: return "ImageView";
    case VK_OBJECT_TYPE_SHADER_MODULE: return "ShaderModule";
    case VK_OBJECT_TYPE_PIPELINE_CACHE: return "PipelineCache";
    case VK_OBJECT_TYPE_PIPELINE_LAYOUT: return "PipelineLayout";
    case VK_OBJECT_TYPE_RENDER_PASS: return "RenderPass";
    case VK_OBJECT_TYPE_PIPELINE: return "Pipeline";
    case VK_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT: return "DescriptorSetLayout";
    case VK_OBJECT_TYPE_SAMPLER: return "Sampler";
    case VK_OBJECT_TYPE_DESCRIPTOR_POOL: return "DescriptorPool";
    case VK_OBJECT_TYPE_DESCRIPTOR_SET: return "DescriptorSet";
    case VK_OBJECT_TYPE_FRAMEBUFFER: return "Framebuffer";
    case VK_OBJECT_TYPE_COMMAND_POOL: return "CommandPool";
    default: return "Unknown";
    }
}



static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
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
    std::cerr << "[--------------------Debug Utils Output Begin -------------]\n";
    std::cerr << std::string("\t") << "Severity        = " << messageSeverityToString(severity) << "\n";
    std::cerr << std::string("\t") << "Type            = " << messageTypeToString(types) << "\n";
    std::cerr << std::string("\t") << "messageIDName   = <" << pCallbackData->pMessageIdName << ">\n";
    std::cerr << std::string("\t") << "messageIdNumber = " << pCallbackData->messageIdNumber << "\n";
    std::cerr << std::string("\t") << "message         = <" << pCallbackData->pMessage << ">\n";
    if (0 < pCallbackData->queueLabelCount)
    {
        std::cerr << std::string("\t") << "Queue Labels:\n";
        for (uint32_t i = 0; i < pCallbackData->queueLabelCount; i++)
        {
            VkDebugUtilsLabelEXT const& queueLabel = pCallbackData->pQueueLabels[i];
            std::cerr << std::string("\t\t") << "labelName = <" << queueLabel.pLabelName << ">\n";
        }
    }
    if (0 < pCallbackData->cmdBufLabelCount)
    {
        std::cerr << std::string("\t") << "CommandBuffer Labels:\n";
        for (uint32_t i = 0; i < pCallbackData->cmdBufLabelCount; i++)
        {
            VkDebugUtilsLabelEXT const& cmdBufLabel = pCallbackData->pCmdBufLabels[i];
            std::cerr << std::string("\t\t") << "labelName = <" << cmdBufLabel.pLabelName << ">\n";
        }
    }
    if (0 < pCallbackData->objectCount)
    {
        std::cerr << std::string("\t") << "Objects:\n";
        for (uint32_t i = 0; i < pCallbackData->objectCount; i++)
        {
            std::cerr << std::string("\t\t") << "Object " << i << "\n";
            std::cerr << std::string("\t\t\t") << "objectType   = " << objectTypeToString(pCallbackData->pObjects[i].objectType) << "\n";
            std::cerr << std::string("\t\t\t") << "objectHandle = " << pCallbackData->pObjects[i].objectHandle << "\n";
            if (pCallbackData->pObjects[i].pObjectName)
            {
                std::cerr << std::string("\t\t\t") << "objectName   = <" << pCallbackData->pObjects[i].pObjectName << ">\n";
            }
        }
    }
    std::cerr << "[--------------------Debug Utils Output End -------------]\n\n";

    return VK_TRUE;
}

VkDebugUtilsMessengerCreateInfoEXT getDebugUtilsCreateInfo() {

    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
    debugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    debugCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    debugCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    debugCreateInfo.pfnUserCallback = debugCallback;

    return debugCreateInfo;
}

std::vector<const char*> gatherLayers(
    const char* const* requiredLayers,
    uint32_t requiredLayersCount,
    VkLayerProperties* availableLayers,
    uint32_t availableLayersCount) {

    auto enabledLayers = std::vector<const char*>();
    for (uint32_t i = 0; i < requiredLayersCount; ++i) {
        bool found = false;
        for (uint32_t j = 0; j < availableLayersCount; ++j) {
            if (strcmp(requiredLayers[i], availableLayers[j].layerName) == 0) {
                found = true;
                break;
            }
        }

        if (found) {
            enabledLayers.push_back(requiredLayers[i]);
        }
    }

#if !defined (NDEBUG)

    bool found = false;
    const char* validationLayer = "VK_LAYER_KHRONOS_validation";

    for (uint32_t i = 0; i < requiredLayersCount; ++i) {
        if (strcmp(validationLayer, requiredLayers[i]) == 0) {
            found = true;
            break;
        }
    }

    if (!found) {
        for (uint32_t i = 0; i < availableLayersCount; ++i) {
            if (strcmp(validationLayer, availableLayers[i].layerName) == 0) {
                enabledLayers.push_back(validationLayer);
                break;
            }
        }
    }
#endif


    return enabledLayers;
}

std::vector<const char*> gatherExtensions(
    const char* const* requiredExtensions,
    uint32_t requiredExtensionsCount,
    VkExtensionProperties* availableExtensions,
    uint32_t availableExtensionsCount) {

    auto enabledExtensions = std::vector<const char*>();
    for (uint32_t i = 0; i < requiredExtensionsCount; ++i) {
        bool found = false;
        for (uint32_t j = 0; j < availableExtensionsCount; ++j) {
            if (strcmp(requiredExtensions[i], availableExtensions[j].extensionName) == 0) {
                found = true;
                break;
            }
        }

        if (found) {
            enabledExtensions.push_back(requiredExtensions[i]);
        }
    }

#if !defined (NDEBUG)

    bool found = false;
    const char* debugExtension = VK_EXT_DEBUG_UTILS_EXTENSION_NAME;

    for (uint32_t i = 0; i < requiredExtensionsCount; ++i) {
        if (strcmp(debugExtension, requiredExtensions[i]) == 0) {
            found = true;
            break;
        }
    }

    if (!found) {
        for (uint32_t i = 0; i < availableExtensionsCount; ++i) {
            if (strcmp(debugExtension, availableExtensions[i].extensionName) == 0) {
                enabledExtensions.push_back(debugExtension);
                break;
            }
        }
    }
#endif


    return enabledExtensions;
}

VkDebugUtilsMessengerEXT createDebugUtilsMessenger(VkInstance instance) {
    VkDebugUtilsMessengerEXT messenger;
    VkDebugUtilsMessengerCreateInfoEXT messenger_ci = getDebugUtilsCreateInfo();
    VkResult res = vkCreateDebugUtilsMessengerEXT(instance, &messenger_ci, nullptr, &messenger);
    check_vk_result(res);
    return messenger;
}

VkInstance createInstance(uint32_t layersCount, const char** layerNames,
    uint32_t extensionsCount, const char** extensionNames) {

    VkResult res = volkInitialize();
    check_vk_result(res);

    VkInstanceCreateInfo instance_ci{};
    instance_ci.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;

#if !defined (NDEBUG)
    VkDebugUtilsMessengerCreateInfoEXT messenger_ci = getDebugUtilsCreateInfo();
    instance_ci.pNext = &messenger_ci;
#endif

    uint32_t availableLayersCount = 0;
    res = vkEnumerateInstanceLayerProperties(&availableLayersCount, nullptr);
    check_vk_result(res);
    assert(availableLayersCount > 0);
    std::vector<VkLayerProperties> availableLayers(availableLayersCount);
    res = vkEnumerateInstanceLayerProperties(&availableLayersCount, availableLayers.data());
    check_vk_result(res);
    auto layers = gatherLayers(layerNames, layersCount, availableLayers.data(), availableLayersCount);
    instance_ci.enabledLayerCount = static_cast<uint32_t>(layers.size());
    instance_ci.ppEnabledLayerNames = layers.data();

    uint32_t availableExtensionsCount = 0;
    res = vkEnumerateInstanceExtensionProperties(nullptr, &availableExtensionsCount, nullptr);
    check_vk_result(res);
    assert(availableExtensionsCount > 0);
    std::vector<VkExtensionProperties> availableExtensions(availableExtensionsCount);
    res = vkEnumerateInstanceExtensionProperties(nullptr, &availableExtensionsCount, availableExtensions.data());
    check_vk_result(res);
    auto extensions = gatherExtensions(extensionNames, extensionsCount, availableExtensions.data(), availableExtensions.size());
    instance_ci.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    instance_ci.ppEnabledExtensionNames = extensions.data();

    VkInstance instance;
    res = vkCreateInstance(&instance_ci, nullptr, &instance);
    check_vk_result(res);

    volkLoadInstanceOnly(instance);

    return instance;
}