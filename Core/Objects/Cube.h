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
    public:
        const std::vector<graphics::Vertex> & getVertices() const override;
        const std::vector<uint32_t> & getIndices() const override;

    private:
        Cube(const Math::Vector3F & position, const Math::Vector3F & color);
    };

}

#endif //GAMEENGINE_CUBE_H
