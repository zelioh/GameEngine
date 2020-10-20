//
// Created by tangt on 13/10/2020.
//
//  Represent a vertice instance in the engine
//

#ifndef GAMEENGINE_VERTEX_H
#define GAMEENGINE_VERTEX_H

#include "vulkan/vulkan.hpp"
#include "Vector3F.h"

namespace graphics {

    class Vertex {
    public:
        Vertex() = default;

        static vk::VertexInputBindingDescription getBindDescription();
        static std::array<vk::VertexInputAttributeDescription, 3> getAttributeDescription();
        bool operator==(const Vertex &other) const;

    public:
        Math::Vector3F position;
        Math::Vector3F color;
        Math::Vector3F texColor;
    };
}

#endif //GAMEENGINE_VERTEX_H
