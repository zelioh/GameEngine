//
// Created by tangt on 13/10/2020.
//
//  Represent a vertice instance in the engine
//

#ifndef GAMEENGINE_VERTEX_H
#define GAMEENGINE_VERTEX_H

#include "vulkan/vulkan.hpp"
#include "Vector3F.h"
#include "Vector2F.h"

namespace graphics {

    class Vertex {
    public:
        Vertex() = default;
        Vertex(const Math::Vector3F & position, const Math::Vector3F & color, const Math::Vector2F & texCoord);

        static vk::VertexInputBindingDescription getBindDescription();
        static std::array<vk::VertexInputAttributeDescription, 3> getAttributeDescription();
        bool operator==(const Vertex &other) const;

    public:
        Math::Vector3F m_position;
        Math::Vector3F m_color;
        Math::Vector2F m_texCoord;
    };
}

#endif //GAMEENGINE_VERTEX_H
