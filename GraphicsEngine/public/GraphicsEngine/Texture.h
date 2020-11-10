//
// Created by tangt on 20/10/2020.
//
// Contain texture data usable by the engine
//

#ifndef GAMEENGINE_TEXTURE_H
#define GAMEENGINE_TEXTURE_H

#include "vulkan/vulkan.hpp"
#include "stb_image.h"

namespace graphics {
    class LogicalDevice;
    class Swapchain;

    class Texture {

        friend class TextureManager;

    public:
        Texture() = default; ///< Default constructor with empty values

        const std::string & getName() const;
        int getWidth() const;
        int getHeight() const;
        int getChannels() const;
        vk::DeviceSize getVkSize() const;
        const vk::Image & getVkTexture() const;
        const vk::DeviceMemory & getVkTextureMemory() const;
        const vk::ImageView & getVkTextureView() const;
        const vk::Sampler & getVkTextureSampler() const;
        uint32_t getMipLevel() const;

        const vk::DescriptorSet & getVkDescriptorSet(int iIndex);


    private:
        Texture(const std::string & name, stbi_uc *pixels, int width, int heiht, int channels);

        void release();

        void initializeInternal(stbi_uc *pixels);
        void createSampler(const vk::Device & logicalDevice);
        void createDescriptorSet();
        void recreateDescriptorSet();

    private:
        std::string m_strName;
        int m_iWidth;
        int m_iHeight;
        int m_iChannels;
        vk::DeviceSize m_size;
        vk::Image m_texture;
        vk::DeviceMemory m_textureMemory;
        vk::ImageView m_textureView;
        vk::Sampler m_textureSampler;
        uint32_t m_iMipLevel;

        vk::DescriptorSet m_descriptorSet;
    };
}
#endif //GAMEENGINE_TEXTURE_H
