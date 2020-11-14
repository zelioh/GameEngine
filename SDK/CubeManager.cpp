//
// Created by FiercePC on 09/11/2020.
//

#include "public/SDK/Cube.h"
#include "public/SDK/CubeManager.h"
#include "public/GraphicsEngine/Cube.h"
#include "public/GraphicsEngine/CubeManager.h"

sdk::Cube sdk::CubeManager::createCube(const std::string &levelIdentifier,
                                       const std::string &cubeIdentifier,
                                       const Math::Vector3F &position,
                                       const Math::Vector3F &color,
                                       const Math::Vector3F &scale,
                                       const Math::SRotation &rotation)
{
    return sdk::Cube(object::CubeManager::getInstance()->createCube(levelIdentifier,
                                                                    cubeIdentifier,
                                                                    position,
                                                                    color,
                                                                    scale,
                                                                    rotation));
}

sdk::Cube sdk::CubeManager::createCubeAutoName(const std::string &levelIdentifier, const Math::Vector3F &position,
                                          const Math::Vector3F &color, const Math::Vector3F &scale,
                                          const Math::SRotation &rotation)
{
    return sdk::Cube(object::CubeManager::getInstance()->createCubeAutoName(levelIdentifier,
                                                                    position,
                                                                    color,
                                                                    scale,
                                                                    rotation));
}

sdk::Cube sdk::CubeManager::findCube(const std::string &levelIdentifier, const std::string &cubeIdentifier)
{
    return sdk::Cube(object::CubeManager::getInstance()->findCube(levelIdentifier, cubeIdentifier));
}

void sdk::CubeManager::deleCube(const std::string &levelIdentifier, const std::string &cubeIdentifier)
{
    object::CubeManager::getInstance()->deleteCube(levelIdentifier, levelIdentifier);
}