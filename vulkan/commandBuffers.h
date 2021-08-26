#pragma once

#include <iostream>

class commandBuffer
{
public:
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

	void createCommandPool();
	
	void createCommandBuffers();
};