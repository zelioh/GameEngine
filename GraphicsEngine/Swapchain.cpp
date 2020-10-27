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
#include "Texture.h"
#include "Window.h"

graphics::Swapchain::Swapchain(const LogicalDevice & logicalDevice, const Window & window):
m_parentLogicalDevice(logicalDevice),
m_renderPass()
{
    initialize(window);
}

void graphics::Swapchain::initialize(const Window & window)
{
    initializeInternal(window);
    initializeImageViews();
    m_renderPass.initialize(*this);
    initializeFrameBuffer();
    createUniformBuffers();
    createDescriptorPool();
    createDescriptorSet(Texture()); ///< TODO: use object TextureTODO
    initializeSyncObj();
}

void graphics::Swapchain::release()
{
    const vk::Device & logicalDevice = m_parentLogicalDevice.getVkLogicalDevice();

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

    m_renderPass.release(*this);
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
}


void graphics::Swapchain::recreate(const Window & window)
{
    const vk::Device & logicalDevice = m_parentLogicalDevice.getVkLogicalDevice();

    logicalDevice.waitIdle();
    {
        logicalDevice.destroyImage(m_colorImage);
        logicalDevice.destroyImageView(m_colorView);
        logicalDevice.freeMemory(m_colorMemory);

        logicalDevice.destroyImage(m_depthImage);
        logicalDevice.destroyImageView(m_depthView);
        logicalDevice.freeMemory(m_depthMemory);

        for (const vk::Framebuffer &framebuffer : m_vFrameBuffer) {
            logicalDevice.destroyFramebuffer(framebuffer);
        }

        m_renderPass.release(*this);
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
    }
    ///< TODO: destroy command pool and pipeline
    initializeInternal(window);
    initializeImageViews();
    m_renderPass.initialize(*this);
    createColorResources();
    createDepthResources();
    initializeFrameBuffer();
    createUniformBuffers();
    createDescriptorPool();
    createDescriptorSet(Texture()); ///< TODO: remove
    ///< TODO: create pipeline, command pool
}

