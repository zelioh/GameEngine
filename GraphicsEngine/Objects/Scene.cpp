//
// Created by tangt on 31/10/2020.
//

#include "Scene.h"
#include "CubeManager.h"
#include "CameraManager.h"
#include "PlaneManager.h"

object::Scene::Scene(const std::string &identifier):
m_strIdentifier(identifier),
m_camera(nullptr)
{
}

std::vector<object::GameObject *> object::Scene::getSceneObjects() const
{
    std::vector<object::GameObject *> objects;

    {
        auto cubes = CubeManager::getInstance()->getObjectOfLevel(m_strIdentifier);

        objects.insert(objects.end(), cubes.begin(), cubes.end());
    }
    {
        auto planes = PlaneManager::getInstance()->getObjectOfLevel(m_strIdentifier);

        objects.insert(objects.end(), planes.begin(), planes.end());
    }
    return objects;
}

const std::string & object::Scene::getIndentifier()
{
    return m_strIdentifier;
}

bool object::Scene::setCurrentCamera(Camera *camera)
{
    m_camera = camera;
    return true;
}

bool object::Scene::setCurrentCamera(const std::string &cameraIdentifier)
{
    Camera * tmp = object::CameraManager::getInstance()->findCamera(m_strIdentifier, cameraIdentifier);

    if (nullptr == tmp)
    {
        return false;
    }
    m_camera = tmp;
    return true;
}

object::Camera * object::Scene::getCurrentCamera() const
{
    return m_camera;
}