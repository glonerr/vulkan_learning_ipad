#include "VulkanLED.h"
#include <iostream>

VulkanLayerAndExtension::VulkanLayerAndExtension() {}

VulkanLayerAndExtension::~VulkanLayerAndExtension() {}

VkResult VulkanLayerAndExtension::getInstanceLayerProperties()
{
    // 存储实例层的数目
    uint32_t instanceLayerCount;
    // 通过向量组来存储层的属性
    std::vector<VkLayerProperties> layerProperties;
    // 检查Vulkan API的执行结果
    VkResult result;

    // 查询所有的层
    do
    {
        result = vkEnumerateInstanceLayerProperties(&instanceLayerCount, NULL);
        if (result)
            return result;
        if (instanceLayerCount == 0)
            return VK_INCOMPLETE;
        layerProperties.resize(instanceLayerCount);
        result = vkEnumerateInstanceLayerProperties(&instanceLayerCount, layerProperties.data());
    } while (result == VK_INCOMPLETE);

    // 查询每个层的所有扩展，并进行保存
    std::cout << "\nInstanced Layers" << std::endl;
    std::cout << "==================" << std::endl;
    for (auto globalLayerProp : layerProperties)
    {
        // 显示层的名字和描述信息
        std::cout << "\n"
                  << globalLayerProp.description << "\n\t|\n\t---[Layer Name]---> " << globalLayerProp.layerName << "\n";

        LayerProperties layerProps;
        layerProps.properties = globalLayerProp;

        // 根据层属性信息，获取基于实例的扩展
        result = getExtensionProperties(layerProps);

        if (result)
        {
            continue;
        }

        layerPropertylist.push_back(layerProps);
    }
    return result;
}

VkResult VulkanLayerAndExtension::getExtensionProperties(LayerProperties &layerProps, VkPhysicalDevice *gpu)
{
    // 保存每一层的扩展总数
    uint32_t extensionCount;
    VkResult result;

    // 层的名称
    char *layerName = layerProps.properties.layerName;

    do
    {
        // 获取当前层中的扩展总数
        if (gpu)
        {
            result = vkEnumerateDeviceExtensionProperties(*gpu, layerName, &extensionCount, NULL);
        }
        else
        {
            result = vkEnumerateInstanceExtensionProperties(layerName, &extensionCount, NULL);
        }

        if (result || extensionCount == 0)
            continue;

        layerProps.extensions.resize(extensionCount);

        if (gpu)
        {
            result = vkEnumerateDeviceExtensionProperties(*gpu, layerName, &extensionCount, layerProps.extensions.data());
        }
        else
        {
            result = vkEnumerateInstanceExtensionProperties(layerName, &extensionCount, layerProps.extensions.data());
        }
        
        
    } while (result == VK_INCOMPLETE);

    return result;
}

VkResult VulkanLayerAndExtension::getDeviceExtensionProperties(VkPhysicalDevice *gpu)
{
    VkResult result;
    return result;
}