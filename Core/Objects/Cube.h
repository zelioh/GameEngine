//
// Created by tangt on 26/10/2020.
//
// Represent a cube into the game
//

#ifndef GAMEENGINE_CUBE_H
#define GAMEENGINE_CUBE_H

#include "GameObject.h"

namespace object {

    class Cube : public GameObject
    {

        friend class CubeManager;

    public:
        const std::vector<graphics::Vertex> & getVertices() const override;
        const std::vector<uint32_t> & getIndices() const override;

    private:
        Cube(const std::string & identifier,
             const Math::Vector3F & position,
             const Math::Vector3F & color,
             const Math::Vector3F & scale = Math::Vector3F(1.f, 1.f, 1.f),
             const Math::Vector3F & rotate = Math::Vector3F(0.f, 0.f, 0.f));
    };

}

#endif //GAMEENGINE_CUBE_H
