//
// Created by tangt on 20/10/2020.
//
// Use for create a Texture instance
//

#ifndef GAMEENGINE_TEXTUREMANAGER_H
#define GAMEENGINE_TEXTUREMANAGER_H

#include <string>
#include <unordered_map>

namespace graphics {

    class LogicalDevice;
    class Swapchain;
    class Texture;

    class TextureManager {
    public:
        static TextureManager * getInstance(); ///< Singletone that return a TextureManager instance
        /**
         * Create a texture, push into m_pool and return the new instance.
         * If the texture name already exist, return that existing texture
         * @param texturePath   path to the texture file
         * @param textureName   name of the texture in the map. If nullptr the name will be the file name before the '.'
         * @return  a Texture instance
         */
        graphics::Texture * createTexture(const std::string & texturePath,
                                          const std::string & textureName = nullptr);
        /**
         * Find a texture in the pool of texture
         * @param textureName   name of the texture
         * @return  Texture instance or nullptr if the texture doesn't exist
         */
        graphics::Texture * findTexture(const std::string & textureName);

        void release();
    private:
        TextureManager() = default; ///< Private constructor use in getInstance
    private:
        std::unordered_map<std::string, Texture *> m_pool;
    };
}

#endif //GAMEENGINE_TEXTUREMANAGER_H
