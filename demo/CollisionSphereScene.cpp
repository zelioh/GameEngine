//
// Created by FiercePC on 15/11/2020.
//

#include "CollisionSphereScene.h"
#include "SDK/Scene.h"
#include "SDK/SceneManager.h"
#include "SDK/CubeManager.h"
#include "SDK/Cube.h"
#include "SDK/TextureManager.h"
#include "SDK/CameraManager.h"
#include "SDK/Camera.h"
#include "BoundingSphere.h"

CollisionSphereScene::CollisionSphereScene():
m_strIdentifier("CollisionSphereScene")
{
}

void CollisionSphereScene::postInitialize()
{
    sdk::Scene myLevel = sdk::SceneManager::createScene(m_strIdentifier);

    sdk::SceneManager::setCurrentScene(m_strIdentifier);

    sdk::Cube cube1 = sdk::CubeManager::createCube(
            m_strIdentifier,
            "TestCube",
            Math::Vector3F(-5.f, 0.f, 0.f),
            Math::Vector3F(1.f, 1.f, 1.f),
            Math::Vector3F(1.f, 1.f, 1.f),
            Math::SRotation{0.f, Math::Vector3F(0.f, 0.f, 1.f)}
    );


    sdk::Cube cube2 = sdk::CubeManager::createCube(
            m_strIdentifier,
            "TestCube2",
            Math::Vector3F(5.f, 0.f, 0.3f),
            Math::Vector3F(1.f, 1.f, 1.f),
            Math::Vector3F(1.f, 1.f, 1.f),
            Math::SRotation{0.f, Math::Vector3F(0.f, 0.f, 1.f)}
    );

    sdk::Texture boxTexture = sdk::TextureManager::createTexture("../assets/box.png", "Box");

    sdk::Camera camera = sdk::CameraManager::createCamera(m_strIdentifier,
                                                          "Camera_one",
                                                          Math::Vector3F(0.f, 3.f, 2.f),
                                                          Math::Vector3F(0.f, 0.f, 0.f),
                                                          Math::Vector3F(0.f, 0.f, 1.f));

    cube1.setTexture(boxTexture);
    cube2.setTexture(boxTexture);

    myLevel.setCurrentCamera(camera);

    auto * box1 = new PhysicsObject(new BoundingSphere(Vector3F(0.0f, 0.0f, 0.0f), 0.5f), Vector3F(1.f, 0.0f, 0.0f));
    auto * box2 = new PhysicsObject(new BoundingSphere(Vector3F(10.0f, 0.0f, 0.0f), 0.5f), Vector3F(-1.f, 0.0f, 0.0f));
    cube1.setPhysicalObject(box1);
    cube2.setPhysicalObject(box2);
}

void CollisionSphereScene::setToCurrentScene()
{
    sdk::SceneManager::setCurrentScene(m_strIdentifier);
}