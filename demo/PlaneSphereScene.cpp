//
// Created by FiercePC on 15/11/2020.
//

#include "PlaneSphereScene.h"
#include "SDK/SceneManager.h"
#include "SDK/Scene.h"
#include "SDK/PlaneManager.h"
#include "SDK/Plane.h"
#include "SDK/CubeManager.h"
#include "SDK/Cube.h"
#include "BoundingSphere.h"
#include "BoundingSphere.h"
#include "Plane.h"
#include "SDK/CameraManager.h"
#include "SDK/Camera.h"

PlaneSphereScene::PlaneSphereScene():
m_strIdentifier("PlaneSphereScene")
{}

void PlaneSphereScene::postInitialize()
{
    sdk::Scene scene = sdk::SceneManager::createScene(m_strIdentifier);

    sdk::Plane plane = sdk::PlaneManager::createPlane(
            m_strIdentifier,
            "Cool_plane",
            Math::Vector3F(0.f, 0.f, -5.f),
            Math::Vector3F(1.f, 0.2f, 0.4f),
            Math::Vector3F(5.f, 5.f, 5.f));

    sdk::Camera camera = sdk::CameraManager::createCamera(m_strIdentifier,
                                                          "Camera_one",
                                                          Math::Vector3F(0.f, 5.f, -2.f),
                                                          Math::Vector3F(0.f, 0.f, 0.f),
                                                          Math::Vector3F(0.f, 0.f, 1.f));

    sdk::Cube cube = sdk::CubeManager::createCube(
            m_strIdentifier,
            "Cube_one",
            Math::Vector3F(0.f, 0.f, 0.f),
            Math::Vector3F(1.f, 0.f, 0.f));

    scene.setCurrentCamera(camera);

    auto * box1 = new PhysicsObject(new BoundingSphere(Vector3F(0.0f, 0.0f, 0.0f), 0.5f), Vector3F(0.f, 0.0f, -1.0f));
    auto * box2 = new PhysicsObject(new Plane(plane.getPosition(), 20.f), Vector3F(0.f, 0.0f, 0.0f));
    cube.setPhysicalObject(box1);
    plane.setPhysicalObject(box2);
}

void PlaneSphereScene::setToCurrentScene()
{
    sdk::SceneManager::setCurrentScene(m_strIdentifier);
}

