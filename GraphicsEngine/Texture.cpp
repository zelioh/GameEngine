//
// Created by tangt on 20/10/2020.
//
// Contain texture data usable by the engine
//

#include "Texture.h"

graphics::Texture::Texture(const std::string & name, stbi_uc *pixels, int width, int height, int channels):
m_strName(name),
m_pixels(pixels),
m_iWidth(width),
m_iHeight(height),
m_iChannels(channels),
m_size(width * height * 4)
{}

const std::string & graphics::Texture::getName() const
{
    return m_strName;
}

stbi_uc * graphics::Texture::getPixelData() const
{
    return m_pixels;
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