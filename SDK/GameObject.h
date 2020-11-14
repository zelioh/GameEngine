//
// Created by FiercePC on 09/11/2020.
//

#ifndef GAMEENGINE_SDK_GAMEOBJECT_H
#define GAMEENGINE_SDK_GAMEOBJECT_H

#include "../Math/Vector3F.h"
#include "../Math/SRotation.h"
#include "PhysicsObject.h"
#include "Texture.h"

namespace object
{
    class GameObject;
}

namespace sdk {

    class GameObject {
    public:

        const Math::Vector3F & getPosition() const;
        const Math::Vector3F & getColor() const;
        const Math::Vector3F & getScale() const;
        const Math::SRotation & getRotation() const;

        void setPosition(const Math::Vector3F & position);
        void setColor(const Math::Vector3F & color);
        void setScale(const Math::Vector3F & scale);
        void setRotate(const Math::SRotation & rotate);

        const std::string & getIdentifier() const;
        const std::string & getLevelIdentifier() const;

        const PhysicsObject * getPhysicalObject();
        void setPhysicalObject(PhysicsObject * physicsObject);

        Texture getTexture() const;
        void setTexture(const Texture & texture);

    protected:
        GameObject(object::GameObject * pEngineObject);

        object::GameObject * m_pObject;
    };

}

#endif //GAMEENGINE_GAMEOBJECT_H
