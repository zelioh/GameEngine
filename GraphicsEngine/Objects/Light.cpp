//
// Created by theos on 03/11/2020.
//

#include "Light.h"
#include "Math_utils.h"
#include "LogicalDevice.h"

const float & object::Light::getStrength() const
{
    return m_strength;
}

const float & object::Light::getSpecular() const
{
    return m_specular;
}

void object::Light::setStrength(const float & strength)
{
	m_strength = strength;
}

void object::Light::setSpecular(const float & specular)
{
	m_specular = specular;
}

object::Light::Light(const std::string & levelIdentifier,
                     const std::string & lightIdentifier,
                     const Math::Vector3F & position,
					 float strength,
					 float specular,
					 const Math::Vector3F& color):
 Cube(levelIdentifier, lightIdentifier, position, color, Math::Vector3F(strength, strength, strength)),
m_strength(strength),
m_specular(specular)
{
    bool emptyStatus = true;
    emptyStatus = m_vertices.empty();

    graphics::LogicalDevice * logicalDevice = graphics::LogicalDevice::getInstance();

    logicalDevice->getVkLogicalDevice().destroyBuffer(m_vertexBuffer);
    logicalDevice->getVkLogicalDevice().freeMemory(m_verterBufferMemory);

    m_vertices.push_back({
                                 Math::Vector3F(-0.5f, -0.5f, 0.5f),
                                 m_color,
                                 Math::Vector2F(1.f, 0.f),
                                 Math::Vector3F(0.f, 0.f, 1.f)
                         });
    m_vertices.push_back({
                                 Math::Vector3F(0.5f, -0.5f, 0.5f),
                                 m_color,
                                 Math::Vector2F(0.f, 0.f),
                                 Math::Vector3F(0.f, 0.f, 1.f)
                         });
    m_vertices.push_back({
                                 Math::Vector3F(0.5f, 0.5f, 0.5f),
                                 m_color,
                                 Math::Vector2F(0.f, 1.f),
                                 Math::Vector3F(0.f, 0.f, 1.f)
                         });
    m_vertices.push_back({
                                 Math::Vector3F(-0.5f, 0.5f, 0.5f),
                                 m_color,
                                 Math::Vector2F(1.f, 1.f),
                                 Math::Vector3F(0.f, 0.f, 1.f)
                         });

    //
    // Vertices front face
    m_vertices.push_back({
                                 Math::Vector3F(-0.5f, -0.5f, -0.5f),
                                 m_color,
                                 Math::Vector2F(0.f, 1.f),
                                 Math::Vector3F(0.f, 0.f, 0.f)
                         });
    m_vertices.push_back({
                                 Math::Vector3F(0.5f, -0.5f, -0.5f),
                                 m_color,
                                 Math::Vector2F(1.f, 1.f),
                                 Math::Vector3F(0.f, 0.f, 0.f)
                         });
    m_vertices.push_back({
                                 Math::Vector3F(0.5f, -0.5f, 0.5f),
                                 m_color,
                                 Math::Vector2F(1.f, 0.f),
                                 Math::Vector3F(0.f, 0.f, 0.f)
                         });
    m_vertices.push_back({
                                 Math::Vector3F(-0.5f, -0.5f, 0.5f),
                                 m_color,
                                 Math::Vector2F(0.f, 0.f),
                                 Math::Vector3F(0.f, 0.f, 0.f)
                         });

    //
    // Vertices left face
    m_vertices.push_back({
                                 Math::Vector3F(-0.5f, 0.5f, -0.5f),
                                 m_color,
                                 Math::Vector2F(0.f, 0.f),
                                 Math::Vector3F(0.f, 0.f, 0.f)
                         });
    m_vertices.push_back({
                                 Math::Vector3F(-0.5f, -0.5f, -0.5f),
                                 m_color,
                                 Math::Vector2F(1.f, 0.f),
                                 Math::Vector3F(0.f, 0.f, 0.f)
                         });
    m_vertices.push_back({
                                 Math::Vector3F(-0.5f, -0.5f, 0.5f),
                                 m_color,
                                 Math::Vector2F(1.f, 1.f),
                                 Math::Vector3F(0.f, 0.f, 0.f)
                         });
    m_vertices.push_back({
                                 Math::Vector3F(-0.5f, 0.5f, 0.5f),
                                 m_color,
                                 Math::Vector2F(0.f, 1.f),
                                 Math::Vector3F(0.f, 0.f, 0.f)
                         });

    //
    // Vertices right face
    m_vertices.push_back({
                                 Math::Vector3F(0.5f, -0.5f, -0.5f),
                                 m_color,
                                 Math::Vector2F(0.f, 0.f),
                                 Math::Vector3F(0.f, 0.f, 0.f)
                         });
    m_vertices.push_back({
                                 Math::Vector3F(0.5f, 0.5f, -0.5f),
                                 m_color,
                                 Math::Vector2F(1.f, 0.f),
                                 Math::Vector3F(0.f, 0.f, 0.f)
                         });
    m_vertices.push_back({
                                 Math::Vector3F(0.5f, 0.5f, 0.5f),
                                 m_color,
                                 Math::Vector2F(1.f, 1.f),
                                 Math::Vector3F(0.f, 0.f, 0.f)
                         });
    m_vertices.push_back({
                                 Math::Vector3F(0.5f, -0.5f, 0.5f),
                                 m_color,
                                 Math::Vector2F(0.f, 1.f),
                                 Math::Vector3F(0.f, 0.f, 0.f)
                         });

    //
    // Vertices back face
    m_vertices.push_back({
                                 Math::Vector3F(0.5f, 0.5f, -0.5f),
                                 m_color,
                                 Math::Vector2F(0.f, 1.f),
                                 Math::Vector3F(0.f, 0.f, 0.f)
                         });
    m_vertices.push_back({
                                 Math::Vector3F(-0.5f, 0.5f, -0.5f),
                                 m_color,
                                 Math::Vector2F(1.f, 1.f),
                                 Math::Vector3F(0.f, 0.f, 0.f)
                         });
    m_vertices.push_back({
                                 Math::Vector3F(-0.5f, 0.5f, 0.5f),
                                 m_color,
                                 Math::Vector2F(1.f, 0.f),
                                 Math::Vector3F(0.f, 0.f, 0.f)
                         });
    m_vertices.push_back({
                                 Math::Vector3F(0.5f, 0.5f, 0.5f),
                                 m_color,
                                 Math::Vector2F(0.f, 0.f),
                                 Math::Vector3F(0.f, 0.f, 0.f)
                         });

    //
    // Vertices down face
    m_vertices.push_back({
                                 Math::Vector3F(-0.5f, 0.5f, -0.5f),
                                 m_color,
                                 Math::Vector2F(0.f, 0.f),
                                 Math::Vector3F(0.f, 0.f, 0.f)
                         });
    m_vertices.push_back({
                                 Math::Vector3F(0.5f, 0.5f, -0.5f),
                                 m_color,
                                 Math::Vector2F(1.f, 0.f),
                                 Math::Vector3F(0.f, 0.f, 0.f)
                         });
    m_vertices.push_back({
                                 Math::Vector3F(0.5f, -0.5f, -0.5f),
                                 m_color,
                                 Math::Vector2F(1.f, 1.f),
                                 Math::Vector3F(0.f, 0.f, 0.f)
                         });
    m_vertices.push_back({
                                 Math::Vector3F(-0.5f, -0.5f, -0.5f),
                                 m_color,
                                 Math::Vector2F(0.f, 1.f),
                                 Math::Vector3F(0.f, 0.f, 0.f)
                         });

    logicalDevice->createVertexBuffer(m_vertexBuffer, m_verterBufferMemory, m_vertices);
}