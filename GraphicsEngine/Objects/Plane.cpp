//
// Created by tangt on 03/11/2020.
//

#include "Plane.h"
#include "LogicalDevice.h"

object::Plane::Plane(const std::string & levelIdentifier,
                   const std::string & identifier,
                   const Math::Vector3F &position,
                   const Math::Vector3F &color /*=Math::Vector3F(1, 1, 1)*/,
                   const Math::Vector3F & scale /*=Math::Vector3F(1, 1, 1)*/,
                   const SRotation & rotate /*=Math::Vector3F(0, 0, 0)*/):
        Cube(levelIdentifier, identifier, position, color, scale, rotate)
{
    bool emptyStatus = true;
    emptyStatus = m_vertices.empty();
    emptyStatus = m_indices.empty();

    release();

    m_vertices.push_back(graphics::Vertex{
            Math::Vector3F(-0.5f, -0.5f, 0.f),
            m_color,
            Math::Vector2F(1.f, 0.f),
            Math::Vector3F(0.f, 0.f, 1.f)
    });
    m_vertices.push_back(graphics::Vertex{
            Math::Vector3F(0.5f, -0.5f, 0.f),
            m_color,
            Math::Vector2F(0.f, 0.f),
            Math::Vector3F(0.f, 0.f, 1.f)
    });
    m_vertices.push_back(graphics::Vertex{
            Math::Vector3F(0.5f, 0.5f, 0.f),
            m_color,
            Math::Vector2F(0.f, 1.f),
            Math::Vector3F(0.f, 0.f, 1.f)
    });
    m_vertices.push_back(graphics::Vertex{
            Math::Vector3F(-0.5f, 0.5f, 0.f),
            m_color,
            Math::Vector2F(1.f, 1.f),
            Math::Vector3F(0.f, 0.f, 1.f)
    });


    //
    // Indices
    m_indices = {
            0, 1, 2, 2, 3, 0,
            };

    graphics::LogicalDevice * logicalDevice = graphics::LogicalDevice::getInstance();

    logicalDevice->createVertexBuffer(m_vertexBuffer, m_verterBufferMemory, m_vertices);
    logicalDevice->createIndexBuffer(m_indexBuffer, m_indexBufferMemory, m_indices);
}