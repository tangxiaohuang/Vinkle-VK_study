#include "baseCode.h"
#include "frameBuffers.h"

void frameBuffers::createFramebuffers()
{
	swapChainFramebuffers.resize(swapChainImageViews.size());
	
	// Ϊ��������ÿһ��ͼ����ͼ���󴴽���Ӧ��֡����
	for (size_t i = 0; i < swapChainImageViews.size(); i++)
	{
		VkImageView attachments[] =
		{
			swapChainImageViews[i]
		};
		
		VkFramebufferCreateInfo framebufferInfo{};
		framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebufferInfo.renderPass = renderPass;
		// attachmentCount �� pAttachments ����ָ�����Ÿ���
		framebufferInfo.attachmentCount = 1;
		framebufferInfo.pAttachments = attachments;
		// width �� height ֡����Ĵ�С 
		framebufferInfo.width = swapChainExtent.width;
		framebufferInfo.height = swapChainExtent.height;
		// layer ʹ�õĽ���ͼ���ǵ��㣬���� layers ��Ա��������Ϊ1
		framebufferInfo.layers = 1;

		if (vkCreateFramebuffer(device, &framebufferInfo, nullptr, &swapChainFramebuffers[i]) != VK_SUCCESS) 
		{
			throw std::runtime_error("failed to create framebuffer!");
		}
	}
}