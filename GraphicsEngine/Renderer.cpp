//
// Created by tangt on 26/10/2020.
//

#include "Renderer.h"
#include "Swapchain.h"
#include "LogicalDevice.h"
#include "Pipeline.h"

graphics::Renderer::Renderer(const Swapchain & swapchain):
m_currentFrame(0),
m_imageIndex(0),
m_update(nullptr)
{
    m_commandBuffer.initialize(swapchain);
}

void graphics::Renderer::setUpdateCallback(const UpdateCallback &callback)
{
    m_update = callback;
}

bool graphics::Renderer::renderObject(Swapchain &swapchain,
                                      const object::GameObject *object,
                                      const Pipeline & pipeline)
{
    if (!renderBegin(swapchain, object))
        return false;
    render(swapchain, object, pipeline);
    return renderEnd(swapchain, pipeline);
}

bool graphics::Renderer::renderBegin(Swapchain & swapchain, const object::GameObject * object)
{
    const vk::Device logicalDevice = swapchain.getParentLogicalDevice().getVkLogicalDevice();

    if (nullptr != object->getTexture())
    {
        ///< TODO: do not do that see to create descriptor set in object
        ///< and bind it like the update function (see github pipeline render)
        //swapchain.updateDescriptorSet(object->getTexture());
    }

    logicalDevice.waitForFences(1, &swapchain.getVkFence(m_currentFrame), true, UINT64_MAX);
    try
    {
        m_imageIndex = swapchain.acquireNextImage(m_currentFrame);
    } catch (vk::OutOfDateKHRError outOfDateError) {
        // Swapchain need to be recreate
        return false;
    }
    m_commandBuffer.beginRender(swapchain, m_imageIndex);
    return true;
}

void graphics::Renderer::render(Swapchain & swapchain, const object::GameObject * object, const Pipeline & pipeline)
{
    if (nullptr != m_update)
    {
        m_update(swapchain, m_imageIndex);
    }
    m_commandBuffer.render(swapchain, swapchain.getParentLogicalDevice().getCommandPool(), pipeline, object, m_imageIndex);
}

bool graphics::Renderer::renderEnd(Swapchain & swapchain, const Pipeline & pipeline)
{
    const LogicalDevice & device = swapchain.getParentLogicalDevice();
    const vk::Device & logicalDevice = device.getVkLogicalDevice();

    m_commandBuffer.endRender(m_imageIndex);

    if (swapchain.getVkFenceInFlight(m_imageIndex))
    {
        logicalDevice.waitForFences(1, &swapchain.getVkFenceInFlight(m_imageIndex), true, UINT64_MAX);
    }
    swapchain.setVkFenceInFlight(m_imageIndex, swapchain.getVkFence(m_currentFrame));

    vk::SubmitInfo submitInfo{};
    vk::Semaphore waitSemaphores[] = {swapchain.getVkImageAvaibleSemaphore(m_currentFrame)};
    vk::Semaphore signalSemaphores[] = {swapchain.getVkRenderFinishSemaphore(m_currentFrame)};
    vk::PipelineStageFlags waitStages[] = {vk::PipelineStageFlagBits::eColorAttachmentOutput};

    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &m_commandBuffer.getCommandBuffer(m_imageIndex);
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;

    logicalDevice.resetFences(1, &swapchain.getVkFence(m_currentFrame));

    vk::Result result = device
                        .getGraphicQueue()
                        .getVkQueue()
                        .submit(1, &submitInfo,swapchain.getVkFence(m_currentFrame));
    if (result != vk::Result::eSuccess)
    {
        throw std::runtime_error("Error failed to submit draw command buffer");
    }
    vk::PresentInfoKHR presentInfo{};
    vk::SwapchainKHR swapchains[] = {swapchain.getVkSwapchain()};

    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapchains;
    presentInfo.pImageIndices = &m_imageIndex;
    result = device.getPresentQueue().getVkQueue().presentKHR(presentInfo);
    if (result == vk::Result::eErrorOutOfDateKHR || result == vk::Result::eSuboptimalKHR)
    {
        return false;
    } else if (result != vk::Result::eSuccess)
    {
        throw std::runtime_error("Error to prensent swap chain image !");
    }
    m_currentFrame = (m_currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
    return true;
}