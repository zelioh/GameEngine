//
// Created by FiercePC on 09/11/2020.
//

#include "SceneManager.h"
#include "Objects/SceneManager.h"
#include "Scene.h"
#include "Objects/Scene.h"

sdk::Scene sdk::SceneManager::createScene(const std::string &identifier)
{
    return Scene(object::SceneManager::getInstance()->createScene(identifier));
}

sdk::Scene sdk::SceneManager::getCurrentScene()
{
    return Scene(object::SceneManager::getInstance()->getCurrentScene());
}

const std::string & sdk::SceneManager::getCurrentSceneIdentifier()
{
    return object::SceneManager::getInstance()->getCurrentSceneIdentifier();
}

bool sdk::SceneManager::setCurrentScene(const std::string &identifier)
{
    return object::SceneManager::getInstance()->setCurrentScene(identifier);
}

bool sdk::SceneManager::releaseScene(const std::string &identifier)
{
    return object::SceneManager::getInstance()->releaseScene(identifier);
}