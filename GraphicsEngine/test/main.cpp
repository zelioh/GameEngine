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

#include <chrono>

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

    graphics::Instance instance(instanceParam);

    instance.initialize(window);

    graphics::PhysicalDevice physicalDevice(instance);
    graphics::LogicalDevice logicalDevice(physicalDevice);
    graphics::Swapchain swapchain(logicalDevice, window);
    graphics::Shader shader("../shaders/defaultVert.spv", "../shaders/defaultFrag.spv");
    graphics::Pipeline pipeline(logicalDevice, swapchain, shader);
    graphics::Renderer renderer(swapchain);

    const std::string myLevelIdentifier = "MyLevel";

    object::Scene * myLevel = object::SceneManager::getInstance()->createScene(myLevelIdentifier);

    if (!object::SceneManager::getInstance()->setCurrentScene(myLevelIdentifier))
    {
        return 84;
    }

    object::CubeManager * manager = object::CubeManager::getInstance();
    object::Cube * cube1 = manager->createCube(logicalDevice,
                                              myLevelIdentifier,
                                              "TestCube",
                                              Math::Vector3F(0.f, 0.f, 0.f),
                                              Math::Vector3F(0.5f, 0.5f, 0.5f),
                                              Math::Vector3F(1.f, 1.f, 1.f),
                                              object::SRotation{90.f, Math::Vector3F(0.f, 0.f, 1.f)});

    object::Cube * cube2 = manager->createCube(logicalDevice,
                                              myLevelIdentifier,
                                              "TestCube2",
                                              Math::Vector3F(1.f, 0.5f, 0.f),
                                              Math::Vector3F(1.f, 1.f, 1.f),
                                              Math::Vector3F(0.5f, 0.5f, 0.5f),
                                              object::SRotation{90.f, Math::Vector3F(0.f, 0.f, 1.f)});

    object::Cube * cube3 = manager->createCube(logicalDevice,
                                              myLevelIdentifier,
                                              "TestCube3",
                                              Math::Vector3F(2.f, -1.f, 0.f),
                                              Math::Vector3F(0.f, 1.5f, 0.f),
                                              Math::Vector3F(1.5f, 1.5f, 1.5f),
                                              object::SRotation{180.f, Math::Vector3F(0.f, 0.f, 1.f)});

    object::Cube * cube4 = manager->createCube(logicalDevice,
                                              myLevelIdentifier,
                                              "TestCube4",
                                              Math::Vector3F(0.f, 2.f, 0.f),
                                              Math::Vector3F(0.5f, 0.5f, 0.5f),
                                              Math::Vector3F(0.5f, 0.5f, 0.5f),
                                              object::SRotation{90.f, Math::Vector3F(0.f, 0.f, 1.f)});

    object::Cube * cube5 = manager->createCube(logicalDevice,
                                              myLevelIdentifier,
                                              "TestCube5",
                                              Math::Vector3F(-1.f, 0.5f, 0.f),
                                              Math::Vector3F(0.f, 0.f, 0.5f),
                                              Math::Vector3F(0.5f, 0.5f, 0.5f),
                                              object::SRotation{0.f, Math::Vector3F(0.f, 0.f, 1.f)});

    graphics::TextureManager * textureManager = graphics::TextureManager::getInstance();
    graphics::Texture * boxTexture = textureManager->createTexture(swapchain, "../assets/box.png", "Box");
    graphics::Texture * phoenixTexture = textureManager->createTexture(swapchain, "../assets/texture.jpg", "Phoenix");

    cube1->setTexture(boxTexture);
    cube3->setTexture(phoenixTexture);
    cube4->setTexture(phoenixTexture);
    cube5->setTexture(phoenixTexture);

    object::PlaneManager * planeManager = object::PlaneManager::getInstance();

    object::Plane * plane = planeManager->createPlane(logicalDevice,
                                                      myLevelIdentifier,
                                                      "Cool_plane",
                                                      Math::Vector3F(0.f, 0.f, -2.f),
                                                      Math::Vector3F(1.f, 0.2f, 0.4f),
                                                      Math::Vector3F(3.f, 3.f, 3.f));

    object::Camera * camera = object::CameraManager::getInstance()->createCamera(myLevelIdentifier,
                                                                                 "Camera_one",
                                                                                 Math::Vector3F(0.f, 3.f, -2.f),
                                                                                 Math::Vector3F(0.f, 0.f, 0.f),
                                                                                 Math::Vector3F(0.f, 0.f, 1.f));

    myLevel->setCurrentCamera(camera);

    auto startTime = std::chrono::high_resolution_clock::now();

    vk::Extent2D extent = swapchain.getVkSwapchainExtent();
    float width = static_cast<float>(extent.width);
    float height = static_cast<float>(extent.height);

    renderer.setProjectionMatrix(Math::utils::perspective(90.0f, width / height, 0.01f, 25.f));

    while (window)
    {
        auto currentTime = std::chrono::high_resolution_clock::now();
        float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

        window.handleEvent();
        if (!window)
        {
            break;
        }
        cube1->setRotate(object::SRotation{90.f * time, cube1->getRotate().axis});
        cube2->setRotate(object::SRotation{90.f * -time, cube2->getRotate().axis});
        cube3->setRotate(object::SRotation{90.f * time, Math::Vector3F(1.f, 0.f, 0.f)});
        Math::Vector3F p = camera->getPosition();

        float camZ = sin(time) + 2.0f;

        p.Z = camZ;

        camera->setPosition(p);

        if (!renderer.render(swapchain, pipeline))
        {
            logicalDevice.releaseCommandPool();
            logicalDevice.initializeCommandPool();
            swapchain.recreate(window);
            pipeline.release(logicalDevice);
            pipeline.initialize(logicalDevice, swapchain, shader);
        }
    }
    logicalDevice.getVkLogicalDevice().waitIdle();
    manager->release(logicalDevice);
    textureManager->release(logicalDevice);
    object::SceneManager::getInstance()->release();
    pipeline.release(logicalDevice);
    swapchain.release();
    logicalDevice.release();
    instance.release();
    return 0;
}