//
// Created by tangt on 20/10/2020.
//
// Contain texture data usable by the engine
//

#include "Texture.h"
#include "LogicalDevice.h"

graphics::Texture::Texture(const LogicalDevice & logicalDevice,
                           const std::string & name,
                           stbi_uc *pixels,
                           int width, int height, int channels):
m_strName(name),
m_iWidth(width),
m_iHeight(height),
m_iChannels(channels),
m_size(width * height * 4)
{
    initializeInternal(logicalDevice, pixels);
}

const std::string & graphics::Texture::getName() const
{
    return m_strName;
}

int graphics::Texture::getWidth() const
{
    return m_iWidth;
}

int graphics::Texture::getHeight() const
{
    return m_iHeight;
}

int graphics::Texture::getChannels() const
{
    return m_iChannels;
}

vk::DeviceSize graphics::Texture::getVkSize() const
{
    return m_size;
}

const vk::Image & graphics::Texture::getVkTexture() const
{
    return m_texture;
}

const vk::DeviceMemory & graphics::Texture::getVkTextureMemory() const
{
    return m_textureMemory;
}

const vk::ImageView & graphics::Texture::getVkTextureView() const
{
    return m_textureView;
}

const vk::Sampler & graphics::Texture::getVkTextureSampler() const
{
    return m_textureSampler;
}

uint32_t graphics::Texture::getMipLevel() const
{
    return m_iMipLevel;
}

void graphics::Texture::initializeInternal(const graphics::LogicalDevice &logicalDevice, stbi_uc *pixels)
{
    vk::Buffer stageBuffer;
    vk::DeviceMemory stageMemory;
    void * data;
    const vk::Device & vkLogicalDevice = logicalDevice.getVkLogicalDevice();

    m_iMipLevel = static_cast<uint32_t>(std::floor(std::log2(std::max(m_iWidth, m_iHeight)))) + 1;

    logicalDevice.createVkBuffer(m_size,
                                 vk::BufferUsageFlagBits::eTransferSrc,
                                 vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent,
                                stageBuffer,
                                 stageMemory
    );
    vkLogicalDevice.mapMemory(stageMemory, 0, m_size, static_cast<vk::MemoryMapFlags>(0), &data);
    memcpy(data, pixels, static_cast<size_t>(m_size));
    vkLogicalDevice.unmapMemory(stageMemory);
    stbi_image_free(pixels);
    logicalDevice.createImage(m_iWidth,
                              m_iHeight,
                              m_iMipLevel,
                              vk::SampleCountFlagBits::e1,
                              vk::Format::eR8G8B8A8Srgb,
                              vk::ImageTiling::eOptimal,
                              vk::ImageUsageFlagBits::eTransferSrc | vk::ImageUsageFlagBits::eTransferDst | vk::ImageUsageFlagBits::eSampled,
                              vk::MemoryPropertyFlagBits::eDeviceLocal,
                              m_texture,
                              m_textureMemory
    );
    logicalDevice.transitionImageLayout(m_texture,
                                        vk::Format::eR8G8B8A8Srgb,
                                        vk::ImageLayout::eUndefined,
                                        vk::ImageLayout::eTransferDstOptimal,
                                        m_iMipLevel
    );
    logicalDevice.copyVkBufferToImage(stageBuffer, m_texture, m_iWidth, m_iHeight);
    vkLogicalDevice.destroyBuffer(stageBuffer);
    vkLogicalDevice.freeMemory(stageMemory);

    logicalDevice.generateMipmap(m_texture, vk::Format::eR8G8B8A8Srgb, m_iWidth, m_iHeight, m_iMipLevel);

    m_textureView = logicalDevice.createVkImageView(
            m_texture,
            vk::Format::eR8G8B8A8Srgb,
            vk::ImageAspectFlags(vk::ImageAspectFlagBits::eColor),
            m_iMipLevel
            );
    createSampler(vkLogicalDevice);
}

void graphics::Texture::createSampler(const vk::Device &logicalDevice)
{
    vk::SamplerCreateInfo samplerInfo{};

    samplerInfo.magFilter = vk::Filter::eLinear;
    samplerInfo.minFilter = vk::Filter::eLinear;
    samplerInfo.addressModeU = vk::SamplerAddressMode::eRepeat;
    samplerInfo.addressModeV = vk::SamplerAddressMode::eRepeat;
    samplerInfo.addressModeW = vk::SamplerAddressMode::eRepeat;
    samplerInfo.anisotropyEnable = VK_TRUE;
    samplerInfo.maxAnisotropy = 16;
    samplerInfo.borderColor = vk::BorderColor::eIntOpaqueBlack;
    samplerInfo.unnormalizedCoordinates = VK_FALSE;
    samplerInfo.compareEnable = VK_FALSE;
    samplerInfo.compareOp = vk::CompareOp::eAlways;
    samplerInfo.mipmapMode = vk::SamplerMipmapMode::eLinear;
    samplerInfo.mipLodBias = 0.f;
    samplerInfo.minLod = 0.f;
    samplerInfo.maxLod = static_cast<float>(m_iMipLevel);
    m_textureSampler = logicalDevice.createSampler(samplerInfo);
    if (!m_textureSampler)
    {
        throw std::runtime_error("Error while creating texture sampler");
    }
}