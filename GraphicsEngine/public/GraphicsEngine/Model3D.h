//
// Created by tangt on 04/11/2020.
//

#ifndef GAMEENGINE_MODEL3D_H
#define GAMEENGINE_MODEL3D_H

#include "GameObject.h"
#include "public/GraphicsEngine/GraphicsEngine.h"

namespace object {

    class GRAPHICS_ENGINE_EXPORT Model3D: public GameObject
    {

        friend class Model3DManager;

    public:
        const vk::Buffer & getVertexBuffer() const final;
        const vk::Buffer & getIndexBuffer() const final;
        const std::vector<graphics::Vertex> & getVertices() const final;
        const std::vector<uint32_t> & getIndices() const final;

        void release() final;

    private:
        Model3D(const std::string & levelIdentifier,
                const std::string & identifier,
                const std::string & fileModel,
                const Math::Vector3F & position,
                const Math::Vector3F & color = Math::Vector3F(1.f, 1.f, 1.f),
                const Math::Vector3F & scale = Math::Vector3F(1.f, 1.f, 1.f),
                const SRotation & rotate = SRotation{0.f, Math::Vector3F(0.f, 0.f, 0.f)});
    };

}

#endif //GAMEENGINE_MODEL3D_H
