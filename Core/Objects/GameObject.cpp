//
// Created by tangt on 26/10/2020.
//
// Main class that represent the common think between each objects
//

#include "GameObject.h"

object::GameObject::GameObject(const std::string & identifier,
                               const Math::Vector3F & position,
                               const Math::Vector3F & color,
                               const Math::Vector3F & scale /*=Math::Vector3F(1, 1, 1)*/,
                               const Math::Vector3F & rotate /*=Math::Vector3F(0, 0, 0)*/):
m_strIdentifier(identifier),
m_position(position),
m_color(color),
m_scale(scale),
m_rotate(rotate)
{
}

const Math::Vector3F & object::GameObject::getColor() const
{
    return m_color;
}

const Math::Vector3F & object::GameObject::getPosition() const
{
    return m_position;
}

const Math::Vector3F & object::GameObject::getScale() const
{
    return m_scale;
}

const Math::Vector3F & object::GameObject::getRotate() const
{
    return m_rotate;
}

void object::GameObject::setPosition(const Math::Vector3F &position)
{
    m_position = position;
}

void object::GameObject::setColor(const Math::Vector3F &color)
{
    m_color = color;
}

void object::GameObject::setScale(const Math::Vector3F &scale)
{
    m_scale = scale;
}

void object::GameObject::setRotate(const Math::Vector3F &rotate)
{
    m_rotate = rotate;
}

const std::string & object::GameObject::getIdentifier() const
{
    return m_strIdentifier;
}