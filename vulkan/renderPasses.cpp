/*
用于渲染的帧缓冲附着，将指定使用的颜色和深度缓冲，以及采样数，渲染操作如何处理缓冲的内容
*/

#include "baseCode.h"
#include "renderPasses.h"

void renderPasses::createRenderPass()
{
    // 交换链图像的颜色缓冲附着
    VkAttachmentDescription colorAttachment{};
    // format   成员变量用于指定颜色缓冲附着的格式
    // samples  成员变量用于指定采样数
    colorAttachment.format = swapChainImageFormat;
    colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
    // loadOp和storeOp成员变量用于指定在渲染之前和渲染之后对附着中的数据进行的操作
    // loadOp成员变量:
    // VK_ATTACHMENT_LOAD_OP_LOAD：      保持附着的现有内容
    // VK_ATTACHMENT_LOAD_OP_CLEAR：     使用一个常量值来清除附着的内容
    // VK_ATTACHMENT_LOAD_OP_DONT_CARE： 不关心附着现存的内容
    // 这里每次渲染新的一帧前使用黑色清除帧缓冲
    colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    // storeOp成员变量:
    // VK_ATTACHMENT_STORE_OP_STORE：    渲染的内容会被存储起来，以便之后读取
    // VK_ATTACHMENT_STORE_OP_DONT_CARE：渲染后，不会读取帧缓冲的内容
    colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    // stencilLoadOp 和 stencilStoreOp 会对模板缓冲起效
    colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    // VK_IMAGE_LAYOUT_PRESENT_SRC_KHR          图像被用在交换链中进行呈现操作
    colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

    // 子流程
    VkAttachmentReference colorAttachmentRef{};
    colorAttachmentRef.attachment = 0;
    // VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL 图像被用作颜色附着
    colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkSubpassDescription subpass{};
    subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    // 这里设置的颜色附着在数组中的索引会被片段着色器使用，对应片段着色器中使用的：
    // layout(location = 0) out vec4 outColor 语句
    subpass.colorAttachmentCount = 1;
    subpass.pColorAttachments = &colorAttachmentRef;

    VkSubpassDependency dependency{};
    dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
    dependency.dstSubpass = 0;
    dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.srcAccessMask = 0;
    dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

    // 设置好了附着和引用的子流程就能开始渲染流程对象
    VkRenderPassCreateInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassInfo.attachmentCount = 1;
    renderPassInfo.pAttachments = &colorAttachment;
    renderPassInfo.subpassCount = 1;
    renderPassInfo.pSubpasses = &subpass;
    renderPassInfo.dependencyCount = 1;
    renderPassInfo.pDependencies = &dependency;

    if (vkCreateRenderPass(device, &renderPassInfo, nullptr, &renderPass) != VK_SUCCESS) 
    {
        throw std::runtime_error("failed to create render pass!");
    }
}