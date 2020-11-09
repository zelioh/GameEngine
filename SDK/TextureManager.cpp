//
// Created by FiercePC on 09/11/2020.
//

#include "TextureManager.h"
#include "public/GraphicsEngine/Texture.h"
#include "public/GraphicsEngine/TextureManager.h"

sdk::Texture sdk::TextureManager::createTexture(const std::string &texturePath, const std::string &textureIdentifier)
{
    return sdk::Texture(graphics::TextureManager::getInstance()->createTexture(texturePath, textureIdentifier));
}

sdk::Texture sdk::TextureManager::findTexture(const std::string &textureIdentifier)
{
    return sdk::Texture(graphics::TextureManager::getInstance()->findTexture(textureIdentifier));
}