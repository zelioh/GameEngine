//
// Created by tangt on 04/11/2020.
//

#include "Model3D.h"
#include "LogicalDevice.h"
#include "Objects/Objects_utils.h"

object::Model3D::Model3D(const std::string &levelIdentifier,
                         const std::string &identifier,
                         const std::string &fileModel,
                         const Math::Vector3F &position,
                         const Math::Vector3F &color,
                         const Math::Vector3F &scale,
                         const Math::SRotation &rotate):
 GameObject(levelIdentifier, identifier, position, color, scale, rotate)
{
    object::utils::loadObj(fileModel, m_vertices, m_indices, m_color);

    graphics::LogicalDevice::getInstance()->createVertexBuffer(m_vertexBuffer, m_verterBufferMemory, m_vertices);
    graphics::LogicalDevice::getInstance()->createIndexBuffer(m_indexBuffer, m_indexBufferMemory, m_indices);
}

const std::vector<graphics::Vertex> & object::Model3D::getVertices() const
{
    return m_vertices;
}

const std::vector<uint32_t> & object::Model3D::getIndices() const
{
    return m_indices;
}

const vk::Buffer & object::Model3D::getVertexBuffer() const
{
    return m_vertexBuffer;
}

const vk::Buffer & object::Model3D::getIndexBuffer() const
{
    return m_indexBuffer;
}

void object::Model3D::release()
{
    graphics::LogicalDevice * logicalDevice = graphics::LogicalDevice::getInstance();

    logicalDevice->getVkLogicalDevice().destroyBuffer(m_vertexBuffer);
    logicalDevice->getVkLogicalDevice().destroyBuffer(m_indexBuffer);

    logicalDevice->getVkLogicalDevice().freeMemory(m_verterBufferMemory);
    logicalDevice->getVkLogicalDevice().freeMemory(m_indexBufferMemory);
}