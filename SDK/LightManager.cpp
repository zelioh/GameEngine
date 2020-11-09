//
// Created by FiercePC on 09/11/2020.
//

#include "LightManager.h"
#include "Objects/LightManager.h"

sdk::Light sdk::LightManager::createLight(const std::string &levelIdentifier, const std::string &LightIdentifier,
                                     const Math::Vector3F &position, float strength, float specular,
                                     const Math::Vector3F &color)
{
    return Light(object::LightManager::getInstance()->createLight(levelIdentifier,
                                                                  LightIdentifier,
                                                                  position,
                                                                  strength,
                                                                  specular,
                                                                  color));
}

sdk::Light sdk::LightManager::createLightAutoName(const std::string &levelIdentifier, const Math::Vector3F &position,
                                             float strength, float specular, const Math::Vector3F &color)
{
    return Light(object::LightManager::getInstance()->createLightAutoName(levelIdentifier,
                                                                  position,
                                                                  strength,
                                                                  specular,
                                                                  color));
}

sdk::Light sdk::LightManager::findLight(const std::string &levelIdentifier, const std::string &LightIdentifier)
{
    return Light(object::LightManager::getInstance()->findLight(levelIdentifier, LightIdentifier));
}

bool sdk::LightManager::deleteLight(const std::string &levelIdentifier, const std::string &LightIdentifier)
{
    return object::LightManager::getInstance()->deleteLight(levelIdentifier, LightIdentifier);
}
