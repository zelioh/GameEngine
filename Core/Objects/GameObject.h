//
// Created by tangt on 26/10/2020.
//
// Main class that represent the common think between each objects
//

#ifndef GAMEENGINE_GAMEOBJECT_H
#define GAMEENGINE_GAMEOBJECT_H

#include "Vector3F.h"
#include "Vertex.h"
#include <vector>

namespace object {

    class GameObject {
    public:
        const Math::Vector3F & getPosition() const;
        const Math::Vector3F & getColor() const;

        void setPosition(const Math::Vector3F & position);
        void setColor(const Math::Vector3F & color);

        virtual const std::vector<graphics::Vertex> & getVertices() const = 0;
        virtual const std::vector<uint32_t> & getIndices() const = 0;

    protected:
        GameObject(const Math::Vector3F & position, const Math::Vector3F & color);

        Math::Vector3F m_position;
        Math::Vector3F m_color;
        std::vector<graphics::Vertex> m_vertices;
        std::vector<uint32_t> m_indices;
    };

}

#endif //GAMEENGINE_GAMEOBJECT_H
