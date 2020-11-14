//
// Created by tangt on 13/10/2020.
//
//  Represent a vertice instance in the engine
//

#include "GraphicsEngine/Vertex.h"

//graphics::Vertex::Vertex(const Math::Vector3F &position,
//                         const Math::Vector3F &color,
//                         const Math::Vector2F &texCoord,
//                         const Math::Vector3F &normal):
//m_position(position),
//m_color(color),
//m_texCoord(texCoord),
//m_normal(normal)
//{
//}

vk::VertexInputBindingDescription graphics::Vertex::getBindDescription()
{
    vk::VertexInputBindingDescription bind{};

    bind.binding = 0;
    bind.inputRate = vk::VertexInputRate::eVertex;
    bind.stride = sizeof(Vertex);
    return bind;
}

std::array<vk::VertexInputAttributeDescription, 4> graphics::Vertex::getAttributeDescription()
{
    std::array<vk::VertexInputAttributeDescription, 4> attributes{};

    attributes[0].binding = 0;
    attributes[0].location = 0;
    attributes[0].format = vk::Format::eR32G32B32Sfloat;
    attributes[0].offset = offsetof(Vertex, m_position);

    attributes[1].binding = 0;
    attributes[1].location = 1;
    attributes[1].format = vk::Format::eR32G32B32Sfloat;
    attributes[1].offset = offsetof(Vertex, m_color);

    attributes[2].binding = 0;
    attributes[2].location = 2;
    attributes[2].format = vk::Format::eR32G32Sfloat;
    attributes[2].offset = offsetof(Vertex, m_texCoord);

    attributes[3].binding = 0;
    attributes[3].location = 3;
    attributes[3].format = vk::Format::eR32G32B32Sfloat;
    attributes[3].offset = offsetof(Vertex, m_normal);

    return attributes;
}

bool graphics::Vertex::operator==(const Vertex &other) const
{
    return m_position == other.m_position && m_texCoord == other.m_texCoord && m_color == other.m_color;
}