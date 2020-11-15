//
// Created by FiercePC on 15/11/2020.
//

#include "CubeScene.h"
#include "SDK/CubeManager.h"
#include "SDK/Cube.h"
#include "SDK/SceneManager.h"
#include "SDK/Scene.h"
#include "PhysicsObject.h"
#include "SDK/TextureManager.h"
#include "SDK/CameraManager.h"
#include "BoundingSphere.h"
#include "Event.h"
#include "SDK/LightManager.h"
#include "SDK/Light.h"
#include "BoundingBox.h"

CubeScene::CubeScene():
m_strIdentifier("CubeScene")
{
}

void CubeScene::postInitialize()
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
            Math::Vector3F(5.f, 0.f, 0.f),
            Math::Vector3F(1.f, 1.f, 1.f),
            Math::Vector3F(1.f, 1.f, 1.f),
            Math::SRotation{0.f, Math::Vector3F(0.f, 0.f, 1.f)}
    );

    sdk::Cube cube3 = sdk::CubeManager::createCube(
            m_strIdentifier,
            "TestCube3",
            Math::Vector3F(2.f, -1.f, 0.f),
            Math::Vector3F(0.f, 1.5f, 0.f),
            Math::Vector3F(1.5f, 1.5f, 1.5f),
            Math::SRotation{90.f, Math::Vector3F(0.f, 0.f, 1.f)});

    sdk::Cube cube4 = sdk::CubeManager::createCube(
            m_strIdentifier,
            "TestCube4",
            Math::Vector3F(0.f, 2.f, 0.f),
            Math::Vector3F(0.5f, 0.5f, 0.5f),
            Math::Vector3F(0.5f, 0.5f, 0.5f),
            Math::SRotation{90.f, Math::Vector3F(0.f, 0.f, 1.f)});

    sdk::Cube cube5 = sdk::CubeManager::createCube(
            m_strIdentifier,
            "TestCube5",
            Math::Vector3F(-1.f, 0.5f, 0.f),
            Math::Vector3F(0.f, 0.f, 0.5f),
            Math::Vector3F(0.5f, 0.5f, 0.5f),
            Math::SRotation{0.f, Math::Vector3F(0.f, 0.f, 1.f)});

    sdk::Texture boxTexture = sdk::TextureManager::createTexture("../assets/box.png", "Box");
    sdk::Texture phoenixTexture = sdk::TextureManager::createTexture("../assets/texture.jpg", "Phoenix");

    cube1.setTexture(boxTexture);
    cube3.setTexture(phoenixTexture);
    cube4.setTexture(phoenixTexture);
    cube5.setTexture(phoenixTexture);

    sdk::Camera camera = sdk::CameraManager::createCamera(m_strIdentifier,
                                                          "Camera_one",
                                                          Math::Vector3F(0.f, 3.f, 2.f),
                                                          Math::Vector3F(0.f, 0.f, 0.f),
                                                          Math::Vector3F(0.f, 0.f, 1.f));

    myLevel.setCurrentCamera(camera);

//    auto * box1 = new PhysicsObject(new BoundingSphere(Vector3F(0.0f, 0.0f, 0.0f), 0.5f), Vector3F(1.f, 0.0f, 0.0f));
//    auto * box2 = new PhysicsObject(new BoundingSphere(Vector3F(10.0f, 0.0f, 0.0f), 0.5f), Vector3F(-1.f, 0.0f, 0.0f));
    auto * box1 = new PhysicsObject(new BoundingBox(Vector3F(0.0f, 0.0f, 0.0f), Vector3F(1.0f, 1.0f, 1.0f)), Vector3F(1.0f, 0.0f, 0.0f));
    auto * box2 = new PhysicsObject(new BoundingBox(Vector3F(10.0f, 0.0f, 0.0f), Vector3F(1.0f, 1.0f, 1.0f)), Vector3F(-1.0f, 0.0f, 0.0f));

    cube1.setPhysicalObject(box1);
    cube2.setPhysicalObject(box2);

//    sdk::LightManager::createLight(m_strIdentifier,
//                                   "light_000",
//                                   Math::Vector3F(0.f, 0.f, 2.f),
//                                   0.2f,
//                                   0.3f,
//                                   Math::Vector3F(1.f, 1.f, 1.f));
}

void CubeScene::preUpdate(float deltaTime)
{
    sdk::Cube cube3 = sdk::CubeManager::findCube(m_strIdentifier, "TestCube3");
    sdk::Cube cube4 = sdk::CubeManager::findCube(m_strIdentifier, "TestCube4");

    cube3.setRotate(Math::SRotation{cube3.getRotation().angle + 90.f * deltaTime, Math::Vector3F(1.f, 0.f, 0.f)});

    if (HID::mouse::IsLeftMouseKeyDown()) {
        static float currentAngle = 90.f;

        currentAngle += 90.f * deltaTime;

        cube4.setRotate(Math::SRotation{currentAngle, cube4.getRotation().axis});
    }
}

void CubeScene::setToCurrentScene()
{
    sdk::SceneManager::setCurrentScene(m_strIdentifier);
}