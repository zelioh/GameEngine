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

    class Texture {

        friend class TextureManager;

    public:
        const std::string & getName() const;
        stbi_uc * getPixelData() const;
        int getWidth() const;
        int getHeight() const;
        int getChannels() const;
        vk::DeviceSize getVkSize() const;

    private:
        Texture(const std::string & name, stbi_uc *pixels, int width, int heiht, int channels);

    private:
        std::string m_strName;
        stbi_uc * m_pixels;
        int m_iWidth;
        int m_iHeight;
        int m_iChannels;
        vk::DeviceSize m_size;
    };
}
#endif //GAMEENGINE_TEXTURE_H
