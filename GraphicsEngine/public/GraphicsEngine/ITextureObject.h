//
// Created by tangt on 28/10/2020.
//

#ifndef GAMEENGINE_ITEXTUREOBJECT_H
#define GAMEENGINE_ITEXTUREOBJECT_H

#include "GraphicsEngine/GraphicsEngine.h"

namespace graphics
{
    class Texture;
}

namespace object {

    class GRAPHICS_ENGINE_EXPORT ITextureObject {
    public:
        graphics::Texture * getTexture() const;
        void setTexture(graphics::Texture  * texture);

    protected:
        graphics::Texture * m_texture;
    };

}

#endif //GAMEENGINE_ITEXTUREOBJECT_H
