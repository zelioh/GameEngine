//
// Created by tangt on 19/10/2020.
//
// Command buffer is use for bind a vertex and index buffer to the graphic pipeline and then use for render
//

#include "GraphicsEngine/CommandBuffer.h"
#include "GraphicsEngine/CommandPool.h"
#include "GraphicsEngine/Swapchain.h"
#include "GraphicsEngine/LogicalDevice.h"
#include "GraphicsEngine/Pipeline.h"
#include "GraphicsEngine/GameObject.h"
#include "public/GraphicsEngine/Texture.h"
#include "GraphicsEngine/SUniformBufferObject.h"
#include "public/GraphicsEngine/TextureManager.h"
#include "GraphicsEngine/SceneManager.h"
#include "GraphicsEngine/Scene.h"
#include "GraphicsEngine/Light.h"
#include "GraphicsEngine/Camera.h"

void graphics::CommandBuffer::initialize()
{
    Swapchain * swapchain = Swapchain::getInstance();
    LogicalDevice * logicalDevice = LogicalDevice::getInstance();

    m_commandBuffers.resize(swapchain->getVkFrameBuffers().size());

    vk::CommandBufferAllocateInfo commandBufferInfo{};

    commandBufferInfo.commandPool = logicalDevice->getCommandPool().getVkCommandPool();
    commandBufferInfo.level = vk::CommandBufferLevel::ePrimary;
    commandBufferInfo.commandBufferCount = static_cast<uint32_t>(m_commandBuffers.size());
    if (logicalDevice->getVkLogicalDevice().allocateCommandBuffers(&commandBufferInfo, m_commandBuffers.data()) != vk::Result::eSuccess)
    {
        throw std::runtime_error("Error while creating command buffer");
    }
}

void graphics::CommandBuffer::release()
{
    LogicalDevice * logicalDevice = LogicalDevice::getInstance();

    logicalDevice->getVkLogicalDevice().freeCommandBuffers(logicalDevice->getCommandPool().getVkCommandPool(), m_commandBuffers);
}

void graphics::CommandBuffer::beginRender(const Swapchain &swapchain, uint32_t imageIndex)
{
    const vk::CommandBuffer & commandBuffer = m_commandBuffers[imageIndex];

    commandBuffer.reset(vk::CommandBufferResetFlagBits::eReleaseResources);

    vk::CommandBufferBeginInfo beginInfo{};

    commandBuffer.begin(beginInfo);

    vk::RenderPassBeginInfo renderPassBeginInfo{};
    std::array<vk::ClearValue, 2> clearValues{};

    clearValues[0].color = vk::ClearColorValue(std::array{0.f, 0.f, 0.f, 1.f});
    clearValues[1].depthStencil = vk::ClearDepthStencilValue(1.f, 0);

    renderPassBeginInfo.renderPass = swapchain.getRenderPass().getVkRenderPass();
    renderPassBeginInfo.framebuffer = swapchain.getVkFrameBuffers()[imageIndex];
    renderPassBeginInfo.renderArea.offset = vk::Offset2D(0, 0);
    renderPassBeginInfo.renderArea.extent = swapchain.getVkSwapchainExtent();
    renderPassBeginInfo.clearValueCount = clearValues.size();
    renderPassBeginInfo.pClearValues = clearValues.data();

    m_commandBuffers[imageIndex].beginRenderPass(renderPassBeginInfo, vk::SubpassContents::eInline);
}

void graphics::CommandBuffer::render(const Swapchain &swapchain,
                                     const CommandPool &commandPool,
                                     const Pipeline & pipeline,
                                     const object::GameObject * object,
                                     uint32_t imageIndex,
                                     const Math::Matrix4F & projectionMatrix,
                                     const Math::Matrix4F & viewMatrix
                                     )
{
    SUniformBufferObject ubo;

    ubo.model = object->getTransformationMatrix();
    ubo.view = viewMatrix;
    ubo.proj = projectionMatrix;
    ubo.proj(1, 1) *= -1;

    object::Light * light = object::SceneManager::getInstance()->getCurrentScene()->getLight();

    if (nullptr != light)
    {
        ubo.position = light->getPosition();
        ubo.color = light->getColor();
        ubo.specular = light->getSpecular();
        ubo.strenght = light->getStrength();
    } else {
        ubo.position = Math::Vector3F(0.f, 0.f, 0.f);
        ubo.color = Math::Vector3F(1.f, 1.f, 1.f);
        ubo.strenght = 0.f;
        ubo.specular = 0.f;
    }

    ubo.cameraPosition = object::SceneManager::getInstance()->getCurrentScene()->getCurrentCamera()->getPosition();

    m_commandBuffers[imageIndex].pushConstants(pipeline.getVkPipelineLayout(),
                                               vk::ShaderStageFlagBits::eAllGraphics,
                                               0,
                                               sizeof(SUniformBufferObject),
                                               &ubo);

    m_commandBuffers[imageIndex].bindPipeline(vk::PipelineBindPoint::eGraphics, pipeline.getVkPipeline());

    vk::Buffer vertexBuffers[] = {object->getVertexBuffer()};
    vk::DeviceSize deviceSize[] = {0};

    m_commandBuffers[imageIndex].bindVertexBuffers(0, 1, vertexBuffers, deviceSize);
    m_commandBuffers[imageIndex].bindIndexBuffer(object->getIndexBuffer(), 0, vk::IndexType::eUint32);
    if (nullptr != object->getTexture()) {
        const vk::DescriptorSet & descriptorSet{object->getTexture()->getVkDescriptorSet(imageIndex)};

        m_commandBuffers[imageIndex].bindDescriptorSets(vk::PipelineBindPoint::eGraphics,
                                                        pipeline.getVkPipelineLayout(),
                                                        0,
                                                        1,
                                                        &descriptorSet,
                                                        0,
                                                        nullptr);
    } else {
        Texture * defaultTexture = TextureManager::getInstance()->createTexture("../assets/white.png",
                                                                                "Default_texture_engine");
        const vk::DescriptorSet & descriptorSet{defaultTexture->getVkDescriptorSet(imageIndex)};

        m_commandBuffers[imageIndex].bindDescriptorSets(vk::PipelineBindPoint::eGraphics,
                                                        pipeline.getVkPipelineLayout(),
                                                        0,
                                                        1,
                                                        &descriptorSet,
                                                        0,
                                                        nullptr);
    }
    m_commandBuffers[imageIndex].drawIndexed(object->getIndices().size(), 1, 0, 0, 0);
}

void graphics::CommandBuffer::endRender(uint32_t imageIndex, const Swapchain & swapchain)
{
    m_commandBuffers[imageIndex].endRenderPass();
    m_commandBuffers[imageIndex].end();
}

const vk::CommandBuffer & graphics::CommandBuffer::getCommandBuffer(uint32_t imageIndex) const
{
    return m_commandBuffers[imageIndex];
}