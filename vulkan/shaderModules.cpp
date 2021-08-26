#include "baseCode.h"
#include "shaderModules.h"

void shaderModules::createGraphicsPipeline()
{
    // ��createGraphicsPipeline�����е���readFile�����������ɫ���ֽ���Ķ�ȡ
    auto vertShaderCode = readFile("C:/Users/Administrator/Desktop/Vulkan��ѧϰ/Vulkan_start/Project/vulkan/vulkan/shadows/shaders/vert.spv");
    auto fragShaderCode = readFile("C:/Users/Administrator/Desktop/Vulkan��ѧϰ/Vulkan_start/Project/vulkan/vulkan/shadows/shaders/frag.spv");

    // �������Ǳ�д�ĸ�������������ɫ��ģ�����
    VkShaderModule vertShaderModule = createShaderModule(vertShaderCode);
    VkShaderModule fragShaderModule = createShaderModule(fragShaderCode);

    // sType        
    // stage        ָ������ɫ���ڹ��ߵ���һ�׶α�ʹ��
    // module       ����ָ���׶�ʹ�õ���ɫ��ģ�����
    // pName        ����ָ���׶ε��õ���ɫ������
    VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
    vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
    vertShaderStageInfo.module = vertShaderModule;
    vertShaderStageInfo.pName = "main";

    VkPipelineShaderStageCreateInfo fragShaderStageInfo{};
    fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    fragShaderStageInfo.module = fragShaderModule;
    fragShaderStageInfo.pName = "main";

    VkPipelineShaderStageCreateInfo shaderStages[] = 
    { 
        vertShaderStageInfo, 
        fragShaderStageInfo 
    };

    // �����������ݸ���������ɫ���Ķ������ݸ�ʽ
    VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
    vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertexInputInfo.vertexBindingDescriptionCount = 0;
    vertexInputInfo.vertexAttributeDescriptionCount = 0;

    // ��������������Ϣ���������ݶ������������͵ļ���ͼԪ���Լ��Ƿ����ü���ͼԪ����
    // VK_PRIMITIVE_TOPOLOGY_POINT_LIST��    ��ͼԪ
    // VK_PRIMITIVE_TOPOLOGY_LINE_LIST��     ÿ�������㹹��һ���߶�ͼԪ
    // VK_PRIMITIVE_TOPOLOGY_LINE_STRIP��    ÿ�������㹹��һ���߶�ͼԪ������һ���߶�ͼԪ�⣬ÿ���߶�ͼԪʹ����һ���߶�ͼԪ��һ������
    // VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST�� ÿ�������㹹��һ��������ͼԪ
    // VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP��ÿ�������εĵڶ����͵��������㱻��һ����������Ϊ��һ�͵ڶ�������ʹ��
    VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
    inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    inputAssembly.primitiveRestartEnable = VK_FALSE;

    // �ӿ��������������������Ⱦ�����֡��������
    VkViewport viewport{};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = (float)swapChainExtent.width;
    viewport.height = (float)swapChainExtent.height;
    // minDepth �� maxDepth ��Ա��������ָ��֡����ʹ�õ����ֵ�ķ�Χ
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;

    // �ü���Χ����
    VkRect2D scissor{};
    scissor.offset = { 0, 0 };
    scissor.extent = swapChainExtent;

    // �ӿںͲü�������Ҫ�����һ��ͨ��VkPipelineViewportStateCreateInfo�ṹ��ָ����
    VkPipelineViewportStateCreateInfo viewportState{};
    viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewportState.viewportCount = 1;
    viewportState.pViewports = &viewport;
    viewportState.scissorCount = 1;
    viewportState.pScissors = &scissor;

    // ��դ����������ɫ���Ķ��㹹�ɵļ���ͼԪת��ΪƬ�ν���Ƭ����ɫ����ɫ
    // ��Ȳ��ԣ������޳��Ͳü����ԵĿ�����������Ҫ��դ��ִ��
    VkPipelineRasterizationStateCreateInfo rasterizer{};
    rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizer.depthClampEnable = VK_FALSE;
    // ��� rasterizerDiscardEnable Ϊ VK_TRUE ��ʾ���еļ���ͼԪ������ͨ����դ�����൱�ڽ�ֹһ��Ƭ�������֡����
    rasterizer.rasterizerDiscardEnable = VK_FALSE;
    //VK_POLYGON_MODE_FILL�� ��������Σ�����������ڲ�������Ƭ��
    //VK_POLYGON_MODE_LINE�� ֻ�ж���εı߻����Ƭ��
    //VK_POLYGON_MODE_POINT��ֻ�ж���εĶ�������Ƭ��
    rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
    rasterizer.lineWidth = 1.0f;
    // cullMode��Ա��������ָ��ʹ�õı����޳�����
    rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
    rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
    rasterizer.depthBiasEnable = VK_FALSE;

    //���ز���
    VkPipelineMultisampleStateCreateInfo multisampling{};
    multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampling.sampleShadingEnable = VK_FALSE;
    multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

    // ��ɫ��� ������ÿ���󶨵�֡������е�������ɫ�������
    VkPipelineColorBlendAttachmentState colorBlendAttachment{};
    colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    colorBlendAttachment.blendEnable = VK_FALSE;

    // ��ɫ��� ��������ȫ�ֵ���ɫ�������
    VkPipelineColorBlendStateCreateInfo colorBlending{};
    colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colorBlending.logicOpEnable = VK_FALSE;
    colorBlending.logicOp = VK_LOGIC_OP_COPY;
    colorBlending.attachmentCount = 1;
    colorBlending.pAttachments = &colorBlendAttachment;
    colorBlending.blendConstants[0] = 0.0f;
    colorBlending.blendConstants[1] = 0.0f;
    colorBlending.blendConstants[2] = 0.0f;
    colorBlending.blendConstants[3] = 0.0f;

    // ���߲��� ���߽�����̬�ر�Ӧ�ó����޸ģ�ʵ�ֶ���ɫ������һ���̶ȵĶ�̬����
    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.setLayoutCount = 0;
    pipelineLayoutInfo.pushConstantRangeCount = 0;

    if (vkCreatePipelineLayout(device, &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) 
    {
        throw std::runtime_error("failed to create pipeline layout!");
    }

    // �����ɫ���׶Ρ��̶�����״̬�����߲��֡���Ⱦ����  ����ͼ�ι��߹���
    VkGraphicsPipelineCreateInfo pipelineInfo{};
    pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipelineInfo.stageCount = 2;
    pipelineInfo.pStages = shaderStages;
    pipelineInfo.pVertexInputState = &vertexInputInfo;
    // ����ʹ����ָ�� VkPipelineShaderStageCreateInfo �����������ɫ���׶�
    pipelineInfo.pInputAssemblyState = &inputAssembly;
    pipelineInfo.pViewportState = &viewportState;
    pipelineInfo.pRasterizationState = &rasterizer;
    pipelineInfo.pMultisampleState = &multisampling;
    pipelineInfo.pColorBlendState = &colorBlending;
    // ����֮ǰ���õĹ̶����ܽ׶���Ϣ
    pipelineInfo.layout = pipelineLayout;
    // ָ��֮ǰ�����Ĺ��߲���
    pipelineInfo.renderPass = renderPass;
    pipelineInfo.subpass = 0;
    // ����֮ǰ��������Ⱦ���̶����ͼ�ι���ʹ�õ��������������������е�����
    // basePipelineHandle��basePipelineIndex��Ա����������һ�������õ�ͼ�ι���Ϊ��������һ���µ�ͼ�ι���
    pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

    // �������߶���
    if (vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &graphicsPipeline) != VK_SUCCESS) 
    {
        throw std::runtime_error("failed to create graphics pipeline!");
    }

    // �����������ɫ��ģ�����
    vkDestroyShaderModule(device, fragShaderModule, nullptr);
    vkDestroyShaderModule(device, vertShaderModule, nullptr);
}

