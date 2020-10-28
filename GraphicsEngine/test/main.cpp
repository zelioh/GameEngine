//
// Created by tangt on 26/10/2020.
//

#include <windows.h>
#include "Window.h"
#include "WindowParameters.h"
#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

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

#include <chrono>

void update(const graphics::Swapchain & swapchain, int imageIndex)
{
    static auto startTime = std::chrono::high_resolution_clock::now();

    auto currentTime = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

    //
    // Here ugly brut values do not do that !!!
    SUniformBufferObject ubo;

    //
    // TODO: use object Transform
    ubo.model = Math::Matrix4F(Math::Vector4F(1.f, 0.00004f, 0.f, 0.f),
                               Math::Vector4F(-0.00004f, 1.f, 0.f, 0.f),
                               Math::Vector4F(0.f, 0.f, 1.f, 0.f),
                               Math::Vector4F(0.f, 0.f, 0.f, 1.f));
    //
    // TODO: use camera look at
    ubo.view = Math::Matrix4F(Math::Vector4F(-0.7071f, -0.4082f, 0.57735f, 0.f),
                              Math::Vector4F(0.7071f, -0.4082f, 0.57735f, 0.f),
                              Math::Vector4F(0.f, 0.81649f, 0.57735f, 0.f),
                              Math::Vector4F(-0.f, -0.f, -3.4641f, 1.f));;
    //
    // TODO: use perspectif compute
    ubo.proj = Math::Matrix4F(Math::Vector4F(1.81066f, 0.f, 0.f, 0.f),
                              Math::Vector4F(0.f, -2.4142f, 0.f, 0.f),
                              Math::Vector4F(0.f, 0.f, -1.01010f, -1.f),
                              Math::Vector4F(0.f, 0.f, -0.10101010f, 0.f));;
    //ubo[1][1] *= -1;

    swapchain.updateUniformBuffer(imageIndex, ubo);
}

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

    object::CubeManager * manager = object::CubeManager::getInstance();
    object::Cube * cube = manager->createCube("TestCube",
                                              Math::Vector3F(0, 0, 0),
                                              Math::Vector3F(0.5f, 0.5f, 0.5f));

    // Do not do the following !!!
    swapchain.initializeVertexIndexBuffers(cube->getVertices(), cube->getIndices());

    //TODO: create vertex buffer inside of the object and then use it at draw call

    renderer.setUpdateCallback(update);
    while (window)
    {
        window.handleEvent();
        if (!window)
        {
            break;
        }
        if (!renderer.renderObject(swapchain, cube, pipeline))
        {
            logicalDevice.releaseCommandPool();
            logicalDevice.initializeCommandPool();
            swapchain.recreate(window);
            pipeline.release(logicalDevice);
            pipeline.initialize(logicalDevice, swapchain, shader);
        }
    }
    logicalDevice.getVkLogicalDevice().waitIdle();
    swapchain.releaseVertexIndexBuffers();
    pipeline.release(logicalDevice);
    swapchain.release();
    logicalDevice.release();
    instance.release();
    ///< TODO: destroy more think, see validation layer
    return 0;
}