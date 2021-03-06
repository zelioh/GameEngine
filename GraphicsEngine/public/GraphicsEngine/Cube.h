//
// Created by tangt on 26/10/2020.
//
// Represent a cube into the game
//

#ifndef GAMEENGINE_CUBE_H
#define GAMEENGINE_CUBE_H

#include "GameObject.h"
#include "public/GraphicsEngine/GraphicsEngine.h"

namespace object {

class GRAPHICS_ENGINE_EXPORT Cube : public GameObject
    {

        friend class CubeManager;

    public:
        const std::vector<graphics::Vertex> & getVertices() const final;
        const std::vector<uint32_t> & getIndices() const final;
        const vk::Buffer & getVertexBuffer() const final;
        const vk::Buffer & getIndexBuffer() const final;

        void release() final;

    protected:
        Cube(const std::string & levelIdentifier,
             const std::string & identifier,
             const Math::Vector3F & position,
             const Math::Vector3F & color = Math::Vector3F(1.f, 1.f, 1.f),
             const Math::Vector3F & scale = Math::Vector3F(1.f, 1.f, 1.f),
             const Math::SRotation & rotate = Math::SRotation{0.f, Math::Vector3F(0.f, 0.f, 0.f)});
    };

}

#endif //GAMEENGINE_CUBE_H
