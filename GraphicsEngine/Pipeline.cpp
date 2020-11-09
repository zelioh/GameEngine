//
// Created by tangt on 13/10/2020.
//
// Graphics pipeline implementation, use to bind a shader, viewport, scissor, rasterizer, ... with the command buffer
//

#include "Pipeline.h"
#include "LogicalDevice.h"
#include "Shader.h"
#include "Vertex.h"
#include "Swapchain.h"
#include "PhysicalDevice.h"
#include "SUniformBufferObject.h"

graphics::Pipeline::Pipeline(const Shader &shader)
{
    initialize(shader);
}

void graphics::Pipeline::initialize(const Shader &shader)
{
    LogicalDevice * logicalDevice = LogicalDevice::getInstance();
    Swapchain * swapchain = Swapchain::getInstance();

    //
    // Set shader stage informations
    vk::ShaderModule vertShaderModule = createShaderModule(shader.getVertexData());
    vk::ShaderModule fragShaderModule = createShaderModule(shader.getFragmentData());

    vk::PipelineShaderStageCreateInfo vertShaderStageInfo{};

    vertShaderStageInfo.stage = vk::ShaderStageFlagBits::eVertex;
    vertShaderStageInfo.module = vertShaderModule;
    vertShaderStageInfo.pName = "main";

    vk::PipelineShaderStageCreateInfo fragShaderStageInfo{};

    fragShaderStageInfo.stage = vk::ShaderStageFlagBits::eFragment;
    fragShaderStageInfo.module = fragShaderModule;
    fragShaderStageInfo.pName = "main";

    vk::PipelineShaderStageCreateInfo shaderStage[] = {vertShaderStageInfo, fragShaderStageInfo};

    //
    // Set vertex input information
    vk::PipelineVertexInputStateCreateInfo vertexInputInfo{};
    vk::VertexInputBindingDescription bind = graphics::Vertex::getBindDescription();
    std::array<vk::VertexInputAttributeDescription, 4> attributes = graphics::Vertex::getAttributeDescription();

    vertexInputInfo.vertexBindingDescriptionCount = 1;
    vertexInputInfo.pVertexBindingDescriptions = &bind;
    vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributes.size());
    vertexInputInfo.pVertexAttributeDescriptions = attributes.data();

    //
    // Set input assembly information
    vk::PipelineInputAssemblyStateCreateInfo inputAssemblyInfo{};

    inputAssemblyInfo.topology = vk::PrimitiveTopology::eTriangleList;
    inputAssemblyInfo.primitiveRestartEnable = false;

    //
    // Set viewport and scissor informations
    vk::Extent2D extent = swapchain->getVkSwapchainExtent();
    vk::Viewport viewport{};

    viewport.x = 0.f;
    viewport.y = 0.f;
    viewport.width = static_cast<float>(extent.width);
    viewport.height = static_cast<float>(extent.height);
    viewport.minDepth = 0.f;
    viewport.maxDepth = 1.f;

    vk::Rect2D scissorRect{};

    scissorRect.offset = vk::Offset2D{0, 0};
    scissorRect.extent = extent;


    vk::PipelineViewportStateCreateInfo viewportInfo{};

    viewportInfo.viewportCount = 1;
    viewportInfo.pViewports = &viewport;
    viewportInfo.scissorCount = 1;
    viewportInfo.pScissors = &scissorRect;

    //
    // Set rasterizer  information
    vk::PipelineRasterizationStateCreateInfo rasterizer{};

    rasterizer.depthClampEnable = false;
    rasterizer.rasterizerDiscardEnable = false;
    rasterizer.polygonMode = vk::PolygonMode::eFill;
    rasterizer.lineWidth = 1.f;
    rasterizer.cullMode = vk::CullModeFlagBits::eBack;
    rasterizer.frontFace = vk::FrontFace::eCounterClockwise;
    rasterizer.depthBiasEnable = false;

    //
    // Set multisampling information
    vk::PipelineMultisampleStateCreateInfo multisampleInfo{};
    PhysicalDevice * physicalDevice = PhysicalDevice::getInstance();

    multisampleInfo.sampleShadingEnable = false;
    multisampleInfo.rasterizationSamples = physicalDevice->getVkMSSASample();
    multisampleInfo.minSampleShading = 1.f;
    multisampleInfo.pSampleMask = nullptr;
    multisampleInfo.alphaToCoverageEnable = false;
    multisampleInfo.alphaToOneEnable = false;

    //
    // Set color blending information
    vk::PipelineColorBlendAttachmentState colorBlendAttachment{};

    colorBlendAttachment.colorWriteMask =   vk::ColorComponentFlagBits::eR |
                                            vk::ColorComponentFlagBits::eG |
                                            vk::ColorComponentFlagBits::eB |
                                            vk::ColorComponentFlagBits::eA;
    colorBlendAttachment.blendEnable = false;
    colorBlendAttachment.srcColorBlendFactor = vk::BlendFactor::eOne;
    colorBlendAttachment.dstColorBlendFactor = vk::BlendFactor::eZero;
    colorBlendAttachment.colorBlendOp = vk::BlendOp::eAdd;
    colorBlendAttachment.srcAlphaBlendFactor = vk::BlendFactor::eOne;
    colorBlendAttachment.dstAlphaBlendFactor = vk::BlendFactor::eZero;
    colorBlendAttachment.alphaBlendOp = vk::BlendOp::eAdd;

    vk::PipelineColorBlendStateCreateInfo colorBlendInfo{};

    colorBlendInfo.attachmentCount = 1;
    colorBlendInfo.pAttachments = &colorBlendAttachment;
    colorBlendInfo.logicOpEnable = false;
    colorBlendInfo.logicOp = vk::LogicOp::eCopy;
    colorBlendInfo.blendConstants[0] = 0.f;
    colorBlendInfo.blendConstants[1] = 0.f;
    colorBlendInfo.blendConstants[2] = 0.f;
    colorBlendInfo.blendConstants[3] = 0.f;

    //
    // Set pipeline layout
    vk::PipelineLayoutCreateInfo layoutInfo{};

    vk::PushConstantRange pushConstantRange{
            vk::ShaderStageFlagBits::eAllGraphics,
            0,
            sizeof(SUniformBufferObject)
    };

    layoutInfo.setLayoutCount = 1;
    layoutInfo.pSetLayouts = &logicalDevice->getDescriptorSetLayout();
    layoutInfo.pushConstantRangeCount = 1;
    layoutInfo.pPushConstantRanges = &pushConstantRange;
    m_pipelineLayout = logicalDevice->getVkLogicalDevice().createPipelineLayout(layoutInfo);
    if (!m_pipelineLayout)
    {
        throw std::runtime_error("Error while creating layout pipeline");
    }

    //
    // Set depth stencil information
    vk::PipelineDepthStencilStateCreateInfo depthStencilInfo{};

    depthStencilInfo.depthTestEnable = true;
    depthStencilInfo.depthWriteEnable = true;
    depthStencilInfo.depthCompareOp = vk::CompareOp::eLess;
    depthStencilInfo.depthBoundsTestEnable = false;
    depthStencilInfo.minDepthBounds = 0.f;
    depthStencilInfo.maxDepthBounds = 1.f;
    depthStencilInfo.stencilTestEnable = false;
    depthStencilInfo.front = vk::StencilOp::eZero;
    depthStencilInfo.back = vk::StencilOp::eZero;

    //
    // Create graphics pipeline
    vk::GraphicsPipelineCreateInfo pipelineInfo{};

    pipelineInfo.stageCount = 2;
    pipelineInfo.pStages = shaderStage;
    pipelineInfo.pColorBlendState = &colorBlendInfo;
    pipelineInfo.pInputAssemblyState = &inputAssemblyInfo;
    pipelineInfo.pRasterizationState = &rasterizer;
    pipelineInfo.pViewportState = &viewportInfo;
    pipelineInfo.pVertexInputState = &vertexInputInfo;
    pipelineInfo.pMultisampleState = &multisampleInfo;
    pipelineInfo.pDepthStencilState = &depthStencilInfo;
    pipelineInfo.pDynamicState = nullptr;
    pipelineInfo.layout = m_pipelineLayout;
    pipelineInfo.renderPass = swapchain->getRenderPass().getVkRenderPass();
    pipelineInfo.subpass = 0;
    pipelineInfo.basePipelineHandle = nullptr;
    pipelineInfo.basePipelineIndex = 0;

    vk::Result result;

    std::tie(result, m_pipeline) = logicalDevice->getVkLogicalDevice().createGraphicsPipeline(nullptr, pipelineInfo);
    if (vk::Result::eSuccess != result)
    {
        throw std::runtime_error("Error while creating graphics pipeline");
    }

    //
    // Release useless datas
    logicalDevice->getVkLogicalDevice().destroyShaderModule(vertShaderModule);
    logicalDevice->getVkLogicalDevice().destroyShaderModule(fragShaderModule);
}

void graphics::Pipeline::release()
{
    const vk::Device & logicalDevice = LogicalDevice::getInstance()->getVkLogicalDevice();

    logicalDevice.destroyPipelineLayout(m_pipelineLayout);
    logicalDevice.destroyPipeline(m_pipeline);
}

vk::ShaderModule graphics::Pipeline::createShaderModule(const std::vector<char> &data)
{
    vk::ShaderModule shaderModule;
    vk::ShaderModuleCreateInfo shaderInfo{};
    const vk::Device & logicalDevice = LogicalDevice::getInstance()->getVkLogicalDevice();

    shaderInfo.codeSize = data.size();
    shaderInfo.pCode = reinterpret_cast<const uint32_t *>(data.data());
    shaderModule = logicalDevice.createShaderModule(shaderInfo);
    if (!shaderModule)
    {
        throw std::runtime_error("Error while creating shader module");
    }
    return shaderModule;
}

const vk::Pipeline & graphics::Pipeline::getVkPipeline() const
{
    return m_pipeline;
}

const vk::PipelineLayout & graphics::Pipeline::getVkPipelineLayout() const
{
    return m_pipelineLayout;
}