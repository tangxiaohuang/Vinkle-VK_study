#include "baseCode.h"
#include "shaderModules.h"

void shaderModules::createGraphicsPipeline()
{
    // 在createGraphicsPipeline函数中调用readFile函数来完成着色器字节码的读取
    auto vertShaderCode = readFile("C:/Users/Administrator/Desktop/Vulkan的学习/Vulkan_start/Project/vulkan/vulkan/shadows/shaders/vert.spv");
    auto fragShaderCode = readFile("C:/Users/Administrator/Desktop/Vulkan的学习/Vulkan_start/Project/vulkan/vulkan/shadows/shaders/frag.spv");

    // 调用我们编写的辅助函数创建着色器模块对象
    VkShaderModule vertShaderModule = createShaderModule(vertShaderCode);
    VkShaderModule fragShaderModule = createShaderModule(fragShaderCode);

    // sType        
    // stage        指定了着色器在管线的哪一阶段被使用
    // module       用于指定阶段使用的着色器模块对象
    // pName        用于指定阶段调用的着色器函数
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

    // 用于描述传递给给顶点着色器的顶点数据格式
    VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
    vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertexInputInfo.vertexBindingDescriptionCount = 0;
    vertexInputInfo.vertexAttributeDescriptionCount = 0;

    // 用于描述两个信息：顶点数据定义了哪种类型的几何图元，以及是否启用几何图元重启
    // VK_PRIMITIVE_TOPOLOGY_POINT_LIST：    点图元
    // VK_PRIMITIVE_TOPOLOGY_LINE_LIST：     每两个顶点构成一个线段图元
    // VK_PRIMITIVE_TOPOLOGY_LINE_STRIP：    每两个顶点构成一个线段图元，除第一个线段图元外，每个线段图元使用上一个线段图元的一个顶点
    // VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST： 每三个顶点构成一个三角形图元
    // VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP：每个三角形的第二个和第三个顶点被下一个三角形作为第一和第二个顶点使用
    VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
    inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    inputAssembly.primitiveRestartEnable = VK_FALSE;

    // 视口用于描述被用来输出渲染结果的帧缓冲区域
    VkViewport viewport{};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = (float)swapChainExtent.width;
    viewport.height = (float)swapChainExtent.height;
    // minDepth 和 maxDepth 成员变量用于指定帧缓冲使用的深度值的范围
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;

    // 裁剪范围设置
    VkRect2D scissor{};
    scissor.offset = { 0, 0 };
    scissor.extent = swapChainExtent;

    // 视口和裁剪矩形需要组合在一起，通过VkPipelineViewportStateCreateInfo结构体指定。
    VkPipelineViewportStateCreateInfo viewportState{};
    viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewportState.viewportCount = 1;
    viewportState.pViewports = &viewport;
    viewportState.scissorCount = 1;
    viewportState.pScissors = &scissor;

    // 光栅化将顶点着色器的顶点构成的几何图元转换为片段交由片段着色器着色
    // 深度测试，背面剔除和裁剪测试的开启，都是需要光栅化执行
    VkPipelineRasterizationStateCreateInfo rasterizer{};
    rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizer.depthClampEnable = VK_FALSE;
    // 如果 rasterizerDiscardEnable 为 VK_TRUE 表示所有的几何图元都不能通过光栅化，相当于禁止一切片段输出到帧缓冲
    rasterizer.rasterizerDiscardEnable = VK_FALSE;
    //VK_POLYGON_MODE_FILL： 整个多边形，包括多边形内部都产生片段
    //VK_POLYGON_MODE_LINE： 只有多边形的边会产生片段
    //VK_POLYGON_MODE_POINT：只有多边形的顶点会产生片段
    rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
    rasterizer.lineWidth = 1.0f;
    // cullMode成员变量用于指定使用的表面剔除类型
    rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
    rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
    rasterizer.depthBiasEnable = VK_FALSE;

    //多重采样
    VkPipelineMultisampleStateCreateInfo multisampling{};
    multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampling.sampleShadingEnable = VK_FALSE;
    multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

    // 颜色混合 用来对每个绑定的帧缓冲进行单独的颜色混合配置
    VkPipelineColorBlendAttachmentState colorBlendAttachment{};
    colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    colorBlendAttachment.blendEnable = VK_FALSE;

    // 颜色混合 用来进行全局的颜色混合配置
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

    // 管线布局 管线建立后动态地被应用程序修改，实现对着色器进行一定程度的动态配置
    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.setLayoutCount = 0;
    pipelineLayoutInfo.pushConstantRangeCount = 0;

    if (vkCreatePipelineLayout(device, &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) 
    {
        throw std::runtime_error("failed to create pipeline layout!");
    }

    // 结合着色器阶段、固定功能状态、管线布局、渲染流程  定义图形管线功能
    VkGraphicsPipelineCreateInfo pipelineInfo{};
    pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipelineInfo.stageCount = 2;
    pipelineInfo.pStages = shaderStages;
    pipelineInfo.pVertexInputState = &vertexInputInfo;
    // 上面使用来指定 VkPipelineShaderStageCreateInfo 定义的两个着色器阶段
    pipelineInfo.pInputAssemblyState = &inputAssembly;
    pipelineInfo.pViewportState = &viewportState;
    pipelineInfo.pRasterizationState = &rasterizer;
    pipelineInfo.pMultisampleState = &multisampling;
    pipelineInfo.pColorBlendState = &colorBlending;
    // 引用之前设置的固定功能阶段信息
    pipelineInfo.layout = pipelineLayout;
    // 指定之前创建的管线布局
    pipelineInfo.renderPass = renderPass;
    pipelineInfo.subpass = 0;
    // 引用之前创建的渲染流程对象和图形管线使用的子流程在子流程数组中的索引
    // basePipelineHandle和basePipelineIndex成员变量用于以一个创建好的图形管线为基础创建一个新的图形管线
    pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

    // 创建管线对象
    if (vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &graphicsPipeline) != VK_SUCCESS) 
    {
        throw std::runtime_error("failed to create graphics pipeline!");
    }

    // 清除创建的着色器模块对象
    vkDestroyShaderModule(device, fragShaderModule, nullptr);
    vkDestroyShaderModule(device, vertShaderModule, nullptr);
}

VkShaderModule shaderModules::createShaderModule(const std::vector<char>& code) 
{
    // 用于存储字节码的数组指针转换为const uint32_t*变量类型
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

// 用于加载SPIR-V格式的着色器字节码文件 readFile 函数会读取指定文件的所有字节返回给调用者
// ate:从文件尾部开始读取
// binary:以二进制的形式读取文件(避免进行诸如行末格式是\n还是\r\n的转换)
// 使用ate模式，从文件尾部开始读取的原因是，我们可以根据读取位置确定文件的大小，然后分配足够的数组空间来容纳数据
std::vector<char> shaderModules::readFile(const std::string& filename)
{
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    if (!file.is_open()) 
    {
        throw std::runtime_error("failed to open file!");
    }

    size_t fileSize = (size_t)file.tellg();
    std::vector<char> buffer(fileSize);

    // 分配好足够的数组空间后，我们可以跳到文件头部，读取整个文件
    file.seekg(0);
    file.read(buffer.data(), fileSize);

    // 关闭文件，返回数据数组
    file.close();
    return buffer;
}