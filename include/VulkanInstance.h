#pragma once
#include "header.h"
#include "VulkanLED.h"

class VulkanInstance
{
    // Vulkan实例对象的变量
    VkInstance instance;

    // Vulkan相关的层和扩展
    VulkanLayerAndExtension layerExtension;

public:
    // 用来创建和删除Vulkan实例的函数
    VkResult createInstance(std::vector<const char *> &layers, std::vector<const char *> extensions, const char *applicationName);

    // 销毁Vulkan实例
    void destoryInstance();
};