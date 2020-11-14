//
// Created by tangt on 26/10/2020.
//

#include "GraphicsEngine/Renderer.h"
#include "GraphicsEngine/Swapchain.h"
#include "GraphicsEngine/LogicalDevice.h"
#include "GraphicsEngine/Pipeline.h"
#include "GraphicsEngine/SceneManager.h"
#include "GraphicsEngine/Scene.h"
#include "GraphicsEngine/SUniformBufferObject.h"
#include "GraphicsEngine/Camera.h"
#include "GraphicsEngine/CameraManager.h"

graphics::Renderer::Renderer():
m_currentFrame(0),
m_imageIndex(0),
m_projection()
{
    m_commandBuffer.initialize();
}

bool graphics::Renderer::render(Swapchain &swapchain, const Pipeline &pipeline)
{
    if (!renderBegin(swapchain))
    {
        return false;
    }

    object::Scene * scene = object::SceneManager::getInstance()->getCurrentScene();
    std::vector<object::GameObject *> sceneObject = scene->getSceneObjects();

    Math::Matrix4F viewMatrix = MATRIX4F_IDENTITY;
    object::Camera * camera = scene->getCurrentCamera();

    if (nullptr != camera)
    {
        viewMatrix = camera->getViewMatrix();
    }

    for (object::GameObject * object : sceneObject)
    {
        renderElement(swapchain, object, pipeline, m_projection, viewMatrix);
    }
    return renderEnd(swapchain, pipeline);
}

void graphics::Renderer::setProjectionMatrix(const Math::Matrix4F &projection)
{
    m_projection = projection;
}

bool graphics::Renderer::renderBegin(Swapchain & swapchain)
{
    const vk::Device & logicalDevice = LogicalDevice::getInstance()->getVkLogicalDevice();

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

void graphics::Renderer::renderElement(Swapchain & swapchain,
                                       const object::GameObject * object,
                                       const Pipeline & pipeline,
                                       const Math::Matrix4F & projectionMatrix,
                                       const Math::Matrix4F & viewMatrix)
{
    LogicalDevice * logicalDevice = LogicalDevice::getInstance();

    m_commandBuffer.render(swapchain,
                           logicalDevice->getCommandPool(),
                           pipeline,
                           object,
                           m_imageIndex,
                           m_projection,
                           viewMatrix);
}

bool graphics::Renderer::renderEnd(Swapchain & swapchain, const Pipeline & pipeline)
{
    LogicalDevice * device = LogicalDevice::getInstance();
    const vk::Device & logicalDevice = device->getVkLogicalDevice();

    m_commandBuffer.endRender(m_imageIndex, swapchain);

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
                        ->getGraphicQueue()
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
    try
    {
        result = device->getPresentQueue().getVkQueue().presentKHR(presentInfo);
    } catch (const vk::OutOfDateKHRError & e) {
        return false;
    }
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

void graphics::Renderer::release()
{
    m_commandBuffer.release();
}

void graphics::Renderer::initialize()
{
    m_commandBuffer.initialize();
}