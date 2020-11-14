//
// Created by tangt on 03/11/2020.
//

#include "GraphicsEngine/Camera.h"
#include "Math_utils.h"

const Math::Vector3F & object::Camera::getPosition() const
{
    return m_position;
}

const Math::Vector3F & object::Camera::getTarget() const
{
    return m_target;
}

const Math::Vector3F & object::Camera::getUpAxis() const
{
    return m_upAxis;
}

const Math::Matrix4F & object::Camera::getViewMatrix() const
{
    return m_viewMatrix;
}

const std::string & object::Camera::getLevelIdentifier() const
{
    return m_strLevelIdentifier;
}

const std::string & object::Camera::getIdentifier() const
{
    return m_strIdentifier;
}

void object::Camera::setPosition(const Math::Vector3F &position)
{
    m_position = position;
    computeViewMatrix();
}

void object::Camera::setTarget(const Math::Vector3F &target)
{
    m_target = target;
    computeViewMatrix();
}

void object::Camera::setUpAxis(const Math::Vector3F &upAxis)
{
    m_upAxis = upAxis;
}

object::Camera::Camera(const std::string & levelIdentifier,
                       const std::string & identifier,
                       const Math::Vector3F &position,
                       const Math::Vector3F &target,
                       const Math::Vector3F &upAxis):
m_position(position),
m_target(target),
m_upAxis(upAxis),
m_viewMatrix(),
m_strLevelIdentifier(levelIdentifier),
m_strIdentifier(identifier)
{
    computeViewMatrix();
}

void object::Camera::computeViewMatrix()
{
    Math::Vector3F cameraDirection = Math::utils::normalize(m_position - m_target);
    Math::Vector3F cameraRight = Math::utils::normalize(Math::utils::cross(m_upAxis, cameraDirection));
    Math::Vector3F cameraUp = Math::utils::cross(cameraDirection, cameraRight);

    m_viewMatrix = MATRIX4F_IDENTITY;

    m_viewMatrix(0, 0) = cameraRight.X;
    m_viewMatrix(1, 0) = cameraRight.Y;
    m_viewMatrix(2, 0) = cameraRight.Z;
    m_viewMatrix(0, 1) = cameraUp.X;
    m_viewMatrix(1, 1) = cameraUp.Y;
    m_viewMatrix(2, 1) = cameraUp.Z;
    m_viewMatrix(0, 2) = cameraDirection.X;
    m_viewMatrix(1, 2) = cameraDirection.Y;
    m_viewMatrix(2, 2) = cameraDirection.Z;
    m_viewMatrix(3, 0) = -Math::utils::dot(cameraRight, m_position);
    m_viewMatrix(3, 1) = -Math::utils::dot(cameraUp, m_position);
    m_viewMatrix(3, 2) = -Math::utils::dot(cameraDirection, m_position);;
}