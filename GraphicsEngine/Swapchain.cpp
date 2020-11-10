//
// Created by tangt on 12/10/2020.
//
// Class that represent the swapchain, use for send the render informations to the surface
//

#include "Swapchain.h"
#include "LogicalDevice.h"
#include "PhysicalDevice.h"
#include "SwapchainDetails.h"
#include "QueueFamilyHint.h"
#include "Instance.h"
#include "Vertex.h"
#include "SUniformBufferObject.h"
#include "Window.h"
#include "Pipeline.h"
#include "Renderer.h"
#include "public/GraphicsEngine/TextureManager.h"

graphics::Swapchain * graphics::Swapchain::getInstance()
{
    static Swapchain * swapchain = nullptr;

    if (nullptr == swapchain)
    {
        swapchain = new Swapchain();
    }
    return swapchain;
}

graphics::Swapchain::Swapchain()
{
}

void graphics::Swapchain::initialize(const Window & window)
{
    initializeInternal(window);
    initializeImageViews();
    m_renderPass.initialize();
    initializeFrameBuffer();
    createUniformBuffers();
    createDescriptorPool();
    initializeSyncObj();
}

void graphics::Swapchain::release()
{
    const vk::Device & logicalDevice = LogicalDevice::getInstance()->getVkLogicalDevice();

    for (int i = 0; i < MAX_FRAMES_IN_FLIGHT; ++i)
    {
        logicalDevice.destroySemaphore(m_imageAvaibleSemaphores[i]);
        logicalDevice.destroySemaphore(m_renderFinishSemaphores[i]);
        logicalDevice.destroyFence(m_fences[i]);
    }

    logicalDevice.destroyImage(m_colorImage);
    logicalDevice.destroyImageView(m_colorView);
    logicalDevice.freeMemory(m_colorMemory);

    logicalDevice.destroyImage(m_depthImage);
    logicalDevice.destroyImageView(m_depthView);
    logicalDevice.freeMemory(m_depthMemory);

    for (const vk::Framebuffer & framebuffer : m_vFrameBuffer)
    {
        logicalDevice.destroyFramebuffer(framebuffer);
    }

    m_renderPass.release();
    for (const vk::ImageView & imageView : m_vImageViews)
    {
        logicalDevice.destroyImageView(imageView);
    }
    logicalDevice.destroySwapchainKHR(m_swapchain);

    const size_t count = m_vImages.size();

    for (size_t i = 0; i < count; ++i)
    {
        logicalDevice.destroyBuffer(m_uniformBuffers[i]);
        logicalDevice.freeMemory(m_uniformBufferMemories[i]);
    }
    logicalDevice.destroyDescriptorPool(m_descriptorPool);
}


void graphics::Swapchain::recreate(const Window & window, graphics::Pipeline & pipeline, Renderer & renderer)
{
    const vk::Device & logicalDevice = LogicalDevice::getInstance()->getVkLogicalDevice();

    logicalDevice.waitIdle();
    logicalDevice.destroyImageView(m_depthView);
    logicalDevice.destroyImage(m_depthImage);
    logicalDevice.freeMemory(m_depthMemory);

    logicalDevice.destroyImageView(m_colorView);
    logicalDevice.destroyImage(m_colorImage);
    logicalDevice.freeMemory(m_colorMemory);

    for (const vk::Framebuffer &framebuffer : m_vFrameBuffer) {
        logicalDevice.destroyFramebuffer(framebuffer);
    }

    renderer.release();
    pipeline.release();
    m_renderPass.release();

    for (const vk::ImageView &imageView : m_vImageViews) {
        logicalDevice.destroyImageView(imageView);
    }

    logicalDevice.destroySwapchainKHR(m_swapchain);

    const size_t count = m_vImages.size();

    for (size_t i = 0; i < count; ++i) {
        logicalDevice.destroyBuffer(m_uniformBuffers[i]);
        logicalDevice.freeMemory(m_uniformBufferMemories[i]);
    }

    logicalDevice.destroyDescriptorPool(m_descriptorPool);

    initializeInternal(window);
    initializeImageViews();
    m_renderPass.initialize();
    pipeline.initialize();
    initializeFrameBuffer();
    createUniformBuffers();
    createDescriptorPool();
    TextureManager::getInstance()->windowSizeChanged();
    renderer.initialize();
}

const vk::SwapchainKHR & graphics::Swapchain::getVkSwapchain() const
{
    return m_swapchain;
}

