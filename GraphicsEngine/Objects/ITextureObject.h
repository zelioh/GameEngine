//
// Created by tangt on 28/10/2020.
//

#ifndef GAMEENGINE_ITEXTUREOBJECT_H
#define GAMEENGINE_ITEXTUREOBJECT_H

namespace graphics
{
    class Texture;
}

namespace object {

    class ITextureObject {
    public:
        graphics::Texture * getTexture() const;
        void setTexture(graphics::Texture  * texture);

    protected:
        graphics::Texture * m_texture;
    };

}

#endif //GAMEENGINE_ITEXTUREOBJECT_H
