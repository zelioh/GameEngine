//
// Created by FiercePC on 09/11/2020.
//

#ifndef GAMEENGINE_SDK_TEXTUREMANAGER_H
#define GAMEENGINE_SDK_TEXTUREMANAGER_H

#include <string>
#include "Texture.h"

namespace sdk {

    class TextureManager
    {
    public:
        static Texture createTexture(const std::string & texturePath, const std::string & textureIdentifier = nullptr);
        static Texture findTexture(const std::string & textureIdentifier);
    };

}

#endif //GAMEENGINE_TEXTUREMANAGER_H