const std::vector<vk::Image> & graphics::Swapchain::getVkSwapchainImage() const
{
    return m_vImages;
}

const vk::Format & graphics::Swapchain::getVkSwapchainFormat() const
{
    return m_format;
}

const vk::Extent2D & graphics::Swapchain::getVkSwapchainExtent() const
{
    return m_extent;
}

const std::vector<vk::Framebuffer> & graphics::Swapchain::getVkFrameBuffers() const
{
    return m_vFrameBuffer;
}

const vk::Semaphore & graphics::Swapchain::getVkImageAvaibleSemaphore(int iIndex) const
{
    return m_imageAvaibleSemaphores[iIndex];
}

const vk::Semaphore & graphics::Swapchain::getVkRenderFinishSemaphore(int iIndex) const
{
    return m_renderFinishSemaphores[iIndex];
}

const vk::Fence & graphics::Swapchain::getVkFence(int iIndex) const
{
    return m_fences[iIndex];
}

const vk::Fence & graphics::Swapchain::getVkFenceInFlight(int iIndex) const
{
    return m_fencesInFlight[iIndex];
}

void graphics::Swapchain::setVkFenceInFlight(int iIndex, const vk::Fence &fence)
{
    m_fencesInFlight[iIndex] = fence;
}

const vk::DescriptorPool & graphics::Swapchain::getVkDescriptorPool() const
{
    return m_descriptorPool;
}

const vk::Buffer & graphics::Swapchain::getVkGetUniformBuffer(int iIndex) const
{
    return m_uniformBuffers[iIndex];
}

uint32_t graphics::Swapchain::acquireNextImage(size_t currentFrame) const
{
    const vk::Device & logicalDevice = LogicalDevice::getInstance()->getVkLogicalDevice();

    return logicalDevice.acquireNextImageKHR(m_swapchain,
                                             UINT64_MAX,
                                             m_imageAvaibleSemaphores[currentFrame],
                                             nullptr);
}

void graphics::Swapchain::updateUniformBuffer(int imageIndex, const SUniformBufferObject &ubo) const
{
    const vk::Device & logicalDevice = LogicalDevice::getInstance()->getVkLogicalDevice();
    void *data;

    logicalDevice.mapMemory(m_uniformBufferMemories[imageIndex], 0, sizeof(ubo), static_cast<vk::MemoryMapFlags>(0), &data);
    memcpy(data, &ubo, sizeof(ubo));
    logicalDevice.unmapMemory(m_uniformBufferMemories[imageIndex]);
}

void graphics::Swapchain::initializeInternal(const Window & window)
{
    Instance * instance = Instance::getInstance();
    graphics::PhysicalDevice * physicalDevice = PhysicalDevice::getInstance();

    SwapchainDetails details(*physicalDevice);
    vk::SurfaceFormatKHR format = chooseSwapchainFormat(details.getSurfaceFormats());
    vk::PresentModeKHR presentMode = chooseSwapchainPrensentMode(details.getPrensentModes());
    vk::SurfaceCapabilitiesKHR capabilities = details.getSurfaceCapabilities();
    vk::Extent2D surfaceExtent = chooseSwapchainExtent(capabilities, window);
    uint32_t imageCount = capabilities.minImageCount + 1;
    QueueFamilyHint hints(*physicalDevice);
    uint32_t queueFamilyHints[] = {hints.getGraphicsFamilyValue(), hints.getPresentFamilyValue()};
    vk::SwapchainCreateInfoKHR swapchainInfo{};

    if (0 < capabilities.maxImageCount && imageCount > capabilities.maxImageCount)
    {
        imageCount = capabilities.maxImageCount;
    }
    swapchainInfo.surface = instance->getSurface().getVulkanSurface();
    swapchainInfo.minImageCount = imageCount;
    swapchainInfo.imageFormat = format.format;
    swapchainInfo.presentMode = presentMode;
    swapchainInfo.imageExtent = surfaceExtent;
    swapchainInfo.imageColorSpace = format.colorSpace;
    swapchainInfo.imageArrayLayers = 1;
    swapchainInfo.imageUsage = vk::ImageUsageFlagBits::eColorAttachment;
    if (hints.getGraphicsFamilyValue() != hints.getPresentFamilyValue())
    {
        swapchainInfo.imageSharingMode = vk::SharingMode::eConcurrent;
        swapchainInfo.queueFamilyIndexCount = 2;
        swapchainInfo.pQueueFamilyIndices = queueFamilyHints;
    } else {
        swapchainInfo.imageSharingMode = vk::SharingMode::eExclusive;
        swapchainInfo.queueFamilyIndexCount = 0;
        swapchainInfo.pQueueFamilyIndices = nullptr;
    }
    swapchainInfo.preTransform = capabilities.currentTransform;
    swapchainInfo.compositeAlpha = vk::CompositeAlphaFlagBitsKHR::eOpaque;
    swapchainInfo.clipped = true;
    swapchainInfo.oldSwapchain = nullptr;

    const vk::Device & logicalDevice = LogicalDevice::getInstance()->getVkLogicalDevice();

    m_swapchain = logicalDevice.createSwapchainKHR(swapchainInfo);
    if (!m_swapchain)
    {
        throw std::runtime_error("Error while creating swapchain");
    }
    m_vImages = logicalDevice.getSwapchainImagesKHR(m_swapchain);
    m_format = format.format;
    m_extent = surfaceExtent;
}

