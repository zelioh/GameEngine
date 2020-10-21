//
// Created by tangt on 20/10/2020.
//
// Contain texture data usable by the engine
//

#ifndef GAMEENGINE_TEXTURE_H
#define GAMEENGINE_TEXTURE_H

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"
#include "vulkan/vulkan.hpp"

namespace graphics {

    class LogicalDevice;

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

    private:
        Texture(const LogicalDevice & logicalDevice, const std::string & name, stbi_uc *pixels, int width, int heiht, int channels);

        void initializeInternal(const LogicalDevice & logicalDevice, stbi_uc *pixels);
        void createSampler(const vk::Device & logicalDevice);

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
    };
}
#endif //GAMEENGINE_TEXTURE_H
