//
// Created by tangt on 26/10/2020.
//

#include <windows.h>
#include "Window.h"
#include "WindowParameters.h"

#include "Instance.h"
#include "InstanceParameter.h"
#include "LogicalDevice.h"
#include "PhysicalDevice.h"
#include "Swapchain.h"
#include "Renderer.h"
#include "Pipeline.h"
#include "Shader.h"
#include "Objects/Cube.h"
#include "Objects/CubeManager.h"
#include "SUniformBufferObject.h"
#include "public/GraphicsEngine/TextureManager.h"
#include "public/GraphicsEngine/Texture.h"
#include "Objects/SceneManager.h"
#include "Math_utils.h"
#include "Objects/Camera.h"
#include "Objects/CameraManager.h"
#include "Objects/Plane.h"
#include "Objects/PlaneManager.h"
#include "Objects/Model3D.h"
#include "Objects/Model3DManager.h"
#include "BoundingSphere.h"
#include "Objects/LightManager.h"
#include "Objects/Light.h"
#include "Event.h"
#include "WindowEvent.h"
#include "public/Core/Core_utils.h"
#include "public/Core/Application.h"

#include <chrono>

float g_deltaTime = 0.0f;

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

    object::Scene * myLevel = object::SceneManager::getInstance()->createScene(myLevelIdentifier);

    object::SceneManager::getInstance()->setCurrentScene(myLevelIdentifier);

    object::CubeManager * manager = object::CubeManager::getInstance();
    object::Cube * cube1 = manager->createCube(
            myLevelIdentifier,
            "TestCube",
            Math::Vector3F(-5.f, 0.f, 0.f),
            Math::Vector3F(1.f, 1.f, 1.f),
            Math::Vector3F(1.f, 1.f, 1.f),
            Math::SRotation{0.f, Math::Vector3F(0.f, 0.f, 1.f)}
    );


    object::Cube * cube2 = manager->createCube(
            myLevelIdentifier,
            "TestCube2",
            Math::Vector3F(5.f, 0.f, 0.f),
            Math::Vector3F(1.f, 1.f, 1.f),
            Math::Vector3F(1.f, 1.f, 1.f),
            Math::SRotation{0.f, Math::Vector3F(0.f, 0.f, 1.f)}
    );

    object::Cube * cube3 = manager->createCube(
            myLevelIdentifier,
            "TestCube3",
            Math::Vector3F(2.f, -1.f, 0.f),
            Math::Vector3F(0.f, 1.5f, 0.f),
            Math::Vector3F(1.5f, 1.5f, 1.5f),
            Math::SRotation{180.f, Math::Vector3F(0.f, 0.f, 1.f)});

    object::Cube * cube4 = manager->createCube(
            myLevelIdentifier,
            "TestCube4",
            Math::Vector3F(0.f, 2.f, 0.f),
            Math::Vector3F(0.5f, 0.5f, 0.5f),
            Math::Vector3F(0.5f, 0.5f, 0.5f),
            Math::SRotation{90.f, Math::Vector3F(0.f, 0.f, 1.f)});

    object::Cube * cube5 = manager->createCube(
            myLevelIdentifier,
            "TestCube5",
            Math::Vector3F(-1.f, 0.5f, 0.f),
            Math::Vector3F(0.f, 0.f, 0.5f),
            Math::Vector3F(0.5f, 0.5f, 0.5f),
            Math::SRotation{0.f, Math::Vector3F(0.f, 0.f, 1.f)});

    graphics::TextureManager * textureManager = graphics::TextureManager::getInstance();
    graphics::Texture * boxTexture = textureManager->createTexture("../assets/box.png", "Box");
    graphics::Texture * phoenixTexture = textureManager->createTexture("../assets/texture.jpg", "Phoenix");

    cube1->setTexture(boxTexture);
    cube3->setTexture(phoenixTexture);
    cube4->setTexture(phoenixTexture);
    cube5->setTexture(phoenixTexture);

    object::PlaneManager * planeManager = object::PlaneManager::getInstance();

    object::Plane * plane = planeManager->createPlane(
            myLevelIdentifier,
            "Cool_plane",
            Math::Vector3F(0.f, -10.f, 0.f),
            Math::Vector3F(1.f, 0.2f, 0.4f),
            Math::Vector3F(5.f, 5.f, 5.f),
            Math::SRotation{270.f, Math::Vector3F(1.f, 0.f, 0.f)});

    object::Camera * camera = object::CameraManager::getInstance()->createCamera(myLevelIdentifier,
                                                                                 "Camera_one",
                                                                                 Math::Vector3F(0.f, 3.f, 2.f),
                                                                                 Math::Vector3F(0.f, 0.f, 0.f),
                                                                                 Math::Vector3F(0.f, 0.f, 1.f));

    myLevel->setCurrentCamera(camera);
    object::Model3DManager * modelsManager = object::Model3DManager::getInstance();

    object::Model3D * viking_room = modelsManager->createModel3D(
            myLevelIdentifier,
            "Viking_room",
            "../models/viking_room.obj",
            Math::Vector3F(0.f, 0.f, 0.f),
            Math::Vector3F(1.f, 1.f, 1.f),
            Math::Vector3F(2.f, 2.f, 2.f));

    graphics::Texture * viking_room_texture = textureManager->createTexture("../assets/viking_room.png", "Viking_room");

    viking_room->setTexture(viking_room_texture);
    viking_room->setRotate(Math::SRotation{90.f, Math::Vector3F(0.f, 0.f, 1.f)});

    PhysicsObject * box1 = new PhysicsObject(new BoundingSphere(Vector3F(0.0f, 0.0f, 0.0f), 0.5f), Vector3F(0.1f, 0.0f, 0.0f));

    PhysicsObject * box2 = new PhysicsObject(new BoundingSphere(Vector3F(10.0f, 0.0f, 0.0f), 0.5f), Vector3F(-0.1f, 0.0f, 0.0f));


    box1->SetPosition(cube1->getPosition());
    box2->SetPosition(cube2->getPosition());

    cube1->setPhysicsObject(box1);
    cube2->setPhysicsObject(box2);

    myLevel->getPhysicsEngine().AddPhysicsObject(cube1->getPhysicsObject());
    myLevel->getPhysicsEngine().AddPhysicsObject(cube2->getPhysicsObject());
    object::LightManager::getInstance()->createLight(myLevelIdentifier,
                                                     "ligth_000",
                                                     Math::Vector3F(0.f, 0.f, 1.f),
                                                     0.2f,
                                                     0.3f,
                                                     Math::Vector3F(1.f, 1.f, 1.f));

}

