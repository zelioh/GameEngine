//
// Created by tangt on 13/10/2020.
//
//  Represent a vertice instance in the engine
//

#ifndef GAMEENGINE_VERTEX_H
#define GAMEENGINE_VERTEX_H

#include "vulkan/vulkan.hpp"
#include "../Math/Vector3F.h"
#include "../Math/Vector2F.h"
#include "public/GraphicsEngine/GraphicsEngine.h"

namespace graphics {

    struct GRAPHICS_ENGINE_EXPORT Vertex {

        Math::Vector3F m_position;
        Math::Vector3F m_color;
        Math::Vector2F m_texCoord;
        Math::Vector3F m_normal;

        static vk::VertexInputBindingDescription getBindDescription();
        static std::array<vk::VertexInputAttributeDescription, 4> getAttributeDescription();
        bool operator==(const Vertex &other) const;
    };
}

#endif //GAMEENGINE_VERTEX_H
