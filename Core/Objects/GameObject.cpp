//
// Created by tangt on 26/10/2020.
//
// Main class that represent the common think between each objects
//

#include "GameObject.h"

object::GameObject::GameObject(const std::string & identifier,
                               const Math::Vector3F & position,
                               const Math::Vector3F & color):
m_strIdentifier(identifier),
m_position(position),
m_color(color)
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

void object::GameObject::setPosition(const Math::Vector3F &position)
{
    m_position = position;
}

void object::GameObject::setColor(const Math::Vector3F &color)
{
    m_color = color;
}

const std::string & object::GameObject::getIdentifier() const
{
    return m_strIdentifier;
}