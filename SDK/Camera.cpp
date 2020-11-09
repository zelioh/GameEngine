//
// Created by FiercePC on 09/11/2020.
//

#include "Camera.h"
#include "Objects/Camera.h"

sdk::Camera::Camera(object::Camera *pEngineCamera):
m_pObjectCamera(pEngineCamera)
{
}

const Math::Vector3F & sdk::Camera::getPosition() const
{
    return m_pObjectCamera->getPosition();
}

const Math::Vector3F & sdk::Camera::getTarget() const
{
    return m_pObjectCamera->getTarget();
}

const Math::Vector3F & sdk::Camera::getUpAxis() const
{
    return m_pObjectCamera->getUpAxis();
}

const std::string & sdk::Camera::getLevelIdentifier() const
{
    return m_pObjectCamera->getLevelIdentifier();
}

const std::string & sdk::Camera::getIndentifier() const
{
    return m_pObjectCamera->getIdentifier();
}

void sdk::Camera::setPosition(const Math::Vector3F &position)
{
    m_pObjectCamera->setPosition(position);
}

void sdk::Camera::setTarget(const Math::Vector3F &target)
{
    m_pObjectCamera->setTarget(target);
}

void sdk::Camera::setUpAxis(const Math::Vector3F &upAxis)
{
    m_pObjectCamera->setUpAxis(upAxis);
}