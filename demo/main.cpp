//
// Created by FiercePC on 11/11/2020.
//

#include "SDK/Application.h"
#include "SDK/Cube.h"
#include "SDK/SceneManager.h"
#include "SDK/Scene.h"
#include "SDK/CubeManager.h"
#include "SDK/Plane.h"
#include "SDK/PlaneManager.h"
#include "SDK/Model3D.h"
#include "SDK/Model3DManager.h"
#include "SDK/Texture.h"
#include "SDK/TextureManager.h"
#include "SDK/CameraManager.h"
#include "SDK/Camera.h"
#include "PhysicsObject.h"
#include "SDK/GameObject.h"
#include "SDK/LightManager.h"
#include "SDK/Light.h"
#include "SDK/Window.h"
#include "Math_utils.h"
#include "Event.h"
#include "GraphicsEngine/WindowParameters.h"
#include "GraphicsEngine/InstanceParameter.h"
#include "BoundingBox.h"
#include "BoundingSphere.h"

void preInitialize(graphics::InstanceParameter &instanceParameter, graphics::WindowParameters & windowParameters)
{
    windowParameters.m_bHasTitleBar = true;
    windowParameters.m_bHasSysMenu = true;
    windowParameters.m_bCanResize = false;
    windowParameters.m_bIsFullScreen = false;
    windowParameters.m_iTop = 0;
    windowParameters.m_iLeft = 0;
    windowParameters.m_iWidth = 800;
    windowParameters.m_iHeight = 600;
    windowParameters.m_bIsBorderLess = true;
    windowParameters.m_bCanMaximaze = true;
    windowParameters.m_bCanMinize = true;
    windowParameters.m_bClipCursorToWindow = true;
    windowParameters.m_strName = "Test graphic engine";

    instanceParameter.setApplicationName("Test graphic engine");
    instanceParameter.setProjectVersions(1, 0, 0);
}

