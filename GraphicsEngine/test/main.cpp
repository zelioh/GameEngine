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
#include "TextureManager.h"
#include "Texture.h"
#include "Objects/SceneManager.h"
#include "Objects/Scene.h"
#include "Math_utils.h"
#include "Objects/Camera.h"
#include "Objects/CameraManager.h"
#include "Objects/Plane.h"
#include "Objects/PlaneManager.h"
#include "Objects/Model3D.h"
#include "Objects/Model3DManager.h"
#include "BoundingBox.h"
#include "BoundingSphere.h"

#include <chrono>
#include <thread>

int WINAPI WinMain(HINSTANCE currentInstance, HINSTANCE previousInstance, PSTR cmdLine, INT cmdCount)
{
    graphics::WindowParameters parameters;

    parameters.m_bHasTitleBar = true;
    parameters.m_bHasSysMenu = true;
    parameters.m_bCanResize = false;
    parameters.m_bIsFullScreen = false;
    parameters.m_iTop = 0;
    parameters.m_iLeft = 0;
    parameters.m_iWidth = 800;
    parameters.m_iHeight = 600;
    parameters.m_bIsBorderLess = true;
    parameters.m_bCanMaximaze = true;
    parameters.m_bCanMinize = true;
    parameters.m_strName = "Test graphic engine";

    graphics::Window window(currentInstance, parameters);

    graphics::InstanceParameter instanceParam;

    instanceParam.setApplicationName("Test graphic engine");
    instanceParam.setProjectVersions(1, 0, 0);

    graphics::Instance * instance = graphics::Instance::getInstance();

    instance->initialize(instanceParam, window);

    graphics::PhysicalDevice * physicalDevice = graphics::PhysicalDevice::getInstance();
    graphics::LogicalDevice * logicalDevice = graphics::LogicalDevice::getInstance();
    graphics::Swapchain swapchain(*logicalDevice, window);
    graphics::Shader shader("../shaders/defaultVert.spv", "../shaders/defaultFrag.spv");
    graphics::Pipeline pipeline(*logicalDevice, swapchain, shader);
    graphics::Renderer renderer(swapchain);

    const std::string myLevelIdentifier = "MyLevel";

    object::Scene * myLevel = object::SceneManager::getInstance()->createScene(myLevelIdentifier);

    if (!object::SceneManager::getInstance()->setCurrentScene(myLevelIdentifier))
    {
        return 84;
    }

    object::CubeManager * manager = object::CubeManager::getInstance();
    object::Cube * cube1 = manager->createCube(*logicalDevice,
                                              myLevelIdentifier,
                                              "TestCube",
                                              Math::Vector3F(-5.f, 0.f, 0.f),
                                              Math::Vector3F(1.f, 1.f, 1.f),
                                              Math::Vector3F(1.f, 1.f, 1.f)
                                              //object::SRotation{90.f, Math::Vector3F(0.f, 0.f, 1.f)}
                                              );

    object::Cube * cube2 = manager->createCube(*logicalDevice,
                                              myLevelIdentifier,
                                              "TestCube2",
                                              Math::Vector3F(5.f, 0.f, 0.f),
                                              Math::Vector3F(1.f, 1.f, 1.f),
                                              Math::Vector3F(1.f, 1.f, 1.f)
                                              //object::SRotation{90.f, Math::Vector3F(0.f, 0.f, 1.f)}
                                              );

//    object::Cube * cube3 = manager->createCube(*logicalDevice,
//                                              myLevelIdentifier,
//                                              "TestCube3",
//                                              Math::Vector3F(2.f, -1.f, 0.f),
//                                              Math::Vector3F(0.f, 1.5f, 0.f),
//                                              Math::Vector3F(1.5f, 1.5f, 1.5f),
//                                              object::SRotation{180.f, Math::Vector3F(0.f, 0.f, 1.f)});
//
//    object::Cube * cube4 = manager->createCube(*logicalDevice,
//                                              myLevelIdentifier,
//                                              "TestCube4",
//                                              Math::Vector3F(0.f, 2.f, 0.f),
//                                              Math::Vector3F(0.5f, 0.5f, 0.5f),
//                                              Math::Vector3F(0.5f, 0.5f, 0.5f),
//                                              object::SRotation{90.f, Math::Vector3F(0.f, 0.f, 1.f)});
//
//    object::Cube * cube5 = manager->createCube(*logicalDevice,
//                                              myLevelIdentifier,
//                                              "TestCube5",
//                                              Math::Vector3F(-1.f, 0.5f, 0.f),
//                                              Math::Vector3F(0.f, 0.f, 0.5f),
//                                              Math::Vector3F(0.5f, 0.5f, 0.5f),
//                                              object::SRotation{0.f, Math::Vector3F(0.f, 0.f, 1.f)});

    graphics::TextureManager * textureManager = graphics::TextureManager::getInstance();
    graphics::Texture * boxTexture = textureManager->createTexture(swapchain, "../assets/box.png", "Box");
    graphics::Texture * phoenixTexture = textureManager->createTexture(swapchain, "../assets/texture.jpg", "Phoenix");

    cube1->setTexture(boxTexture);
    //cube3->setTexture(phoenixTexture);
    //cube4->setTexture(phoenixTexture);
    //cube5->setTexture(phoenixTexture);

    object::PlaneManager * planeManager = object::PlaneManager::getInstance();

//    object::Plane * plane = planeManager->createPlane(*logicalDevice,
//                                                      myLevelIdentifier,
//                                                      "Cool_plane",
//                                                      Math::Vector3F(0.f, -10.f, 0.f),
//                                                      Math::Vector3F(1.f, 0.2f, 0.4f),
//                                                      Math::Vector3F(5.f, 5.f, 5.f),
//                                                      object::SRotation{270.f, Math::Vector3F(1.f, 0.f, 0.f)});

    object::Camera * camera = object::CameraManager::getInstance()->createCamera(myLevelIdentifier,
                                                                                 "Camera_one",
                                                                                 Math::Vector3F(0.f, 3.f, 2.f),
                                                                                 Math::Vector3F(0.f, 0.f, 0.f),
                                                                                 Math::Vector3F(0.f, 0.f, 1.f));

    myLevel->setCurrentCamera(camera);

    auto startTime = std::chrono::high_resolution_clock::now();

    vk::Extent2D extent = swapchain.getVkSwapchainExtent();
    float width = static_cast<float>(extent.width);
    float height = static_cast<float>(extent.height);

    renderer.setProjectionMatrix(Math::utils::perspective(90.0f, width / height, 0.01f, 25.f));


//    object::Model3DManager * modelsManager = object::Model3DManager::getInstance();
//
//    object::Model3D * viking_room = modelsManager->createModel3D(*logicalDevice,
//                                                                 myLevelIdentifier,
//                                                                 "Viking_room",
//                                                                 "../models/viking_room.obj",
//                                                                 Math::Vector3F(0.f, 0.f, 0.f),
//                                                                 Math::Vector3F(1.f, 1.f, 1.f),
//                                                                 Math::Vector3F(2.f, 2.f, 2.f));

    graphics::Texture * viking_room_texture = textureManager->createTexture(swapchain, "../assets/viking_room.png", "Viking_room");

//    viking_room->setTexture(viking_room_texture);
//    viking_room->setRotate(object::SRotation{90.f, Math::Vector3F(0.f, 0.f, 1.f)});

//    PhysicsObject * box1 = new PhysicsObject(new BoundingBox(Math::Vector3F(0.0f, 0.0f, 0.0f), Math::Vector3F(1.0f, 1.0f, 1.0f)),
//                                       Math::Vector3F(0.1f, 0.0f, 0.0f));
//    PhysicsObject * box2 = new PhysicsObject(new BoundingBox(Math::Vector3F(0.0f, 0.0f, 0.0f), Math::Vector3F(1.0f, 1.0f, 1.0f)),
//                                       Math::Vector3F(-0.1f, 0.0f, 0.0f));

    PhysicsObject * box1 = new PhysicsObject(new BoundingSphere(Vector3F(0.0f, 0.0f, 0.0f), 0.5f), Vector3F(0.1f, 0.0f, 0.0f));

    PhysicsObject * box2 = new PhysicsObject(new BoundingSphere(Vector3F(10.0f, 0.0f, 0.0f), 0.5f), Vector3F(-0.1f, 0.0f, 0.0f));


    box1->SetPosition(cube1->getPosition());
    box2->SetPosition(cube2->getPosition());

    cube1->setPhysicsObject(box1);
    cube2->setPhysicsObject(box2);

    myLevel->getPhysicsEngine().AddPhysicsObject(cube1->getPhysicsObject());
    myLevel->getPhysicsEngine().AddPhysicsObject(cube2->getPhysicsObject());

    while (window)
    {
        auto currentTime = std::chrono::high_resolution_clock::now();
        float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

        window.handleEvent();
        if (!window)
        {
            break;
        }
        //cube1->setRotate(object::SRotation{90.f * time, cube1->getRotate().axis});
        //cube2->setRotate(object::SRotation{90.f * -time, cube2->getRotate().axis});
//        cube3->setRotate(object::SRotation{90.f * time, Math::Vector3F(1.f, 0.f, 0.f)});
//        Math::Vector3F p = camera->getPosition();
//
//        float camZ = sin(time) + 2.0f;
//
//        p.Z = camZ;
//
//        camera->setPosition(p);

        object::SceneManager::getInstance()->getCurrentScene()->getPhysicsEngine().CollisionHandler();
        object::SceneManager::getInstance()->getCurrentScene()->getPhysicsEngine().Update(0.05f);

        cube1->setPosition(cube1->getPhysicsObject()->GetPosition());
        cube2->setPosition(cube2->getPhysicsObject()->GetPosition());

        //Sleep(100);

        if (!renderer.render(swapchain, pipeline))
        {
            logicalDevice->releaseCommandPool();
            logicalDevice->initializeCommandPool();
            swapchain.recreate(window);
            pipeline.release(*logicalDevice);
            pipeline.initialize(*logicalDevice, swapchain, shader);
        }
    }
    logicalDevice->getVkLogicalDevice().waitIdle();
    manager->release(*logicalDevice);
    textureManager->release(*logicalDevice);
    object::SceneManager::getInstance()->release();
    pipeline.release(*logicalDevice);
    swapchain.release();
    logicalDevice->release();
    instance->release();
    return 0;
}