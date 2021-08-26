/*
������Ⱦ��֡���帽�ţ���ָ��ʹ�õ���ɫ����Ȼ��壬�Լ�����������Ⱦ������δ����������
*/

#include "baseCode.h"
#include "renderPasses.h"

void renderPasses::createRenderPass()
{
    // ������ͼ�����ɫ���帽��
    VkAttachmentDescription colorAttachment{};
    // format   ��Ա��������ָ����ɫ���帽�ŵĸ�ʽ
    // samples  ��Ա��������ָ��������
    colorAttachment.format = swapChainImageFormat;
    colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
    // loadOp��storeOp��Ա��������ָ������Ⱦ֮ǰ����Ⱦ֮��Ը����е����ݽ��еĲ���
    // loadOp��Ա����:
    // VK_ATTACHMENT_LOAD_OP_LOAD��      ���ָ��ŵ���������
    // VK_ATTACHMENT_LOAD_OP_CLEAR��     ʹ��һ������ֵ��������ŵ�����
    // VK_ATTACHMENT_LOAD_OP_DONT_CARE�� �����ĸ����ִ������
    // ����ÿ����Ⱦ�µ�һ֡ǰʹ�ú�ɫ���֡����
    colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    // storeOp��Ա����:
    // VK_ATTACHMENT_STORE_OP_STORE��    ��Ⱦ�����ݻᱻ�洢�������Ա�֮���ȡ
    // VK_ATTACHMENT_STORE_OP_DONT_CARE����Ⱦ�󣬲����ȡ֡���������
    colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    // stencilLoadOp �� stencilStoreOp ���ģ�建����Ч
    colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    // VK_IMAGE_LAYOUT_PRESENT_SRC_KHR          ͼ�����ڽ������н��г��ֲ���
    colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

    // ������
    VkAttachmentReference colorAttachmentRef{};
    colorAttachmentRef.attachment = 0;
    // VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL ͼ��������ɫ����
    colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkSubpassDescription subpass{};
    subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    // �������õ���ɫ�����������е������ᱻƬ����ɫ��ʹ�ã���ӦƬ����ɫ����ʹ�õģ�
    // layout(location = 0) out vec4 outColor ���
    subpass.colorAttachmentCount = 1;
    subpass.pColorAttachments = &colorAttachmentRef;

    VkSubpassDependency dependency{};
    dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
    dependency.dstSubpass = 0;
    dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.srcAccessMask = 0;
    dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

    // ���ú��˸��ź����õ������̾��ܿ�ʼ��Ⱦ���̶���
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