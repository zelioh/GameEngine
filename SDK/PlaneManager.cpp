//
// Created by FiercePC on 09/11/2020.
//

#include "public/SDK/PlaneManager.h"
#include "public/GraphicsEngine/PlaneManager.h"
#include "public/GraphicsEngine/Plane.h"

sdk::Plane sdk::PlaneManager::createPlane(const std::string &levelIdentifier, const std::string &planeIdentifier,
                                     const Math::Vector3F &position, const Math::Vector3F &color,
                                     const Math::Vector3F &scale, const Math::SRotation &rotation)
{
    return Plane(object::PlaneManager::getInstance()->createPlane(levelIdentifier,
                                                                  planeIdentifier,
                                                                  position,
                                                                  color,
                                                                  scale,
                                                                  rotation));
}


sdk::Plane sdk::PlaneManager::createPlaneAutoName(const std::string &levelIdentifier, const Math::Vector3F &position,
                                             const Math::Vector3F &color, const Math::Vector3F &scale,
                                             const Math::SRotation &rotation)
{
    return Plane(object::PlaneManager::getInstance()->createPlaneAutoName(levelIdentifier,
                                                                  position,
                                                                  color,
                                                                  scale,
                                                                  rotation));
}

sdk::Plane sdk::PlaneManager::findPlane(const std::string &levelIdentifier, const std::string &planeIdentifier)
{
    return Plane(object::PlaneManager::getInstance()->findPlane(levelIdentifier, planeIdentifier));
}

void sdk::PlaneManager::delePlane(const std::string &levelIdentifier, const std::string &planeIdentifier)
{
    object::PlaneManager::getInstance()->deletePlane(levelIdentifier, planeIdentifier);
}