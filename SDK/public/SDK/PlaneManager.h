//
// Created by FiercePC on 09/11/2020.
//

#ifndef GAMEENGINE_SDK_PLANEMANAGER_H
#define GAMEENGINE_SDK_PLANEMANAGER_H

#include "Plane.h"
#include "SDK.h"

namespace sdk {

    class SDK_EXPORT PlaneManager {
    public:
        static Plane createPlane(const std::string & levelIdentifier,
                               const std::string & planeIdentifier,
                               const Math::Vector3F & position = Math::Vector3F(0.f, 0.f, 0.f),
                               const Math::Vector3F & color = Math::Vector3F(1.f, 1.f, 1.f),
                               const Math::Vector3F & scale = Math::Vector3F(1.f, 1.f, 1.f),
                               const Math::SRotation & rotation = Math::SRotation{0.f, Math::Vector3F(0.f, 0.f, 0.f)});

        static Plane createPlaneAutoName(const std::string & levelIdentifier,
                                       const Math::Vector3F & position = Math::Vector3F(0.f, 0.f, 0.f),
                                       const Math::Vector3F & color = Math::Vector3F(1.f, 1.f, 1.f),
                                       const Math::Vector3F & scale = Math::Vector3F(1.f, 1.f, 1.f),
                                       const Math::SRotation & rotation = Math::SRotation{0.f, Math::Vector3F(0.f, 0.f, 0.f)});

        static Plane findPlane(const std::string & levelIdentifier, const std::string & planeIdentifier);

        static void delePlane(const std::string & levelIdentifier, const std::string & planeIdentifier);
    };

}

#endif //GAMEENGINE_PLANEMANAGER_H
