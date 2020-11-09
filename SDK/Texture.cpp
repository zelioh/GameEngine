//
// Created by FiercePC on 09/11/2020.
//

#include "Texture.h"
#include "public/GraphicsEngine/Texture.h"

sdk::Texture::Texture(graphics::Texture *pEngineTexture):
m_pTexture(pEngineTexture)
{}

const std::string & sdk::Texture::getIdentifier() const
{
    return m_pTexture->getName();
}

int sdk::Texture::getChannels() const
{
    return m_pTexture->getChannels();
}

int sdk::Texture::getHeight() const
{
    return m_pTexture->getHeight();
}

int sdk::Texture::getWidht() const
{
    return m_pTexture->getWidth();
}

uint32_t sdk::Texture::getMipLevel() const
{
    return m_pTexture->getMipLevel();
}
