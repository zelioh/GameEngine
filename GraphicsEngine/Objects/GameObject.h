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
#include <string>

#include "ITextureObject.h"
#include "SRotation.h"
#include "PhysicsObject.h"

namespace graphics
{
    class LogicalDevice;
}

namespace object {
    class GameObject: public ITextureObject
    {
    public:
        const Math::Vector3F & getPosition() const;
        const Math::Vector3F & getColor() const;
        const Math::Vector3F & getScale() const;
        const SRotation & getRotate() const;

        void setPosition(const Math::Vector3F & position);
        void setColor(const Math::Vector3F & color);
        void setScale(const Math::Vector3F & scale);
        void setRotate(const SRotation & rotate);

        const std::string & getIdentifier() const;
        const std::string & getLevelIdentifier() const;

        virtual const std::vector<graphics::Vertex> & getVertices() const = 0;
        virtual const std::vector<uint32_t> & getIndices() const = 0;

        virtual const vk::Buffer & getVertexBuffer() const = 0;
        virtual const vk::Buffer & getIndexBuffer() const = 0;

        virtual void release() = 0;

        Math::Matrix4F getTransformationMatrix() const;
        void setPhysicsObject(PhysicsObject * object) { this->m_physicsObject = object; };
        PhysicsObject * getPhysicsObject() const { return this->m_physicsObject; };

    protected:
        GameObject(const std::string & levelIdentifier,
                   const std::string & identifier,
                   const Math::Vector3F & position,
                   const Math::Vector3F & color = Math::Vector3F(1.f, 1.f, 1.f),
                   const Math::Vector3F & scale = Math::Vector3F(1.f, 1.f, 1.f),
                   const SRotation & rotate = SRotation{0.f, Math::Vector3F(0.f, 0.f, 0.f)});

        Math::Vector3F m_position;
        Math::Vector3F m_color;
        Math::Vector3F m_scale;
        SRotation m_rotate;
        std::vector<graphics::Vertex> m_vertices;
        std::vector<uint32_t> m_indices;
        std::string m_strIdentifier;
        std::string m_strLevelIdentifier;

        //
        // Vertex buffer
        vk::Buffer m_vertexBuffer;
        vk::DeviceMemory m_verterBufferMemory;

        //
        // Index buffer
        vk::Buffer m_indexBuffer;
        vk::DeviceMemory m_indexBufferMemory;
        PhysicsObject * m_physicsObject;
    };

}

#endif //GAMEENGINE_GAMEOBJECT_H