const graphics::LogicalDevice & graphics::Swapchain::getParentLogicalDevice() const
{
    return m_parentLogicalDevice;
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

const vk::Buffer & graphics::Swapchain::getVkVertexBuffer() const
{
    return m_vertexBuffer;
}

const vk::Buffer & graphics::Swapchain::getVkIndexBuffer() const
{
    return m_indexBuffer;
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

const vk::DescriptorSet & graphics::Swapchain::getVkDescriptorSet(int iIndex) const
{
    return m_descriptorSets[iIndex];
}

uint32_t graphics::Swapchain::acquireNextImage(size_t currentFrame) const
{
    return m_parentLogicalDevice.getVkLogicalDevice().acquireNextImageKHR(m_swapchain,
                                                                   UINT64_MAX,
                                                                   m_imageAvaibleSemaphores[currentFrame],
                                                                   nullptr);
}

void graphics::Swapchain::initializeVertexIndexBuffers(const std::vector<Vertex> &vertices,
                                                       const std::vector<uint32_t> &indices)
{
    createVertexBuffer(vertices);
    createIndexBuffer(indices);
}

void graphics::Swapchain::releaseVertexIndexBuffers()
{
    const vk::Device & logicalDevice = m_parentLogicalDevice.getVkLogicalDevice();

    logicalDevice.destroyBuffer(m_vertexBuffer);
    logicalDevice.freeMemory(m_verterBufferMemory);

    logicalDevice.destroyBuffer(m_indexBuffer);
    logicalDevice.freeMemory(m_indexBufferMemory);
}

void graphics::Swapchain::updateUniformBuffer(int imageIndex, const SUniformBufferObject &ubo) const
{
    const vk::Device & logicalDevice = m_parentLogicalDevice.getVkLogicalDevice();
    void *data;

    logicalDevice.mapMemory(m_uniformBufferMemories[imageIndex], 0, sizeof(ubo), static_cast<vk::MemoryMapFlags>(0), &data);
    memcpy(data, &ubo, sizeof(ubo));
    logicalDevice.unmapMemory(m_uniformBufferMemories[imageIndex]);
}

void graphics::Swapchain::initializeInternal(const Window & window)
{
    SwapchainDetails details(m_parentLogicalDevice.getParentPhysicalDevice());
    vk::SurfaceFormatKHR format = chooseSwapchainFormat(details.getSurfaceFormats());
    vk::PresentModeKHR presentMode = chooseSwapchainPrensentMode(details.getPrensentModes());
    vk::SurfaceCapabilitiesKHR capabilities = details.getSurfaceCapabilities();
    vk::Extent2D surfaceExtent = chooseSwapchainExtent(capabilities, window);
    uint32_t imageCount = capabilities.minImageCount + 1;
    QueueFamilyHint hints(m_parentLogicalDevice.getParentPhysicalDevice());
    uint32_t queueFamilyHints[] = {hints.getGraphicsFamilyValue(), hints.getPresentFamilyValue()};
    vk::SwapchainCreateInfoKHR swapchainInfo{};

    if (0 < capabilities.maxImageCount && imageCount > capabilities.maxImageCount)
    {
        imageCount = capabilities.maxImageCount;
    }
    swapchainInfo.surface = m_parentLogicalDevice.getParentPhysicalDevice().getParentInstance().getSurface().getVulkanSurface();
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

    m_swapchain = m_parentLogicalDevice.getVkLogicalDevice().createSwapchainKHR(swapchainInfo);
    if (!m_swapchain)
    {
        throw std::runtime_error("Error while creating swapchain");
    }
    m_vImages = m_parentLogicalDevice.getVkLogicalDevice().getSwapchainImagesKHR(m_swapchain);
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

    m_vImageViews.resize(count);
    for (size_t i = 0; i < count; ++i)
    {
        m_vImageViews[i] = m_parentLogicalDevice.createVkImageView(m_vImages[i], m_format, vk::ImageAspectFlagBits::eColor);
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
        m_vFrameBuffer[i] = m_parentLogicalDevice.getVkLogicalDevice().createFramebuffer(framebufferInfo);
        if (!m_vFrameBuffer[i])
        {
            throw std::runtime_error("Error while creating framebuffer");
        }
    }
}

void graphics::Swapchain::createColorResources()
{
    m_parentLogicalDevice.createVkImage(m_extent.width, m_extent.height,
                                        1,
                                        m_parentLogicalDevice.getParentPhysicalDevice().getVkMSSASample(),
                                        m_format,
                                        vk::ImageTiling::eOptimal,
                                        vk::ImageUsageFlagBits::eTransientAttachment | vk::ImageUsageFlagBits::eColorAttachment,
                                        vk::MemoryPropertyFlagBits::eDeviceLocal,
                                        m_colorImage, m_colorMemory);
    m_colorView = m_parentLogicalDevice.createVkImageView(m_colorImage, m_format, vk::ImageAspectFlagBits::eColor, 1);
}

void graphics::Swapchain::createDepthResources()
{
    vk::Format format = m_parentLogicalDevice
            .getParentPhysicalDevice()
            .findVkSupportedFormat(
                    {vk::Format::eD32Sfloat, vk::Format::eD32SfloatS8Uint, vk::Format::eD24UnormS8Uint},
                    vk::ImageTiling::eOptimal,
                    vk::FormatFeatureFlagBits::eDepthStencilAttachment);


    m_parentLogicalDevice.createVkImage(m_extent.width, m_extent.height,
                                        1,
                                        m_parentLogicalDevice.getParentPhysicalDevice().getVkMSSASample(),
                                        format,
                                        vk::ImageTiling::eOptimal,
                                        vk::ImageUsageFlagBits::eDepthStencilAttachment,
                                        vk::MemoryPropertyFlagBits::eDeviceLocal,
                                        m_depthImage, m_depthMemory);
    m_depthView = m_parentLogicalDevice.createVkImageView(m_depthImage, format, vk::ImageAspectFlagBits::eDepth, 1);
}

void graphics::Swapchain::createVertexBuffer(const std::vector<Vertex> &vertices)
{
    vk::DeviceSize size = sizeof(vertices[0]) * vertices.size();
    void *data;
    vk::Buffer stageBuffer;
    vk::DeviceMemory stageBufferMemory;
    const vk::Device & logicalDevice = m_parentLogicalDevice.getVkLogicalDevice();

    m_parentLogicalDevice.createVkBuffer(size,
                                         vk::BufferUsageFlagBits::eTransferSrc,
                                         vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent,
                                         stageBuffer,
                                         stageBufferMemory);
    logicalDevice.mapMemory(stageBufferMemory, 0, size, static_cast<vk::MemoryMapFlags>(0), &data);
    memcpy(data, vertices.data(), static_cast<size_t>(size));
    logicalDevice.unmapMemory(stageBufferMemory);
    m_parentLogicalDevice.createVkBuffer(size,
                                         vk::BufferUsageFlagBits::eTransferDst | vk::BufferUsageFlagBits::eVertexBuffer,
                                         vk::MemoryPropertyFlagBits::eDeviceLocal,
                                         m_vertexBuffer,
                                         m_verterBufferMemory);
    m_parentLogicalDevice.copyVkBuffer(stageBuffer, m_vertexBuffer, size);
    logicalDevice.destroyBuffer(stageBuffer);
    logicalDevice.freeMemory(stageBufferMemory);
}

void graphics::Swapchain::createIndexBuffer(const std::vector<uint32_t> &indices)
{
    vk::DeviceSize size = sizeof(indices[0]) * indices.size();
    void *data;
    vk::Buffer stageBuffer;
    vk::DeviceMemory stageBufferMemory;
    const vk::Device & logicalDevice = m_parentLogicalDevice.getVkLogicalDevice();

    m_parentLogicalDevice.createVkBuffer(size,
                                         vk::BufferUsageFlagBits::eTransferSrc,
                                         vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent,
                                         stageBuffer,
                                         stageBufferMemory);
    logicalDevice.mapMemory(stageBufferMemory, 0, size, static_cast<vk::MemoryMapFlags>(0), &data);
    memcpy(data, indices.data(), static_cast<size_t>(size));
    logicalDevice.unmapMemory(stageBufferMemory);
    m_parentLogicalDevice.createVkBuffer(size,
                                         vk::BufferUsageFlagBits::eTransferDst | vk::BufferUsageFlagBits::eIndexBuffer,
                                         vk::MemoryPropertyFlagBits::eDeviceLocal,
                                         m_indexBuffer,
                                         m_indexBufferMemory);
    m_parentLogicalDevice.copyVkBuffer(stageBuffer, m_indexBuffer, size);
    logicalDevice.destroyBuffer(stageBuffer);
    logicalDevice.freeMemory(stageBufferMemory);
}

void graphics::Swapchain::createUniformBuffers()
{
    vk::DeviceSize size = sizeof(SUniformBufferObject);
    const size_t buffersize = m_vImages.size();

    m_uniformBuffers.resize(buffersize);
    m_uniformBufferMemories.resize(buffersize);
    for (size_t i = 0; i < buffersize; ++i)
    {
        m_parentLogicalDevice.createVkBuffer(size,
                                             vk::BufferUsageFlagBits::eUniformBuffer,
                                             vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent,
                                             m_uniformBuffers[i],
                                             m_uniformBufferMemories[i]);
    }
}


void graphics::Swapchain::createDescriptorPool()
{
    std::array<vk::DescriptorPoolSize, 2> poolSizes{};

    poolSizes[0].descriptorCount = static_cast<uint32_t>(m_vImages.size());
    poolSizes[1].descriptorCount = static_cast<uint32_t>(m_vImages.size());

    vk::DescriptorPoolCreateInfo poolInfo{};

    poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
    poolInfo.pPoolSizes = poolSizes.data();
    poolInfo.maxSets = static_cast<uint32_t>(m_vImages.size());

    if (!(m_descriptorPool = m_parentLogicalDevice.getVkLogicalDevice().createDescriptorPool(poolInfo)))
    {
        throw std::runtime_error("Error while creating pool descriptor");
    }
}

void graphics::Swapchain::createDescriptorSet(const Texture & texture)
{
    const size_t size = m_vImages.size();
    std::vector<vk::DescriptorSetLayout> layouts(size, m_parentLogicalDevice.getDescriptorSetLayout());
    vk::DescriptorSetAllocateInfo allocateInfo{};
    const vk::Device & logicalDevice = m_parentLogicalDevice.getVkLogicalDevice();

    allocateInfo.descriptorPool = m_descriptorPool;
    allocateInfo.descriptorSetCount = size;
    allocateInfo.pSetLayouts = layouts.data();
    m_descriptorSets.resize(size);
    m_descriptorSets = logicalDevice.allocateDescriptorSets(allocateInfo);
    for (size_t i = 0; i < size; ++i)
    {
        vk::DescriptorBufferInfo bufferInfo{};

        bufferInfo.buffer = m_uniformBuffers[i];
        bufferInfo.offset = 0;
        bufferInfo.range = sizeof(SUniformBufferObject);

        vk::DescriptorImageInfo imageInfo{};

        imageInfo.sampler = texture.getVkTextureSampler();
        imageInfo.imageView = texture.getVkTextureView();
        imageInfo.imageLayout = vk::ImageLayout::eShaderReadOnlyOptimal;

        if (texture.getVkTextureView() == nullptr)
        {
            vk::WriteDescriptorSet writeSet;

            writeSet.dstSet = m_descriptorSets[i];
            writeSet.dstBinding = 0;
            writeSet.dstArrayElement = 0;
            writeSet.descriptorType = vk::DescriptorType::eUniformBuffer;
            writeSet.descriptorCount = 1;
            writeSet.pBufferInfo = &bufferInfo;
            writeSet.pImageInfo = nullptr;
            writeSet.pTexelBufferView = nullptr;

            logicalDevice.updateDescriptorSets(1, &writeSet, 0, nullptr);
        } else {
            std::array<vk::WriteDescriptorSet, 2> writeSets{};

            writeSets[0].dstSet = m_descriptorSets[i];
            writeSets[0].dstBinding = 0;
            writeSets[0].dstArrayElement = 0;
            writeSets[0].descriptorType = vk::DescriptorType::eUniformBuffer;
            writeSets[0].descriptorCount = 1;
            writeSets[0].pBufferInfo = &bufferInfo;
            writeSets[0].pImageInfo = nullptr;
            writeSets[0].pTexelBufferView = nullptr;
            writeSets[1].dstSet = m_descriptorSets[i];
            writeSets[1].dstBinding = 1;
            writeSets[1].dstArrayElement = 0;
            writeSets[1].descriptorType = vk::DescriptorType::eCombinedImageSampler;
            writeSets[1].descriptorCount = 1;
            writeSets[1].pBufferInfo = nullptr;
            writeSets[1].pImageInfo = &imageInfo;
            writeSets[1].pTexelBufferView = nullptr;

            logicalDevice.updateDescriptorSets(writeSets.size(), writeSets.data(), 0, nullptr);
        }
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

    vk::Device logicalDevice = m_parentLogicalDevice.getVkLogicalDevice();

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