void preUpdate(float deltaTime, Matrix4F & projectionMatrix, int width, int height)
{
    projectionMatrix = Math::utils::perspective(90.0f,
                                                static_cast<float>(width) / static_cast<float>(height),
                                                0.01f, 25.f);

    object::Cube * cube3 = object::CubeManager::getInstance()->findCube("MyLevel", "TestCube3");
    object::Cube * cube4 = object::CubeManager::getInstance()->findCube("MyLevel", "TestCube4");

    cube3->setRotate(Math::SRotation{90.f * deltaTime, Math::Vector3F(1.f, 0.f, 0.f)});

    object::Camera * camera = object::SceneManager::getInstance()->getCurrentScene()->getCurrentCamera();

    Math::Vector3F p = camera->getPosition();
    Math::Vector3F t = camera->getTarget();

    //
    // TODO: singtone window
//    if (HID::keyboard::IsKeyDown(HID::KEY::ESCAPE)) {
//        window.close();
//        return;
//    }

    float moveFactor = 2.5f * g_deltaTime;

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

//    if (HID::mouse::IsRightMouseKeyDown()) {
//        auto result = HID::mouse::MouseMove(window.getHWindow());
//
//        if (result.first > 200) {
//            t.X += 2.5f * deltaTime;
//        } else if (result.first > 100) {
//            t.X += 1.0f * deltaTime;
//        } else if (result.first < -200) {
//            t.X -= 2.5f * deltaTime;
//        } else if (result.first < -100) {
//            t.X -= 1.0f * deltaTime;
//        }
//
//        if (result.second > 50) {
//            t.Y -= 2.5f * deltaTime;
//        } else if (result.second < -50) {
//            t.Y += 2.5f * deltaTime;
//        }
//    }

    camera->setPosition(p);
    camera->setTarget(t);

    if (HID::mouse::IsLeftMouseKeyDown()) {
        static float currentAngle = 90.f;

        currentAngle += 90.f * deltaTime;

        cube4->setRotate(Math::SRotation{currentAngle, cube4->getRotate().axis});
    }
}

int WINAPI WinMain(HINSTANCE currentInstance, HINSTANCE previousInstance, PSTR cmdLine, INT cmdCount)
{
    core::Application application;

    application.setPreInitializeCallback(preInitialize);
    application.setPostInitializeCallback(postInitialize);
    application.setPreUpdateFunction(preUpdate);

    application.run();
    return 0;
}