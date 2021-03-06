//
// Created by tangt on 26/10/2020.
//
// Main class that represent the common think between each objects
//

#include "GraphicsEngine/GameObject.h"
#include "GraphicsEngine/LogicalDevice.h"
#include "GraphicsEngine/SceneManager.h"
#include "PhysicsObject.h"

object::GameObject::GameObject(const std::string & levelIdentifier,
                               const std::string & identifier,
                               const Math::Vector3F & position,
                               const Math::Vector3F & color,
                               const Math::Vector3F & scale /*=Math::Vector3F(1, 1, 1)*/,
                               const SRotation & rotate /*=SRotation{0, Vector3F(0, 0, 0)}*/):
m_strIdentifier(identifier),
m_strLevelIdentifier(levelIdentifier),
m_position(position),
m_color(color),
m_scale(scale),
m_rotate(rotate),
m_vertices(),
m_indices(),
m_physicsObject(nullptr)
{
    m_texture = nullptr;
}

const Math::Vector3F & object::GameObject::getColor() const
{
    return m_color;
}

const Math::Vector3F & object::GameObject::getPosition() const
{
    return m_position;
}

const Math::Vector3F & object::GameObject::getScale() const
{
    return m_scale;
}

const Math::SRotation & object::GameObject::getRotate() const
{
    return m_rotate;
}

void object::GameObject::setPosition(const Math::Vector3F &position)
{
    m_position = position;
    m_physicsObject->SetPosition(position);
}

void object::GameObject::setColor(const Math::Vector3F &color)
{
    m_color = color;
}

void object::GameObject::setScale(const Math::Vector3F &scale)
{
    m_scale = scale;
}

void object::GameObject::setRotate(const Math::SRotation &rotate)
{
    m_rotate = rotate;
}

const std::string & object::GameObject::getIdentifier() const
{
    return m_strIdentifier;
}

const std::string & object::GameObject::getLevelIdentifier() const
{
    return m_strLevelIdentifier;
}

Math::Matrix4F object::GameObject::getTransformationMatrix() const
{
    Math::Matrix4F translation = MATRIX4F_IDENTITY;

    Math::Vector4F t0 = Math::Vector4F(translation(0, 0), translation(0, 1), translation(0, 2), translation(0, 3)) * m_position.X;
    Math::Vector4F t1 = Math::Vector4F(translation(1, 0), translation(1, 1), translation(1, 2), translation(1, 3)) * m_position.Y;
    Math::Vector4F t2 = Math::Vector4F(translation(2, 0), translation(2, 1), translation(2, 2), translation(2, 3)) * m_position.Z;
    Math::Vector4F t3 = Math::Vector4F(translation(3, 0), translation(3, 1), translation(3, 2), translation(3, 3)) * 1;
    Math::Vector4F ttotal = t0 + t1 + t2 + t3;

    translation(3, 0) = ttotal.X;
    translation(3, 1) = ttotal.Y;
    translation(3, 2) = ttotal.Z;
    translation(3, 3) = ttotal.W;

    Math::Matrix4F transformation = translation;

    m_rotate.rotateMatrix(transformation);

    transformation(0, 0) *= m_scale.X;
    transformation(0, 1) *= m_scale.X;
    transformation(0, 2) *= m_scale.X;
    transformation(0, 3) *= m_scale.X;

    transformation(1, 0) *= m_scale.Y;
    transformation(1, 1) *= m_scale.Y;
    transformation(1, 2) *= m_scale.Y;
    transformation(1, 3) *= m_scale.Y;

    transformation(2, 0) *= m_scale.Z;
    transformation(2, 1) *= m_scale.Z;
    transformation(2, 2) *= m_scale.Z;
    transformation(2, 3) *= m_scale.Z;

    return transformation;
}

void object::GameObject::setPhysicsObject(PhysicsObject *object)
{
    m_physicsObject = object;
    m_physicsObject->SetPosition(m_position);
    SceneManager::getInstance()->findScene(m_strLevelIdentifier)->getPhysicsEngine().AddPhysicsObject(m_physicsObject);
}

PhysicsObject * object::GameObject::getPhysicsObject() const
{
    return m_physicsObject;
}

void object::GameObject::Update()
{
    if (nullptr != m_physicsObject) {
        m_position = m_physicsObject->GetPosition();
    }
}