#include "baseCode.h"
#include "frameBuffers.h"

void frameBuffers::createFramebuffers()
{
	swapChainFramebuffers.resize(swapChainImageViews.size());
	
	// 为交换链的每一个图像视图对象创建对应的帧缓冲
	for (size_t i = 0; i < swapChainImageViews.size(); i++)
	{
		VkImageView attachments[] =
		{
			swapChainImageViews[i]
		};
		
		VkFramebufferCreateInfo framebufferInfo{};
		framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebufferInfo.renderPass = renderPass;
		// attachmentCount 和 pAttachments 用于指定附着个数
		framebufferInfo.attachmentCount = 1;
		framebufferInfo.pAttachments = attachments;
		// width 和 height 帧缓冲的大小 
		framebufferInfo.width = swapChainExtent.width;
		framebufferInfo.height = swapChainExtent.height;
		// layer 使用的交换图像都是单层，所以 layers 成员变量设置为1
		framebufferInfo.layers = 1;

		if (vkCreateFramebuffer(device, &framebufferInfo, nullptr, &swapChainFramebuffers[i]) != VK_SUCCESS) 
		{
			throw std::runtime_error("failed to create framebuffer!");
		}
	}
}