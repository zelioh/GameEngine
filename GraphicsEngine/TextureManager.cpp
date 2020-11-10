//
// Created by tangt on 20/10/2020.
//
// Use for create a Texture instance
//

#include "public/GraphicsEngine/TextureManager.h"
#include "public/GraphicsEngine/Texture.h"
#include "LogicalDevice.h"

/*static*/ graphics::TextureManager * graphics::TextureManager::getInstance()
{
    static TextureManager * manager = nullptr;

    if (nullptr == manager)
    {
        manager = new TextureManager();
    }
    return manager;
}

graphics::Texture * graphics::TextureManager::createTexture(const std::string &texturePath,
                                                            const std::string &textureName) {
    //
    // Create texture name
    std::string name = "";

    if (nullptr == textureName.c_str()) {
        name = texturePath.substr(0, texturePath.find('.'));
    } else {
        name = textureName;
    }

    //
    // Check if texture name already exist in the pool
    auto search = m_pool.find(name);

    if (search != m_pool.end()) {
        return m_pool[name];
    }

    //
    // Create the new texture
    int width = 0, height = 0, channels = 0;
    stbi_uc *pixels = stbi_load(texturePath.c_str(), &width, &height, &channels, STBI_rgb_alpha);

    graphics::Texture *texture = new Texture(name, pixels, width, height, channels);
    m_pool[name] = texture;
    return m_pool[name];
}

graphics::Texture * graphics::TextureManager::findTexture(const std::string &textureName)
{
    auto search = m_pool.find(textureName);

    if (search != m_pool.end()) {
        return m_pool[textureName];
    }
    assert(false); ///< Assert always. TODO: use Engine assert system
    return nullptr;
}

void graphics::TextureManager::release()
{
    for (auto texture : m_pool)
    {
        texture.second->release();
        delete texture.second;
        texture.second = nullptr;
    }
}

void graphics::TextureManager::windowSizeChanged()
{
    for (auto & texture : m_pool)
    {
        texture.second->recreateDescriptorSet();
    }
}