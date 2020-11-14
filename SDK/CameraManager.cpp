//
// Created by FiercePC on 09/11/2020.
//

#include "public/SDK/CameraManager.h"
#include "public/GraphicsEngine/CameraManager.h"

sdk::Camera sdk::CameraManager::createCamera(const std::string &levelIdentifier, const std::string &cameraIdentifier,
                                        const Math::Vector3F &position, const Math::Vector3F &target,
                                        const Math::Vector3F &upAxis)
{
    return Camera(object::CameraManager::getInstance()->createCamera(levelIdentifier,
                                                                     cameraIdentifier,
                                                                     position,
                                                                     target,
                                                                     upAxis));
}

sdk::Camera sdk::CameraManager::createCameraAutoName(const std::string &levelIdentifier, const Math::Vector3F &position,
                                                const Math::Vector3F &target, const Math::Vector3F &upAxis)
{
    return Camera(object::CameraManager::getInstance()->createCameraAutoName(levelIdentifier,
                                                                     position,
                                                                     target,
                                                                     upAxis));
}

sdk::Camera sdk::CameraManager::findCamera(const std::string &levelIdentifier, const std::string &cameraIdentifier)
{
    return Camera(object::CameraManager::getInstance()->findCamera(levelIdentifier, cameraIdentifier));
}

bool sdk::CameraManager::deleteCamera(const std::string &levelIdentifier, const std::string &cameraIdentifier)
{
    return object::CameraManager::getInstance()->deleteCamera(levelIdentifier, cameraIdentifier);
}