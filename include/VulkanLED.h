#pragma once
#include "header.h"
#include <vector>
struct LayerProperties
{
    VkLayerProperties properties;
    std::vector<VkExtensionProperties> extensions;
};

class VulkanLayerAndExtension
{
public:
    VulkanLayerAndExtension();
    ~VulkanLayerAndExtension();

    // 应用程序中所需用到的层的名称列表
    std::vector<const char *> appRequestedLayerNames;

    // 应用程序中所需用到的扩展的名称列表
    std::vector<const char *> appRequestedExtensionNames;

    // 层和对应的扩展列表
    std::vector<LayerProperties> layerPropertylist;

    // 获取实力/全局层
    VkResult getInstanceLayerProperties();

    // 全局扩展
    VkResult getExtensionProperties(LayerProperties &layerProps, VkPhysicalDevice *gpu = NULL);

    // 设备扩展
    VkResult getDeviceExtensionProperties(VkPhysicalDevice *gpu);
};
