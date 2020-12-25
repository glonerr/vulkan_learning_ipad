#include "VulkanInstance.h"

VkResult VulkanInstance::createInstance(std::vector<const char *> &layers, std::vector<const char *> extensions, const char *appName)
{
    // 设置实例相关的层和扩展的信息
    layerExtension.appRequestedExtensionNames = extensions;
    layerExtension.appRequestedLayerNames = layers;

    // 定义Vulkan应用程序的结构体
    VkApplicationInfo app_info = {VK_STRUCTURE_TYPE_APPLICATION_INFO, NULL, appName, 1, appName, 1, VK_API_VERSION_1_0};

    // 定义Vulkan实例创建的参数结构体
    VkInstanceCreateInfo instance_ci = {VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO, NULL, 0, &app_info, (uint32_t)layers.size(), layers.size() ? layers.data() : NULL, (uint32_t)extensions.size(), extensions.size() ? extensions.data() : NULL};

    return vkCreateInstance(&instance_ci, NULL, &instance);
}

void VulkanInstance::destoryInstance()
{
    vkDestroyInstance(instance, NULL);
}