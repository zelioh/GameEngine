//
// Created by tangt on 03/11/2020.
//

#ifndef GAMEENGINE_PLANE_H
#define GAMEENGINE_PLANE_H

#include "Cube.h"

#include "public/GraphicsEngine/GraphicsEngine.h"

namespace object {

    class GRAPHICS_ENGINE_EXPORT Plane: public Cube
    {

        friend class PlaneManager;

    private:
        Plane(const std::string & levelIdentifier,
             const std::string & identifier,
             const Math::Vector3F & position,
             const Math::Vector3F & color = Math::Vector3F(1.f, 1.f, 1.f),
             const Math::Vector3F & scale = Math::Vector3F(1.f, 1.f, 1.f),
             const Math::SRotation & rotate = SRotation{0.f, Math::Vector3F(0.f, 0.f, 0.f)});
    };

}

#endif //GAMEENGINE_PLANE_H
