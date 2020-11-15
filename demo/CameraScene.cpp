//
// Created by FiercePC on 15/11/2020.
//

#include "CameraScene.h"
#include "SDK/Model3D.h"
#include "SDK/Model3DManager.h"
#include "SDK/TextureManager.h"
#include "SDK/Camera.h"
#include "SDK/CameraManager.h"
#include "SDK/SceneManager.h"
#include "SDK/Scene.h"
#include "SDK/Window.h"
#include "Event.h"
#include "SDK/LightManager.h"
#include "SDK/Light.h"

CameraScene::CameraScene():
m_strIdentifier("CameraScene")
{

}

void CameraScene::postInitialize()
{
    sdk::Scene scene = sdk::SceneManager::createScene(m_strIdentifier);

    sdk::Model3D viking_room = sdk::Model3DManager::createModel3D(
            m_strIdentifier,
            "Viking_room",
            "../models/viking_room.obj",
            Math::Vector3F(0.f, 0.f, 0.f),
            Math::Vector3F(1.f, 1.f, 1.f),
            Math::Vector3F(2.f, 2.f, 2.f));

    sdk::Texture viking_room_texture = sdk::TextureManager::createTexture("../assets/viking_room.png", "Viking_room");

    viking_room.setTexture(viking_room_texture);
    viking_room.setRotate(Math::SRotation{90.f, Math::Vector3F(0.f, 0.f, 1.f)});

    sdk::Camera camera = sdk::CameraManager::createCamera(m_strIdentifier,
                                                          "Camera_one",
                                                          Math::Vector3F(0.f, 3.f, 2.f),
                                                          Math::Vector3F(0.f, 0.f, 0.f),
                                                          Math::Vector3F(0.f, 0.f, 1.f));

    sdk::Camera camera2 = sdk::CameraManager::createCamera(m_strIdentifier,
                                                           "Camera_two",
                                                           Math::Vector3F(0.f, -3.f, 2.f),
                                                           Math::Vector3F(0.f, 0.f, 0.f),
                                                           Math::Vector3F(0.f, 0.f, 1.f));
    sdk::Camera camera3 = sdk::CameraManager::createCamera(m_strIdentifier,
                                                           "Camera_three",
                                                           Math::Vector3F(0.f, 1.f, 3.f),
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

void CameraScene::preUpdate(float deltaTime)
{
    sdk::Camera camera1 = sdk::CameraManager::findCamera(m_strIdentifier, "Camera_one");
    sdk::Camera camera2 = sdk::CameraManager::findCamera(m_strIdentifier, "Camera_two");
    sdk::Camera camera3 = sdk::CameraManager::findCamera(m_strIdentifier, "Camera_three");

    if (HID::keyboard::IsKeyDown(HID::KEY::NUM1))
    {
        sdk::SceneManager::findScene(m_strIdentifier).setCurrentCamera(camera1);
    } else if (HID::keyboard::IsKeyDown(HID::KEY::NUM2)) {
        sdk::SceneManager::findScene(m_strIdentifier).setCurrentCamera(camera2);
    } else if (HID::keyboard::IsKeyDown(HID::KEY::NUM3)) {
        sdk::SceneManager::findScene(m_strIdentifier).setCurrentCamera(camera3);
    }

    sdk::Camera camera = sdk::SceneManager::findScene(m_strIdentifier).getCurrentCamera();

    Math::Vector3F p = camera.getPosition();
    Math::Vector3F t = camera.getTarget();

    float moveFactor = 2.5f * deltaTime;

    if (HID::keyboard::IsKeyDown(HID::KEY::S)) {
        p.Y += moveFactor;
        t.Y += moveFactor;
    }
    if (HID::keyboard::IsKeyDown(HID::KEY::Z)) {
        p.Y -= moveFactor;
        t.Y -= moveFactor;
    }
    if (HID::keyboard::IsKeyDown(HID::KEY::D)) {
        p.X -= moveFactor;
        t.X -= moveFactor;
    }
    if (HID::keyboard::IsKeyDown(HID::KEY::Q)) {
        p.X += moveFactor;
        t.X += moveFactor;
    }
    if (HID::keyboard::IsKeyDown(HID::KEY::A)) {
        p.Z -= moveFactor;
        t.Z -= moveFactor;
    }
    if (HID::keyboard::IsKeyDown(HID::KEY::E)) {
        p.Z += moveFactor;
        t.Z += moveFactor;
    }

    if (HID::mouse::IsRightMouseKeyDown()) {
        auto result = HID::mouse::MouseMove(sdk::Window().getHWindow());

        if (result.first > 200) {
            t.X += 2.5f * deltaTime;
        } else if (result.first > 100) {
            t.X += 1.0f * deltaTime;
        } else if (result.first < -200) {
            t.X -= 2.5f * deltaTime;
        } else if (result.first < -100) {
            t.X -= 1.0f * deltaTime;
        }

        if (result.second > 50) {
            t.Y -= 2.5f * deltaTime;
        } else if (result.second < -50) {
            t.Y += 2.5f * deltaTime;
        }
    }

    camera.setPosition(p);
    camera.setTarget(t);
}

void CameraScene::setToCurrentScene()
{
    sdk::SceneManager::setCurrentScene(m_strIdentifier);
}