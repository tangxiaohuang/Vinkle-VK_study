#include "baseCode.h"
#include "commandBuffers.h"

// 指令池的概念：用于管理指令缓冲对象使用的内存，并负责指令缓冲对象的分配
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

// 为每个图像分配一个指令缓冲对象
void commandBuffer::createCommandBuffers()
{
	commandBuffers.resize(swapChainFramebuffers.size());

	VkCommandBufferAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = commandPool;
    // level 用于指定分配的指令缓冲对象是主要指令缓冲对象还是辅助指令缓冲对象
    // VK_COMMAND_BUFFER_LEVEL_PRIMARY：     可以被提交到队列进行执行，但不能被其它指令缓冲对象调用。
    // VK_COMMAND_BUFFER_LEVEL_SECONDARY：   不能直接被提交到队列进行执行，但可以被主要指令缓冲对象调用执行。
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = (uint32_t)commandBuffers.size();

	if (vkAllocateCommandBuffers(device, &allocInfo, commandBuffers.data()) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to allocate command buffers!");
	}

    // 记录指令到指令缓冲
    for (size_t i = 0; i < commandBuffers.size(); i++) {
        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        //这里还有一个 beginInfo.flags 用于指定我们将要怎样使用指令缓冲
        // VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT：         指令缓冲在执行一次后，就被用来记录新的指令。
        // VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT：    这是一个只在一个渲染流程内使用的辅助指令缓冲。
        // VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT：        在指令缓冲等待执行时，仍然可以提交这一指令缓冲。

        // vkBeginCommandBuffer函数会重置指令缓冲对象
        if (vkBeginCommandBuffer(commandBuffers[i], &beginInfo) != VK_SUCCESS) {
            throw std::runtime_error("failed to begin recording command buffer!");
        }

        // 开始渲染流程
        VkRenderPassBeginInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        // renderPass   用于指定使用的渲染流程对象
        renderPassInfo.renderPass = renderPass;
        // framebuffer  用于指定使用的帧缓冲对象
        renderPassInfo.framebuffer = swapChainFramebuffers[i];
        // renderArea   成员变量用于指定用于渲染的区域,若区域未定义，则会和附着大小完全一样
        renderPassInfo.renderArea.offset = { 0, 0 };
        renderPassInfo.renderArea.extent = swapChainExtent;

        VkClearValue clearColor = { {{0.0f, 0.0f, 0.0f, 1.0f}} };
        renderPassInfo.clearValueCount = 1;
        renderPassInfo.pClearValues = &clearColor;

        vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

        // 绑定图形管线 第二个参数用于指定管线对象是图形管线还是计算管线
        vkCmdBindPipeline(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);

        // 提交绘制操作到指令缓冲，参数：记录有要执行的指令的指令缓冲对象、指定的顶点个数（这里是3-三角形）、用于实例渲染（为1时表示不进行实例渲染）、用于定义着色器变量gl_VertexIndex的值、用于定义着色器变量gl_InstanceIndex的值
        vkCmdDraw(commandBuffers[i], 3, 1, 0, 0);

        // 结束渲染流程
        vkCmdEndRenderPass(commandBuffers[i]);

        // 结束记录指令到指令缓冲
        if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS) {
            throw std::runtime_error("failed to record command buffer!");
        }
    }
}
