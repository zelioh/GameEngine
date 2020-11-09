//
// Created by FiercePC on 09/11/2020.
//

#ifndef GAMEENGINE_SDK_GAMEOBJECT_H
#define GAMEENGINE_SDK_GAMEOBJECT_H

#include "Vector3F.h"
#include "SRotation.h"
#include "PhysicsObject.h"

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

    protected:
        GameObject(object::GameObject * pEngineObject);

        object::GameObject * m_pObject;
    };

}

#endif //GAMEENGINE_GAMEOBJECT_H
