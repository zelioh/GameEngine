//
// Created by FiercePC on 15/11/2020.
//

#include "LightScene.h"
#include "SDK/CubeManager.h"
#include "SDK/Cube.h"
#include "SDK/Camera.h"
#include "SDK/CameraManager.h"
#include "SDK/TextureManager.h"
#include "SDK/PlaneManager.h"
#include "SDK/Scene.h"
#include "SDK/SceneManager.h"
#include "SDK/Light.h"
#include "SDK/LightManager.h"

LightScene::LightScene():
m_strIdentifier("LightScene"),
m_bTopReach(true)
{
}

void LightScene::postInitialize()
{
    sdk::Scene scene = sdk::SceneManager::createScene(m_strIdentifier);

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

    cube3.setTexture(boxTexture);
    cube4.setTexture(phoenixTexture);
    cube5.setTexture(phoenixTexture);

    sdk::Plane plane = sdk::PlaneManager::createPlane(
            m_strIdentifier,
            "Cool_plane",
            Math::Vector3F(0.f, 0.f, -2.f),
            Math::Vector3F(1.f, 0.2f, 0.4f),
            Math::Vector3F(5.f, 5.f, 5.f),
            Math::SRotation{90.f, Math::Vector3F(1.f, 0.f, 0.f)});

    sdk::Camera camera = sdk::CameraManager::createCamera(m_strIdentifier,
                                                          "Camera_one",
                                                          Math::Vector3F(0.f, 3.f, 2.f),
                                                          Math::Vector3F(0.f, 0.f, 0.f),
                                                          Math::Vector3F(0.f, 0.f, 1.f));

    scene.setCurrentCamera(camera);

    sdk::LightManager::createLight(m_strIdentifier,
                                   "light_000",
                                   Math::Vector3F(0.f, 0.f, 2.f),
                                   0.2f,
                                   0.3f,
                                   Math::Vector3F(1.f, 1.f, 1.f));
}

void LightScene::preUpdate(float deltaTime)
{
    sdk::Light light = sdk::LightManager::findLight(m_strIdentifier, "light_000");
    Math::Vector3F color = light.getColor();

    color.Z = (m_bTopReach) ? color.Z - (1.f * deltaTime) : color.Z + (1.f * deltaTime);

    if (color.Z >= 1.f)
    {
        m_bTopReach = true;
    }
    if (color.Z <= 0.f)
    {
        m_bTopReach = false;
    }
    light.setColor(color);
}

void LightScene::setToCurrentScene()
{
    sdk::SceneManager::setCurrentScene(m_strIdentifier);
}