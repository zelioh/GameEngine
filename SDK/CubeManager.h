//
// Created by FiercePC on 09/11/2020.
//

#ifndef GAMEENGINE_SDK_CUBEMANAGER_H
#define GAMEENGINE_SDK_CUBEMANAGER_H

#include <string>
#include "../Math/Vector3F.h"
#include "../Math/SRotation.h"

namespace sdk {

    class Cube;

    class CubeManager
    {
    public:
          static Cube createCube(const std::string & levelIdentifier,
                                   const std::string & cubeIdentifier,
                                   const Math::Vector3F & position = Math::Vector3F(0.f, 0.f, 0.f),
                                   const Math::Vector3F & color = Math::Vector3F(1.f, 1.f, 1.f),
                                   const Math::Vector3F & scale = Math::Vector3F(1.f, 1.f, 1.f),
                                   const Math::SRotation & rotation = Math::SRotation{0.f, Math::Vector3F(0.f, 0.f, 0.f)});

          static Cube createCubeAutoName(const std::string & levelIdentifier,
                                           const Math::Vector3F & position = Math::Vector3F(0.f, 0.f, 0.f),
                                           const Math::Vector3F & color = Math::Vector3F(1.f, 1.f, 1.f),
                                           const Math::Vector3F & scale = Math::Vector3F(1.f, 1.f, 1.f),
                                           const Math::SRotation & rotation = Math::SRotation{0.f, Math::Vector3F(0.f, 0.f, 0.f)});

          static Cube findCube(const std::string & levelIdentifier, const std::string & cubeIdentifier);

          static void deleCube(const std::string & levelIdentifier, const std::string & cubeIdentifier);
    };

}

#endif //GAMEENGINE_CUBEMANAGER_H
