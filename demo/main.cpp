//
// Created by FiercePC on 11/11/2020.
//

#include "SDK/Application.h"
#include "SDK/Window.h"
#include "Math_utils.h"
#include "Event.h"
#include "AudioEngine.h"
#include "CameraScene.h"
#include "LightScene.h"
#include "CubeScene.h"
#include "Matrix4F.h"
#include "CollisionSphereScene.h"
#include "PlaneSphereScene.h"

CameraScene g_cameraScene;
LightScene g_lightScene;
CubeScene g_cubeScene;
CollisionSphereScene g_collisionSphereScene;
PlaneSphereScene g_planeSphereScene;

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
    g_lightScene.postInitialize();
    g_cubeScene.postInitialize();
    g_cameraScene.postInitialize();
    g_collisionSphereScene.postInitialize();
    g_planeSphereScene.postInitialize();

    //
    // Doesn't work
//    if (AudioEngine::PlayWavMusic("music.wav") == FALSE)
//    {
//        ASSERT_ALWAYS();
//    }
    g_cameraScene.setToCurrentScene();
}

void preUpdate(float deltaTime, Math::Matrix4F & projectionMatrix)
{
    auto window = sdk::Window();

    projectionMatrix = Math::utils::perspective(90.0f,
                                                static_cast<float>(window.getWidth()) / static_cast<float>(window.getHeight()),
                                                0.01f, 25.f);

    if (HID::keyboard::IsKeyDown(HID::KEY::ESCAPE)) {
        window.close();
        return;
    }

    static int sceneId = 0;

    if (HID::keyboard::IsKeyDown(HID::KEY::U))
    {
        sceneId = 0;
        g_cameraScene.setToCurrentScene();
    } else if (HID::keyboard::IsKeyDown(HID::KEY::I)) {
        sceneId = 1;
        g_lightScene.setToCurrentScene();
    } else if (HID::keyboard::IsKeyDown(HID::KEY::O)) {
        sceneId = 2;
        g_cubeScene.setToCurrentScene();
    } else if (HID::keyboard::IsKeyDown(HID::KEY::P)) {
        sceneId = 3;
        g_collisionSphereScene.setToCurrentScene();
    } else if (HID::keyboard::IsKeyDown(HID::KEY::M)) {
        sceneId = 4;
        g_planeSphereScene.setToCurrentScene();
    }

    switch (sceneId) {
        case 0:
            g_cameraScene.preUpdate(deltaTime);
            break;
        case 1:
            g_lightScene.preUpdate(deltaTime);
            break;
        case 2:
            g_cubeScene.preUpdate(deltaTime);
            break;
        default:
            break;
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