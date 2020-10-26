//
// Created by tangt on 19/10/2020.
//
// Command buffer is use for bind a vertex and index buffer to the graphic pipeline and then use for render
//

#include "CommandBuffer.h"
#include "CommandPool.h"
#include "Swapchain.h"
#include "LogicalDevice.h"
#include "Pipeline.h"

void graphics::CommandBuffer::initialize(const Swapchain & swapchain)
{
    const vk::Device & logicalDevice = swapchain.getParentLogicalDevice().getVkLogicalDevice();

    m_commandBuffers.resize(swapchain.getVkFrameBuffers().size());

    vk::CommandBufferAllocateInfo commandBufferInfo{};

    commandBufferInfo.commandPool = swapchain.getParentLogicalDevice().getCommandPool().getVkCommandPool();
    commandBufferInfo.level = vk::CommandBufferLevel::ePrimary;
    commandBufferInfo.commandBufferCount = static_cast<uint32_t>(m_commandBuffers.size());
    if (logicalDevice.allocateCommandBuffers(&commandBufferInfo, m_commandBuffers.data()) != vk::Result::eSuccess)
    {
        throw std::runtime_error("Error while creating command buffer");
    }
}

void graphics::CommandBuffer::release(const LogicalDevice & logicalDevice)
{
    logicalDevice.getVkLogicalDevice().freeCommandBuffers(logicalDevice.getCommandPool().getVkCommandPool(), m_commandBuffers);
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
                                     const std::vector<uint32_t> & indices,
                                     uint32_t imageIndex
                                     )
{
        m_commandBuffers[imageIndex].bindPipeline(vk::PipelineBindPoint::eGraphics, pipeline.getVkPipeline());

        vk::Buffer vertexBuffers[] = {swapchain.getVkVertexBuffer()};
        vk::DeviceSize deviceSize[] = {0};

        m_commandBuffers[imageIndex].bindVertexBuffers(0, 1, vertexBuffers, deviceSize);
        m_commandBuffers[imageIndex].bindIndexBuffer(swapchain.getVkIndexBuffer(), 0, vk::IndexType::eUint32);
        m_commandBuffers[imageIndex].bindDescriptorSets(vk::PipelineBindPoint::eGraphics,
                                               pipeline.getVkPipelineLayout(),
                                               0,
                                               1,
                                               &swapchain.getVkDescriptorSet(imageIndex),
                                               0,
                                               nullptr);
        m_commandBuffers[imageIndex].drawIndexed(indices.size(), 1, 0, 0, 0);
}

void graphics::CommandBuffer::endRender(uint32_t imageIndex)
{
    m_commandBuffers[imageIndex].endRenderPass();
    m_commandBuffers[imageIndex].end();
}

const vk::CommandBuffer & graphics::CommandBuffer::getCommandBuffer(uint32_t imageIndex) const
{
    return m_commandBuffers[imageIndex];
}