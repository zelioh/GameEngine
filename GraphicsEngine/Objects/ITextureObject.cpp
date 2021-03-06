//
// Created by FiercePC on 29/10/2020.
//

#include "GraphicsEngine/ITextureObject.h"
#include "public/GraphicsEngine/Texture.h"

graphics::Texture * object::ITextureObject::getTexture() const
{
    return m_texture;
}

void object::ITextureObject::setTexture(graphics::Texture *texture)
{
    m_texture = texture;
}