const vk::SurfaceFormatKHR & graphics::Swapchain::chooseSwapchainFormat(
        const std::vector<vk::SurfaceFormatKHR> & formats)
{
    for (const vk::SurfaceFormatKHR & format : formats)
    {
        if (format.colorSpace == vk::ColorSpaceKHR::eVkColorspaceSrgbNonlinear &&
            format.format == vk::Format::eR8G8B8A8Srgb)
        {
            return format;
        }
    }
    return formats[0];
}

const vk::PresentModeKHR & graphics::Swapchain::chooseSwapchainPrensentMode(
        const std::vector<vk::PresentModeKHR> &presentModes)
{
    for (const vk::PresentModeKHR & presentMode : presentModes)
    {
        if (presentMode == vk::PresentModeKHR::eMailbox)
        {
            return presentMode;
        }
    }
    return presentModes[0];
}

vk::Extent2D graphics::Swapchain::chooseSwapchainExtent(const vk::SurfaceCapabilitiesKHR &capabilities, const Window & window)
{
    if (capabilities.currentExtent.width != UINT32_MAX)
    {
        return capabilities.currentExtent;
    } else {
        int width = window.getWidth(), height = window.getHeight();

        VkExtent2D currentExtent = {static_cast<uint32_t>(width), static_cast<uint32_t>(height)};

        currentExtent.width = max(capabilities.minImageExtent.width,
                                   min(capabilities.maxImageExtent.width, currentExtent.width));
        currentExtent.height = max(capabilities.minImageExtent.height,
                                   min(capabilities.maxImageExtent.height, currentExtent.height));
        return currentExtent;
    }
}

void graphics::Swapchain::initializeImageViews()
{
    const size_t count = m_vImages.size();
    LogicalDevice * logicalDevice = LogicalDevice::getInstance();

    m_vImageViews.resize(count);
    for (size_t i = 0; i < count; ++i)
    {
        m_vImageViews[i] = logicalDevice->createVkImageView(m_vImages[i], m_format, vk::ImageAspectFlagBits::eColor);
    }
}

const graphics::RenderPass & graphics::Swapchain::getRenderPass() const
{
    return m_renderPass;
}

void graphics::Swapchain::initializeFrameBuffer()
{
    createColorResources();
    createDepthResources();

    const int count = m_vImageViews.size();
    m_vFrameBuffer.resize(count);
    const vk::Device & logicalDevice = LogicalDevice::getInstance()->getVkLogicalDevice();

    for (int i = 0; i < count; ++i)
    {
        std::array<vk::ImageView, 3> attachments = {
                m_colorView,
                m_depthView,
                m_vImageViews[i]
        };
        vk::FramebufferCreateInfo framebufferInfo{};

        framebufferInfo.renderPass = m_renderPass.getVkRenderPass();
        framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
        framebufferInfo.pAttachments = attachments.data();
        framebufferInfo.layers = 1;
        framebufferInfo.width = m_extent.width;
        framebufferInfo.height = m_extent.height;
        m_vFrameBuffer[i] = logicalDevice.createFramebuffer(framebufferInfo);
        if (!m_vFrameBuffer[i])
        {
            throw std::runtime_error("Error while creating framebuffer");
        }
    }
}

