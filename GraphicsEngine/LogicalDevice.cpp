//
// Created by tangt on 12/10/2020.
//
// Class that represente the logical device, use for queue and pipeline instancing
//

#include "LogicalDevice.h"
#include "PhysicalDevice.h"
#include "QueueFamilyHint.h"
#include "ValidationLayer.h"
#include "Instance.h"
#include "CommandPool.h"
#include <set>

graphics::LogicalDevice::LogicalDevice(const graphics::PhysicalDevice &physicalDevice):
m_parentPhysicalDevice(physicalDevice)
{
    initializeInternal();
    initializeDescriptorLayout();
    m_commandPool.initialize(*this);
}

void graphics::LogicalDevice::release()
{
    m_commandPool.release(*this);
    m_logicalDevice.destroy(nullptr);
}

const vk::Device & graphics::LogicalDevice::getVkLogicalDevice() const
{
    return m_logicalDevice;
}

const graphics::PhysicalDevice & graphics::LogicalDevice::getParentPhysicalDevice() const
{
    return m_parentPhysicalDevice;
}

const graphics::Queue & graphics::LogicalDevice::getGraphicQueue() const
{
    return m_graphicQueue;
}

const graphics::Queue & graphics::LogicalDevice::getPresentQueue() const
{
    return m_presentQueue;
}

vk::ImageView graphics::LogicalDevice::createVkImageView(const vk::Image &image,
                                                         const vk::Format &format,
                                                         vk::ImageAspectFlags aspect,
                                                         uint32_t mipLevel /* = 1 */) const
{
    vk::ImageViewCreateInfo imageViewInfo{};

    imageViewInfo.image = image;
    imageViewInfo.viewType = vk::ImageViewType::e2D;
    imageViewInfo.format = format;
    imageViewInfo.subresourceRange.aspectMask = aspect;
    imageViewInfo.subresourceRange.baseArrayLayer = 0;
    imageViewInfo.subresourceRange.baseMipLevel = 0;
    imageViewInfo.subresourceRange.levelCount = mipLevel;
    imageViewInfo.subresourceRange.layerCount = 1;

    return m_logicalDevice.createImageView(imageViewInfo);
}

const vk::DescriptorSetLayout & graphics::LogicalDevice::getDescriptorSetLayout() const
{
    return m_descriptorLayout;
}

const graphics::CommandPool & graphics::LogicalDevice::getCommandPool() const
{
    return m_commandPool;
}

void graphics::LogicalDevice::initializeInternal()
{
    QueueFamilyHint hints(m_parentPhysicalDevice);
    std::vector<vk::DeviceQueueCreateInfo> queueInfos;
    std::set<uint32_t> uniqueQueueFamily = {hints.getGraphicsFamilyValue(), hints.getPresentFamilyValue()};
    float queuePriority = 1.f;

    for (uint32_t queueFamily : uniqueQueueFamily)
    {
        vk::DeviceQueueCreateInfo queueInfo{};

        queueInfo.queueFamilyIndex = queueFamily;
        queueInfo.queueCount = 1;
        queueInfo.pQueuePriorities  = &queuePriority;
        queueInfos.push_back(queueInfo);
    }

    vk::PhysicalDeviceFeatures featues{};
    vk::DeviceCreateInfo deviceInfo{};
    const std::vector<const char *> deviceExtension = m_parentPhysicalDevice.getDeviceExtensions();

    featues.samplerAnisotropy = true;
    deviceInfo.queueCreateInfoCount = static_cast<uint32_t>(queueInfos.size());
    deviceInfo.pQueueCreateInfos = queueInfos.data();
    deviceInfo.pEnabledFeatures = &featues;
    deviceInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtension.size());
    deviceInfo.ppEnabledExtensionNames = deviceExtension.data();
    if (ENGINE_DEBUG)
    {
        const std::vector<const char *> & layerName = m_parentPhysicalDevice.getParentInstance().getValidationLayer().getValidationLayerNames();

        deviceInfo.enabledLayerCount = 1;
        deviceInfo.ppEnabledLayerNames = layerName.data();
    } else {
        deviceInfo.enabledLayerCount = 0;
        deviceInfo.ppEnabledLayerNames = nullptr;
    }

    m_logicalDevice = m_parentPhysicalDevice.getVkPhysicalDevice().createDevice(deviceInfo);

    if (!m_logicalDevice)
    {
        throw std::runtime_error("Error while creating logical device");
    }
    m_graphicQueue = Queue(m_logicalDevice.getQueue(hints.getGraphicsFamilyValue(), 0));
    m_presentQueue = Queue(m_logicalDevice.getQueue(hints.getPresentFamilyValue(), 0));
}

void graphics::LogicalDevice::initializeDescriptorLayout()
{
    vk::DescriptorSetLayoutBinding uboBinding{};
    vk::DescriptorSetLayoutBinding samplerBinding{};

    uboBinding.binding = 0;
    uboBinding.descriptorType = vk::DescriptorType::eUniformBuffer;
    uboBinding.descriptorCount = 1;
    uboBinding.stageFlags = vk::ShaderStageFlagBits::eVertex;
    uboBinding.pImmutableSamplers = nullptr;

    samplerBinding.binding = 1;
    samplerBinding.descriptorType = vk::DescriptorType::eCombinedImageSampler;
    samplerBinding.stageFlags = vk::ShaderStageFlagBits::eFragment;
    samplerBinding.pImmutableSamplers = nullptr;

    std::array<vk::DescriptorSetLayoutBinding, 2> bindings = {uboBinding, samplerBinding};
    vk::DescriptorSetLayoutCreateInfo layoutInfo{};

    layoutInfo.bindingCount = static_cast<uint32_t>(bindings.size());
    layoutInfo.pBindings = bindings.data();
    m_descriptorLayout = m_logicalDevice.createDescriptorSetLayout(layoutInfo);
    if (m_descriptorLayout == nullptr)
    {
        throw std::runtime_error("Error while creating descriptor set layout");
    }
}

