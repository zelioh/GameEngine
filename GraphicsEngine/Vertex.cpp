//
// Created by tangt on 13/10/2020.
//
//  Represent a vertice instance in the engine
//

#include "Vertex.h"


vk::VertexInputBindingDescription graphics::Vertex::getBindDescription()
{
    vk::VertexInputBindingDescription bind{};

    bind.binding = 0;
    bind.inputRate = vk::VertexInputRate::eVertex;
    bind.stride = sizeof(Vertex);
    return bind;
}

std::array<vk::VertexInputAttributeDescription, 3> graphics::Vertex::getAttributeDescription()
{
    std::array<vk::VertexInputAttributeDescription, 3> attributes{};

    attributes[0].binding = 0;
    attributes[0].location = 0;
    attributes[0].format = vk::Format::eR32G32B32Sfloat;
    attributes[0].offset = offsetof(Vertex, position);
    attributes[1].binding = 0;
    attributes[1].location = 1;
    attributes[1].format = vk::Format::eR32G32B32Sfloat;
    attributes[1].offset = offsetof(Vertex, color);
    attributes[2].binding = 0;
    attributes[2].location = 2;
    attributes[2].format = vk::Format::eR32G32Sfloat;
    attributes[2].offset = offsetof(Vertex, texColor);

    return attributes;
}

bool graphics::Vertex::operator==(const Vertex &other) const
{
    return position == other.position && texColor == other.texColor && color == other.color;
}