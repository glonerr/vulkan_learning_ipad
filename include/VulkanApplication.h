#pragma once
#include "VulkanInstance.h"
#include "VulkanLED.h"
#include <memory>
#include <mutex>

class VulkanApplication{
private:
VulkanApplication();
public:
~VulkanApplication();

private:
std::unique_ptr<VulkanApplication> instance;
std::once_flag onlyOnce;

public:
static VulkanApplication GetInstance();

// 初始化并分配资源
void initialize();
// 准备资源
void prepare();
// 更新数据
void update();
// 渲染
bool render();
// 反初始化
void deInitialize();

private:
// 创建Vulkan实例对象
VkResult createVulkanInstance(std::vector<const char*> layers,std::vector<const char*> &extensions,const char* applicationName);
VkResult handShakeWithDevice(VkPhysicalDevice *gpu,std::vector<const char*>&layers,std::vector<const char*>&extensions);
};
