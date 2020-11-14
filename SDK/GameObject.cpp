//
// Created by FiercePC on 09/11/2020.
//

#include "public/SDK/GameObject.h"
#include "public/GraphicsEngine/GameObject.h"

sdk::GameObject::GameObject(object::GameObject *pEngineObject):
m_pObject(pEngineObject)
{
}

const Math::Vector3F & sdk::GameObject::getPosition() const
{
    return m_pObject->getPosition();
}

const Math::Vector3F & sdk::GameObject::getColor() const
{
    return m_pObject->getColor();
}

const Math::Vector3F & sdk::GameObject::getScale() const
{
    return m_pObject->getScale();
}

const Math::SRotation & sdk::GameObject::getRotation() const
{
    return m_pObject->getRotate();
}

const std::string & sdk::GameObject::getLevelIdentifier() const
{
    return m_pObject->getLevelIdentifier();
}

const std::string & sdk::GameObject::getIdentifier() const
{
    return m_pObject->getIdentifier();
}

void sdk::GameObject::setPosition(const Math::Vector3F &position)
{
    m_pObject->setPosition(position);
}

void sdk::GameObject::setColor(const Math::Vector3F &color)
{
    m_pObject->setColor(color);
}

void sdk::GameObject::setScale(const Math::Vector3F &scale)
{
    m_pObject->setScale(scale);
}

void sdk::GameObject::setRotate(const Math::SRotation &rotate)
{
    m_pObject->setRotate(rotate);
}

const PhysicsObject * sdk::GameObject::getPhysicalObject()
{
    return m_pObject->getPhysicsObject();
}

void sdk::GameObject::setPhysicalObject(PhysicsObject *physicsObject)
{
    m_pObject->setPhysicsObject(physicsObject);
}

sdk::Texture sdk::GameObject::getTexture() const
{
    return Texture(m_pObject->getTexture());
}

void sdk::GameObject::setTexture(const Texture & texture)
{
    m_pObject->setTexture(texture.m_pTexture);
}