VkShaderModule shaderModules::createShaderModule(const std::vector<char>& code) 
{
    // ���ڴ洢�ֽ��������ָ��ת��Ϊconst uint32_t*��������
    VkShaderModuleCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = code.size();
    createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

    VkShaderModule shaderModule;
    if (vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS) 
    {
        throw std::runtime_error("failed to create shader module!");
    }

    return shaderModule;
}

// ���ڼ���SPIR-V��ʽ����ɫ���ֽ����ļ� readFile �������ȡָ���ļ��������ֽڷ��ظ�������
// ate:���ļ�β����ʼ��ȡ
// binary:�Զ����Ƶ���ʽ��ȡ�ļ�(�������������ĩ��ʽ��\n����\r\n��ת��)
// ʹ��ateģʽ�����ļ�β����ʼ��ȡ��ԭ���ǣ����ǿ��Ը��ݶ�ȡλ��ȷ���ļ��Ĵ�С��Ȼ������㹻������ռ�����������
std::vector<char> shaderModules::readFile(const std::string& filename)
{
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    if (!file.is_open()) 
    {
        throw std::runtime_error("failed to open file!");
    }

    size_t fileSize = (size_t)file.tellg();
    std::vector<char> buffer(fileSize);

    // ������㹻������ռ�����ǿ��������ļ�ͷ������ȡ�����ļ�
    file.seekg(0);
    file.read(buffer.data(), fileSize);

    // �ر��ļ���������������
    file.close();
    return buffer;
}