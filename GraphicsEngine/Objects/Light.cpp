//
// Created by theos on 03/11/2020.
//

#include "Light.h"
#include "Math_utils.h"

const Math::Vector3F & object::Light::getPosition() const
{
    return m_position;
}

const float & object::Light::getStrength() const
{
    return m_strength;
}

const float & object::Light::getSpecular() const
{
    return m_specular;
}

const Math::Vector3F & object::Light::getColor() const
{
	return m_color;
}

void object::Light::setPosition(const Math::Vector3F &position)
{
    m_position = position;
}

void object::Light::setStrength(const float & strength)
{
	m_strength = strength;
}

void object::Light::setSpecular(const float & specular)
{
	m_specular = specular;
}

void object::Light::setColor(const Math::Vector3F& color)
{
	m_color = color;

}

object::Light::Light(const Math::Vector3F& position,
					 const Math::float& strength,
					 const Math::float& specular,
					 const Math::Vector3F& color) :
m_position(position),
m_strength(strength),
m_specular(specular),
m_color(color)