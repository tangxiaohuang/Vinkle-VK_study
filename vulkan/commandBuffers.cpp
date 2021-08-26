#include "baseCode.h"
#include "commandBuffers.h"

// ָ��صĸ�����ڹ���ָ������ʹ�õ��ڴ棬������ָ������ķ���
void commandBuffer::createCommandPool()
{
    QueueFamilyIndices queueFamilyIndices = findQueueFamilies(physicalDevice);

    VkCommandPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();

    if (vkCreateCommandPool(device, &poolInfo, nullptr, &commandPool) != VK_SUCCESS) 
    {
        throw std::runtime_error("failed to create command pool!");
    }
}

// Ϊÿ��ͼ�����һ��ָ������
void commandBuffer::createCommandBuffers()
{
	commandBuffers.resize(swapChainFramebuffers.size());

	VkCommandBufferAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = commandPool;
    // level ����ָ�������ָ����������Ҫָ�������Ǹ���ָ������
    // VK_COMMAND_BUFFER_LEVEL_PRIMARY��     ���Ա��ύ�����н���ִ�У������ܱ�����ָ��������á�
    // VK_COMMAND_BUFFER_LEVEL_SECONDARY��   ����ֱ�ӱ��ύ�����н���ִ�У������Ա���Ҫָ���������ִ�С�
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = (uint32_t)commandBuffers.size();

	if (vkAllocateCommandBuffers(device, &allocInfo, commandBuffers.data()) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to allocate command buffers!");
	}

    // ��¼ָ�ָ���
    for (size_t i = 0; i < commandBuffers.size(); i++) {
        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        //���ﻹ��һ�� beginInfo.flags ����ָ�����ǽ�Ҫ����ʹ��ָ���
        // VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT��         ָ�����ִ��һ�κ󣬾ͱ�������¼�µ�ָ�
        // VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT��    ����һ��ֻ��һ����Ⱦ������ʹ�õĸ���ָ��塣
        // VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT��        ��ָ���ȴ�ִ��ʱ����Ȼ�����ύ��һָ��塣

        // vkBeginCommandBuffer����������ָ������
        if (vkBeginCommandBuffer(commandBuffers[i], &beginInfo) != VK_SUCCESS) {
            throw std::runtime_error("failed to begin recording command buffer!");
        }

        // ��ʼ��Ⱦ����
        VkRenderPassBeginInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        // renderPass   ����ָ��ʹ�õ���Ⱦ���̶���
        renderPassInfo.renderPass = renderPass;
        // framebuffer  ����ָ��ʹ�õ�֡�������
        renderPassInfo.framebuffer = swapChainFramebuffers[i];
        // renderArea   ��Ա��������ָ��������Ⱦ������,������δ���壬���͸��Ŵ�С��ȫһ��
        renderPassInfo.renderArea.offset = { 0, 0 };
        renderPassInfo.renderArea.extent = swapChainExtent;

        VkClearValue clearColor = { {{0.0f, 0.0f, 0.0f, 1.0f}} };
        renderPassInfo.clearValueCount = 1;
        renderPassInfo.pClearValues = &clearColor;

        vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

        // ��ͼ�ι��� �ڶ�����������ָ�����߶�����ͼ�ι��߻��Ǽ������
        vkCmdBindPipeline(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);

        // �ύ���Ʋ�����ָ��壬��������¼��Ҫִ�е�ָ���ָ������ָ���Ķ��������������3-�����Σ�������ʵ����Ⱦ��Ϊ1ʱ��ʾ������ʵ����Ⱦ�������ڶ�����ɫ������gl_VertexIndex��ֵ�����ڶ�����ɫ������gl_InstanceIndex��ֵ
        vkCmdDraw(commandBuffers[i], 3, 1, 0, 0);

        // ������Ⱦ����
        vkCmdEndRenderPass(commandBuffers[i]);

        // ������¼ָ�ָ���
        if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS) {
            throw std::runtime_error("failed to record command buffer!");
        }
    }
}
