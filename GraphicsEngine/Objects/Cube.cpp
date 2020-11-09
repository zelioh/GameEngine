//
// Created by tangt on 26/10/2020.
//
// Represent a cube into the game
//

#include "Cube.h"
#include "LogicalDevice.h"

object::Cube::Cube(const std::string & levelIdentifier,
                   const std::string & identifier,
                   const Math::Vector3F &position,
                   const Math::Vector3F &color /*=Math::Vector3F(1, 1, 1)*/,
                   const Math::Vector3F & scale /*=Math::Vector3F(1, 1, 1)*/,
                   const Math::SRotation & rotate /*=Math::Vector3F(0, 0, 0)*/):
GameObject(levelIdentifier, identifier, position, color, scale, rotate)
{
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
                                 Math::Vector3F(0.f, 1.f, 0.f)
                         });
    m_vertices.push_back({
                                 Math::Vector3F(0.5f, -0.5f, -0.5f),
                                 m_color,
                                 Math::Vector2F(1.f, 1.f),
                                 Math::Vector3F(0.f, 1.f, 0.f)
                         });
    m_vertices.push_back({
                                 Math::Vector3F(0.5f, -0.5f, 0.5f),
                                 m_color,
                                 Math::Vector2F(1.f, 0.f),
                                 Math::Vector3F(0.f, 1.f, 0.f)
                         });
    m_vertices.push_back({
                                 Math::Vector3F(-0.5f, -0.5f, 0.5f),
                                 m_color,
                                 Math::Vector2F(0.f, 0.f),
                                 Math::Vector3F(0.f, 1.f, 0.f)
                         });

    //
    // Vertices left face
    m_vertices.push_back({
                                 Math::Vector3F(-0.5f, 0.5f, -0.5f),
                                 m_color,
                                 Math::Vector2F(0.f, 0.f),
                                 Math::Vector3F(-1.f, 0.f, 0.f)
                         });
    m_vertices.push_back({
                                 Math::Vector3F(-0.5f, -0.5f, -0.5f),
                                 m_color,
                                 Math::Vector2F(1.f, 0.f),
                                 Math::Vector3F(-1.f, 0.f, 0.f)
                         });
    m_vertices.push_back({
                                 Math::Vector3F(-0.5f, -0.5f, 0.5f),
                                 m_color,
                                 Math::Vector2F(1.f, 1.f),
                                 Math::Vector3F(-1.f, 0.f, 0.f)
                         });
    m_vertices.push_back({
                                 Math::Vector3F(-0.5f, 0.5f, 0.5f),
                                 m_color,
                                 Math::Vector2F(0.f, 1.f),
                                 Math::Vector3F(-1.f, 0.f, 0.f)
                         });

    //
    // Vertices right face
    m_vertices.push_back({
                                 Math::Vector3F(0.5f, -0.5f, -0.5f),
                                 m_color,
                                 Math::Vector2F(0.f, 0.f),
                                 Math::Vector3F(1.f, 0.f, 0.f)
                         });
    m_vertices.push_back({
                                 Math::Vector3F(0.5f, 0.5f, -0.5f),
                                 m_color,
                                 Math::Vector2F(1.f, 0.f),
                                 Math::Vector3F(1.f, 0.f, 0.f)
                         });
    m_vertices.push_back({
                                 Math::Vector3F(0.5f, 0.5f, 0.5f),
                                 m_color,
                                 Math::Vector2F(1.f, 1.f),
                                 Math::Vector3F(1.f, 0.f, 0.f)
                         });
    m_vertices.push_back({
                                 Math::Vector3F(0.5f, -0.5f, 0.5f),
                                 m_color,
                                 Math::Vector2F(0.f, 1.f),
                                 Math::Vector3F(1.f, 0.f, 0.f)
                         });

    //
    // Vertices back face
    m_vertices.push_back({
            Math::Vector3F(0.5f, 0.5f, -0.5f),
            m_color,
            Math::Vector2F(0.f, 1.f),
            Math::Vector3F(0.f, -1.f, 0.f)
    });
    m_vertices.push_back({
            Math::Vector3F(-0.5f, 0.5f, -0.5f),
            m_color,
            Math::Vector2F(1.f, 1.f),
            Math::Vector3F(0.f, -1.f, 0.f)
    });
    m_vertices.push_back({
            Math::Vector3F(-0.5f, 0.5f, 0.5f),
            m_color,
            Math::Vector2F(1.f, 0.f),
            Math::Vector3F(0.f, -1.f, 0.f)
    });
    m_vertices.push_back({
            Math::Vector3F(0.5f, 0.5f, 0.5f),
            m_color,
            Math::Vector2F(0.f, 0.f),
            Math::Vector3F(0.f, -1.f, 0.f)
    });

    //
    // Vertices down face
    m_vertices.push_back({
            Math::Vector3F(-0.5f, 0.5f, -0.5f),
            m_color,
            Math::Vector2F(0.f, 0.f),
            Math::Vector3F(0.f, 0.f, -1.f)
    });
    m_vertices.push_back({
            Math::Vector3F(0.5f, 0.5f, -0.5f),
            m_color,
            Math::Vector2F(1.f, 0.f),
            Math::Vector3F(0.f, 0.f, -1.f)
    });
    m_vertices.push_back({
            Math::Vector3F(0.5f, -0.5f, -0.5f),
            m_color,
            Math::Vector2F(1.f, 1.f),
            Math::Vector3F(0.f, 0.f, -1.f)
    });
    m_vertices.push_back({
            Math::Vector3F(-0.5f, -0.5f, -0.5f),
            m_color,
            Math::Vector2F(0.f, 1.f),
            Math::Vector3F(0.f, 0.f, -1.f)
    });

    //
    // Indices
    m_indices = {
            0, 1, 2, 2, 3, 0,
            4, 5, 6, 6, 7, 4,
            8, 9, 10, 10, 11, 8,
            12, 13, 14, 14, 15, 12,
            16, 17, 18, 18, 19, 16,
            20, 21, 22, 22, 23, 20
    };

    graphics::LogicalDevice::getInstance()->createVertexBuffer(m_vertexBuffer, m_verterBufferMemory, m_vertices);
    graphics::LogicalDevice::getInstance()->createIndexBuffer(m_indexBuffer, m_indexBufferMemory, m_indices);
}

const std::vector<graphics::Vertex> & object::Cube::getVertices() const
{
    return m_vertices;
}

const std::vector<uint32_t> & object::Cube::getIndices() const
{
    return m_indices;
}

const vk::Buffer & object::Cube::getVertexBuffer() const
{
    return m_vertexBuffer;
}

const vk::Buffer & object::Cube::getIndexBuffer() const
{
    return m_indexBuffer;
}

void object::Cube::release()
{
    graphics::LogicalDevice * logicalDevice = graphics::LogicalDevice::getInstance();

    logicalDevice->getVkLogicalDevice().destroyBuffer(m_vertexBuffer);
    logicalDevice->getVkLogicalDevice().destroyBuffer(m_indexBuffer);

    logicalDevice->getVkLogicalDevice().freeMemory(m_verterBufferMemory);
    logicalDevice->getVkLogicalDevice().freeMemory(m_indexBufferMemory);
}