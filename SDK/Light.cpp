//
// Created by FiercePC on 09/11/2020.
//

#include "public/SDK/Light.h"
#include "public/GraphicsEngine/Light.h"

sdk::Light::Light(object::Light *pLight):
m_pLight(pLight)
{
}

const Math::Vector3F & sdk::Light::getPosition() const
{
    return m_pLight->getPosition();
}

const Math::Vector3F & sdk::Light::getColor() const
{
    return m_pLight->getColor();
}

float sdk::Light::getStrength() const
{
    return m_pLight->getStrength();
}

float sdk::Light::getSpecular() const
{
    return m_pLight->getSpecular();
}

const std::string & sdk::Light::getLevelIdentifier() const
{
    return m_pLight->getLevelIdentifier();
}

const std::string & sdk::Light::getIdentifier() const
{
    return m_pLight->getIdentifier();
}

void sdk::Light::setPosition(const Math::Vector3F &position)
{
    m_pLight->setPosition(position);
}

void sdk::Light::setColor(const Math::Vector3F &color)
{
    m_pLight->setColor(color);
}

void sdk::Light::setStrength(float strength)
{
    m_pLight->setStrength(strength);
}

void sdk::Light::setSpecular(float specular)
{
    m_pLight->setSpecular(specular);
}