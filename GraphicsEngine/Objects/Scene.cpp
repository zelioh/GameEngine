//
// Created by tangt on 31/10/2020.
//

#include "Scene.h"
#include "CubeManager.h"
#include "CameraManager.h"
#include "PlaneManager.h"
#include "Model3DManager.h"
#include "LightManager.h"
#include "Light.h"
#include "Cube.h"
#include "GameObject.h"

object::Scene::Scene(const std::string &identifier):
m_strIdentifier(identifier),
m_camera(nullptr),
m_light(nullptr)
{
}

std::vector<object::GameObject *> object::Scene::getSceneObjects()
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
    {
        auto models = Model3DManager::getInstance()->getObjectOfLevel(m_strIdentifier);

        objects.insert(objects.end(), models.begin(), models.end());
    }
	{
		auto lights = LightManager::getInstance()->getLightOfScene(m_strIdentifier);

        if (lights.size() <= 0)
        {
            m_light = nullptr;
        } else {
            m_light = lights[0]; ///< Take the first available light. TODO: multi-lighting
        }
        objects.push_back(lights[0]);
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

PhysicsEngine & object::Scene::getPhysicsEngine()
{
    return m_physicsEngine;
}

object::Light * object::Scene::getLight() const
{
    return m_light;
}

void object::Scene::update()
{
    auto objects = getSceneObjects();

    for (auto obj : objects)
    {
        obj->Update();
    }
}

void object::Scene::release()
{
    CubeManager::getInstance()->releaseScene(m_strIdentifier);
    PlaneManager::getInstance()->releaseScene(m_strIdentifier);
    Model3DManager::getInstance()->releaseScene(m_strIdentifier);
    LightManager::getInstance()->releaseScene(m_strIdentifier);
}