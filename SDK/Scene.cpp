//
// Created by FiercePC on 09/11/2020.
//

#include "Scene.h"
#include "Objects/Scene.h"

sdk::Scene::Scene(object::Scene *pEngineScene):
m_pScene(pEngineScene)
{
}

const std::string & sdk::Scene::getIdentifier() const
{
    return m_pScene->getIndentifier();
}

sdk::Camera sdk::Scene::getCurrentCamera() const
{
    return Camera(m_pScene->getCurrentCamera());
}

void sdk::Scene::setCurrentCamera(const sdk::Camera &camera)
{
    m_pScene->setCurrentCamera(camera.m_pObjectCamera);
}

bool sdk::Scene::setCurrentCamera(const std::string &cameraIdentifier)
{
    return m_pScene->setCurrentCamera(cameraIdentifier);
}