void postInitialize()
{
    const std::string myLevelIdentifier = "MyLevel";

    sdk::Scene myLevel = sdk::SceneManager::createScene(myLevelIdentifier);

    sdk::SceneManager::setCurrentScene(myLevelIdentifier);

    sdk::Cube cube1 = sdk::CubeManager::createCube(
            myLevelIdentifier,
            "TestCube",
            Math::Vector3F(-5.f, 0.f, 0.f),
            Math::Vector3F(1.f, 1.f, 1.f),
            Math::Vector3F(1.f, 1.f, 1.f),
            Math::SRotation{0.f, Math::Vector3F(0.f, 0.f, 1.f)}
    );


    sdk::Cube cube2 = sdk::CubeManager::createCube(
            myLevelIdentifier,
            "TestCube2",
            Math::Vector3F(5.f, 0.f, 0.f),
            Math::Vector3F(1.f, 1.f, 1.f),
            Math::Vector3F(1.f, 1.f, 1.f),
            Math::SRotation{0.f, Math::Vector3F(0.f, 0.f, 1.f)}
    );

    sdk::Cube cube3 = sdk::CubeManager::createCube(
            myLevelIdentifier,
            "TestCube3",
            Math::Vector3F(2.f, -1.f, 0.f),
            Math::Vector3F(0.f, 1.5f, 0.f),
            Math::Vector3F(1.5f, 1.5f, 1.5f),
            Math::SRotation{90.f, Math::Vector3F(0.f, 0.f, 1.f)});

    sdk::Cube cube4 = sdk::CubeManager::createCube(
            myLevelIdentifier,
            "TestCube4",
            Math::Vector3F(0.f, 2.f, 0.f),
            Math::Vector3F(0.5f, 0.5f, 0.5f),
            Math::Vector3F(0.5f, 0.5f, 0.5f),
            Math::SRotation{90.f, Math::Vector3F(0.f, 0.f, 1.f)});

    sdk::Cube cube5 = sdk::CubeManager::createCube(
            myLevelIdentifier,
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

    sdk::Plane plane = sdk::PlaneManager::createPlane(
            myLevelIdentifier,
            "Cool_plane",
            Math::Vector3F(0.f, -10.f, 0.f),
            Math::Vector3F(1.f, 0.2f, 0.4f),
            Math::Vector3F(5.f, 5.f, 5.f),
            Math::SRotation{270.f, Math::Vector3F(1.f, 0.f, 0.f)});

    sdk::Camera camera = sdk::CameraManager::createCamera(myLevelIdentifier,
                                                                                 "Camera_one",
                                                                                 Math::Vector3F(0.f, 3.f, 2.f),
                                                                                 Math::Vector3F(0.f, 0.f, 0.f),
                                                                                 Math::Vector3F(0.f, 0.f, 1.f));

    sdk::Camera camera2 = sdk::CameraManager::createCamera(myLevelIdentifier,
                                                                                  "Camera_two",
                                                                                  Math::Vector3F(0.f, -3.f, 2.f),
                                                                                  Math::Vector3F(0.f, 0.f, 0.f),
                                                                                  Math::Vector3F(0.f, 0.f, 1.f));

    myLevel.setCurrentCamera(camera);

    sdk::Model3D viking_room = sdk::Model3DManager::createModel3D(
            myLevelIdentifier,
            "Viking_room",
            "../models/viking_room.obj",
            Math::Vector3F(0.f, 0.f, 0.f),
            Math::Vector3F(1.f, 1.f, 1.f),
            Math::Vector3F(2.f, 2.f, 2.f));

    sdk::Texture viking_room_texture = sdk::TextureManager::createTexture("../assets/viking_room.png", "Viking_room");

    viking_room.setTexture(viking_room_texture);
    viking_room.setRotate(Math::SRotation{90.f, Math::Vector3F(0.f, 0.f, 1.f)});

     PhysicsObject * box1 = new PhysicsObject(new BoundingSphere(Vector3F(0.0f, 0.0f, 0.0f), 0.5f), Vector3F(1.f, 0.0f, 0.0f));
    PhysicsObject * box2 = new PhysicsObject(new BoundingSphere(Vector3F(10.0f, 0.0f, 0.0f), 0.5f), Vector3F(-1.f, 0.0f, 0.0f));

    cube1.setPhysicalObject(box1);
    cube2.setPhysicalObject(box2);

    sdk::LightManager::createLight(myLevelIdentifier,
                                                     "ligth_000",
                                                     Math::Vector3F(0.f, 0.f, 1.f),
                                                     0.2f,
                                                     0.3f,
                                                     Math::Vector3F(1.f, 1.f, 1.f));

}

void preUpdate(float deltaTime, Matrix4F & projectionMatrix)
{
    auto window = sdk::Window();

    projectionMatrix = Math::utils::perspective(90.0f,
                                                static_cast<float>(window.getWidth()) / static_cast<float>(window.getHeight()),
                                                0.01f, 25.f);

    sdk::Cube cube3 = sdk::CubeManager::findCube("MyLevel", "TestCube3");
    sdk::Cube cube4 = sdk::CubeManager::findCube("MyLevel", "TestCube4");

    cube3.setRotate(Math::SRotation{cube3.getRotation().angle + 90.f * deltaTime, Math::Vector3F(1.f, 0.f, 0.f)});

    if (HID::keyboard::IsKeyDown(HID::KEY::N))
    {
        sdk::SceneManager::getCurrentScene().setCurrentCamera("Camera_one");
    }

    if (HID::keyboard::IsKeyDown(HID::KEY::B))
    {
        sdk::SceneManager::getCurrentScene().setCurrentCamera("Camera_two");
    }

    sdk::Camera camera = sdk::SceneManager::getCurrentScene().getCurrentCamera();

    Math::Vector3F p = camera.getPosition();
    Math::Vector3F t = camera.getTarget();

    if (HID::keyboard::IsKeyDown(HID::KEY::ESCAPE)) {
        window.close();
        return;
    }

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
        auto result = HID::mouse::MouseMove(window.getHWindow());

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

    if (HID::mouse::IsLeftMouseKeyDown()) {
        static float currentAngle = 90.f;

        currentAngle += 90.f * deltaTime;

        cube4.setRotate(Math::SRotation{currentAngle, cube4.getRotation().axis});
    }
}

int main()
{
    sdk::Application application;

    application.setPreUpdateFunction(preUpdate);
    application.setPostInitializeCallback(postInitialize);
    application.setPreInitializeCallback(preInitialize);

    application.run();

    return 0;
}