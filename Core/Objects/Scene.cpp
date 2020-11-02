//
// Created by tangt on 31/10/2020.
//

#include "Scene.h"
#include "CubeManager.h"

object::Scene::Scene(const std::string &identifier):
m_strIdentifier(identifier)
{
}

std::vector<object::GameObject *> object::Scene::getSceneObjects() const
{
    std::vector<object::GameObject *> objects;

    {
        auto cubes = CubeManager::getInstance()->getObjectOfLevel(m_strIdentifier);

        objects.insert(objects.end(), cubes.begin(), cubes.end());
    }
    return objects;
}