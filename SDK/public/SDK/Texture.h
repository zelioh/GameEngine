//
// Created by FiercePC on 09/11/2020.
//

#ifndef GAMEENGINE_SDK_TEXTURE_H
#define GAMEENGINE_SDK_TEXTURE_H

#include <string>
#include "SDK.h"

namespace graphics
{
    class Texture;
}

namespace sdk {

    class SDK_EXPORT Texture {

        friend class GameObject;
        friend class TextureManager;

    public:
        const std::string & getIdentifier() const;
        int getWidht() const;
        int getHeight() const;
        int getChannels() const;
        uint32_t getMipLevel() const;

    private:
        Texture(graphics::Texture * pEngineTexture);

        graphics::Texture * m_pTexture;
    };

}

#endif //GAMEENGINE_TEXTURE_H