void graphics::Swapchain::createColorResources()
{
    PhysicalDevice * physicalDevice = PhysicalDevice::getInstance();
    LogicalDevice * logicalDevice = LogicalDevice::getInstance();

    logicalDevice->createVkImage(m_extent.width, m_extent.height,
                                        1,
                                        physicalDevice->getVkMSSASample(),
                                        m_format,
                                        vk::ImageTiling::eOptimal,
                                        vk::ImageUsageFlagBits::eTransientAttachment | vk::ImageUsageFlagBits::eColorAttachment,
                                        vk::MemoryPropertyFlagBits::eDeviceLocal,
                                        m_colorImage, m_colorMemory);
    m_colorView = logicalDevice->createVkImageView(m_colorImage, m_format, vk::ImageAspectFlagBits::eColor, 1);
}

void graphics::Swapchain::createDepthResources()
{
    PhysicalDevice * physicalDevice = PhysicalDevice::getInstance();
    LogicalDevice * logicalDevice = LogicalDevice::getInstance();

    vk::Format format = physicalDevice->findVkSupportedFormat(
                    {vk::Format::eD32Sfloat, vk::Format::eD32SfloatS8Uint, vk::Format::eD24UnormS8Uint},
                    vk::ImageTiling::eOptimal,
                    vk::FormatFeatureFlagBits::eDepthStencilAttachment);


    logicalDevice->createVkImage(m_extent.width, m_extent.height,
                                        1,
                                        physicalDevice->getVkMSSASample(),
                                        format,
                                        vk::ImageTiling::eOptimal,
                                        vk::ImageUsageFlagBits::eDepthStencilAttachment,
                                        vk::MemoryPropertyFlagBits::eDeviceLocal,
                                        m_depthImage, m_depthMemory);
    m_depthView = logicalDevice->createVkImageView(m_depthImage, format, vk::ImageAspectFlagBits::eDepth, 1);
}

void graphics::Swapchain::createUniformBuffers()
{
    vk::DeviceSize size = sizeof(SUniformBufferObject);
    const size_t buffersize = m_vImages.size();
    LogicalDevice * logicalDevice = LogicalDevice::getInstance();

    m_uniformBuffers.resize(buffersize);
    m_uniformBufferMemories.resize(buffersize);
    for (size_t i = 0; i < buffersize; ++i)
    {
        logicalDevice->createVkBuffer(size,
                                             vk::BufferUsageFlagBits::eUniformBuffer,
                                             vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent,
                                             m_uniformBuffers[i],
                                             m_uniformBufferMemories[i]);
    }
}


void graphics::Swapchain::createDescriptorPool()
{
    std::array<vk::DescriptorPoolSize, 2> poolSizes{};

    poolSizes[0].descriptorCount = 64;
    poolSizes[0].type = vk::DescriptorType::eUniformBuffer;
    poolSizes[1].descriptorCount = 64;
    poolSizes[1].type = vk::DescriptorType::eCombinedImageSampler;

    vk::DescriptorPoolCreateInfo poolInfo{};

    poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
    poolInfo.pPoolSizes = poolSizes.data();
    poolInfo.maxSets = 64;
    poolInfo.flags = vk::DescriptorPoolCreateFlagBits::eFreeDescriptorSet;

    LogicalDevice * logicalDevice = LogicalDevice::getInstance();

    if (!(m_descriptorPool = logicalDevice->getVkLogicalDevice().createDescriptorPool(poolInfo)))
    {
        throw std::runtime_error("Error while creating pool descriptor");
    }
}

void graphics::Swapchain::initializeSyncObj()
{
    vk::SemaphoreCreateInfo semaphoreInfo{};
    vk::FenceCreateInfo fenceInfo{};

    m_imageAvaibleSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
    m_renderFinishSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
    m_fences.resize(MAX_FRAMES_IN_FLIGHT);
    m_fencesInFlight.resize(m_vImages.size(), nullptr);
    fenceInfo.flags = vk::FenceCreateFlagBits::eSignaled;

    vk::Device logicalDevice = LogicalDevice::getInstance()->getVkLogicalDevice();

    for (int i = 0; i < MAX_FRAMES_IN_FLIGHT; ++i)
    {
        m_imageAvaibleSemaphores[i] = logicalDevice.createSemaphore(semaphoreInfo);
        m_renderFinishSemaphores[i] = logicalDevice.createSemaphore(semaphoreInfo);
        m_fences[i] = logicalDevice.createFence(fenceInfo);
        if (!m_imageAvaibleSemaphores[i] || !m_renderFinishSemaphores[i] || !m_fences[i])
        {
            throw std::runtime_error("Error while creating fence and semaphore");
        }
    }
}