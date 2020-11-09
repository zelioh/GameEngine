//
// Created by FiercePC on 09/11/2020.
//

#include "Objects/Model3DManager.h"
#include "Model3DManager.h"

sdk::Model3D sdk::Model3DManager::createModel3D(const std::string &levelIdentifier, const std::string &identifier,
                                           const std::string &fileModel, const Math::Vector3F &position,
                                           const Math::Vector3F &color, const Math::Vector3F &scale,
                                           const SRotation &rotate)
{
    return Model3D(object::Model3DManager::getInstance()->createModel3D(levelIdentifier,
                                                                        identifier,
                                                                        fileModel,
                                                                        position,
                                                                        color,
                                                                        scale,
                                                                        rotate));
}

sdk::Model3D sdk::Model3DManager::createModel3DAutoName(const std::string &levelIdentifier, const std::string &fileModel,
                                                   const Math::Vector3F &position, const Math::Vector3F &color,
                                                   const Math::Vector3F &scale, const SRotation &rotate)
{
    return Model3D(object::Model3DManager::getInstance()->createModel3DAutoName(levelIdentifier,
                                                                        fileModel,
                                                                        position,
                                                                        color,
                                                                        scale,
                                                                        rotate));
}

sdk::Model3D sdk::Model3DManager::findModel3D(const std::string &levelIdentifier, const std::string &identifier)
{
    return Model3D(object::Model3DManager::getInstance()->findModel3D(levelIdentifier, identifier));
}

void sdk::Model3DManager::deleteModel3D(const std::string &levelIdentifier, const std::string &modelIdentifier)
{
    object::Model3DManager::getInstance()->deleteModel3D(levelIdentifier, modelIdentifier);
}