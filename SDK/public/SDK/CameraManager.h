//
// Created by FiercePC on 09/11/2020.
//

#ifndef GAMEENGINE_SDK_CAMERAMANAGER_H
#define GAMEENGINE_SDK_CAMERAMANAGER_H

#include "Camera.h"
#include "SDK.h"

namespace sdk {

    class SDK_EXPORT CameraManager {
    public:
        static Camera createCamera(const std::string & levelIdentifier,
                              const std::string & cameraIdentifier,
                              const Math::Vector3F & position,
                              const Math::Vector3F & target,
                              const Math::Vector3F & upAxis);

        static Camera createCameraAutoName(const std::string & levelIdentifier,
                                      const Math::Vector3F & position,
                                      const Math::Vector3F & target,
                                      const Math::Vector3F & upAxis);

        static Camera findCamera(const std::string & levelIdentifier, const std::string & cameraIdentifier);

        static bool deleteCamera(const std::string & levelIdentifier, const std::string & cameraIdentifier);
    };

}

#endif //GAMEENGINE_CAMERAMANAGER_H