void graphics::LogicalDevice::createVkImage(uint32_t width, uint32_t height, uint32_t mipLevel,
                                            vk::SampleCountFlagBits numSample, vk::Format format,
                                            vk::ImageTiling tiling, vk::ImageUsageFlags usages,
                                            vk::MemoryPropertyFlagBits properties, vk::Image &image,
                                            vk::DeviceMemory &memory) const
{
    vk::ImageCreateInfo imageInfo{};

    imageInfo.imageType = vk::ImageType::e2D;
    imageInfo.extent.width = width;
    imageInfo.extent.height = height;
    imageInfo.extent.depth = 1;
    imageInfo.mipLevels = mipLevel;
    imageInfo.arrayLayers = 1;
    imageInfo.format = format;
    imageInfo.tiling = tiling;
    imageInfo.initialLayout = vk::ImageLayout::eUndefined;
    imageInfo.usage = usages;
    imageInfo.sharingMode = vk::SharingMode::eExclusive;
    imageInfo.samples = numSample;
    imageInfo.flags = static_cast<vk::ImageCreateFlags>(0);
    image = m_logicalDevice.createImage(imageInfo);

    if (!image)
    {
        throw std::runtime_error("Error while create image");
    }

    vk::MemoryRequirements memoryRequirements = m_logicalDevice.getImageMemoryRequirements(image);
    vk::MemoryAllocateInfo allocateInfo{};

    allocateInfo.allocationSize = memoryRequirements.size;
    allocateInfo.memoryTypeIndex = m_parentPhysicalDevice.findMemoryType(memoryRequirements.memoryTypeBits, properties);
    memory = m_logicalDevice.allocateMemory(allocateInfo);
    if (!memory)
    {
        throw std::runtime_error("Error while allocate memory");
    }
    m_logicalDevice.bindImageMemory(image, memory, 0);
}

void graphics::LogicalDevice::createVkBuffer(vk::DeviceSize size, vk::BufferUsageFlags usages,
                                             vk::MemoryPropertyFlags properties, vk::Buffer &buffer,
                                             vk::DeviceMemory &memory) const
{
    vk::BufferCreateInfo bufferInfo{};

    bufferInfo.size = size;
    bufferInfo.usage = usages;
    bufferInfo.sharingMode = vk::SharingMode::eExclusive;
    buffer = m_logicalDevice.createBuffer(bufferInfo);
    if (!buffer)
    {
        throw std::runtime_error("Error while creating buffer");
    }

    vk::MemoryRequirements requirements = m_logicalDevice.getBufferMemoryRequirements(buffer);
    vk::MemoryAllocateInfo allocationInfo{};

    allocationInfo.allocationSize = requirements.size;
    allocationInfo.memoryTypeIndex = m_parentPhysicalDevice.findMemoryType(requirements.memoryTypeBits, properties);
    memory = m_logicalDevice.allocateMemory(allocationInfo);
    if (!memory)
    {
        throw std::runtime_error("Error while allocating buffer memory");
    }
    m_logicalDevice.bindBufferMemory(buffer, memory, 0);
}

void graphics::LogicalDevice::copyVkBuffer(const vk::Buffer &srcBuffer, const vk::Buffer &dstBuffer, uint64_t size) const
{
    vk::CommandBuffer commandBuffer = beginVkSingleTimeBuffer();
    vk::BufferCopy bufferCopy{};

    bufferCopy.size = size;
    bufferCopy.srcOffset = 0;
    bufferCopy.dstOffset = 0;
    commandBuffer.copyBuffer(srcBuffer, dstBuffer, 1, &bufferCopy);
    endVkSingleTimeBuffer(commandBuffer);
}

vk::CommandBuffer graphics::LogicalDevice::beginVkSingleTimeBuffer() const {
    vk::CommandBufferAllocateInfo commandBufferInfo{};

    commandBufferInfo.level = vk::CommandBufferLevel::ePrimary;
    commandBufferInfo.commandBufferCount = 1;
    commandBufferInfo.commandPool = m_commandPool.getVkCommandPool();

    vk::CommandBuffer commandBuffer = m_logicalDevice.allocateCommandBuffers(commandBufferInfo)[0];
    vk::CommandBufferBeginInfo beginInfo{};

    beginInfo.flags = vk::CommandBufferUsageFlagBits::eOneTimeSubmit;
    commandBuffer.begin(beginInfo);
    return commandBuffer;
}

void graphics::LogicalDevice::endVkSingleTimeBuffer(const vk::CommandBuffer &commandBuffer) const
{
    commandBuffer.end();

    vk::SubmitInfo info{};

    info.commandBufferCount = 1;
    info.pCommandBuffers = &commandBuffer;
    m_graphicQueue.getVkQueue().submit(1, &info, nullptr);
    m_graphicQueue.getVkQueue().waitIdle();
    m_logicalDevice.freeCommandBuffers(m_commandPool.getVkCommandPool(), 1, &commandBuffer);
}