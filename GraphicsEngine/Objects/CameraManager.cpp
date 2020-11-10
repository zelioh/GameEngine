//
// Created by tangt on 03/11/2020.
//

#include "CameraManager.h"
#include "Camera.h"
#include "SceneManager.h"
#include "public/Core/Core_utils.h"

object::CameraManager * object::CameraManager::getInstance()
{
    static CameraManager * manager = nullptr;

    if (nullptr == manager)
    {
        manager = new CameraManager();
    }
    return manager;
}

object::Camera * object::CameraManager::createCamera(const std::string &levelIdentifier,
                                                     const std::string &cameraIdentifier,
                                                     const Math::Vector3F &position,
                                                     const Math::Vector3F &target,
                                                     const Math::Vector3F &upAxis)
{
    if (!SceneManager::getInstance()->isExisting(levelIdentifier))
    {
        return nullptr;
    }

    //
    // Search if cube already exist
    auto search = m_pool[levelIdentifier].find(cameraIdentifier);

    if (search != m_pool[levelIdentifier].end() && m_pool[levelIdentifier][cameraIdentifier] != nullptr) {
        WARNING_MESSAGE("Camera " + cameraIdentifier + " already exist");
        return m_pool[levelIdentifier][cameraIdentifier];
    }

    // Create cube instance
    m_pool[levelIdentifier][cameraIdentifier] = new Camera(levelIdentifier, cameraIdentifier, position, target, upAxis);
    return m_pool[levelIdentifier][cameraIdentifier];
}

object::Camera * object::CameraManager::createCameraAutoName(const std::string &levelIdentifier,
                                                             const Math::Vector3F &position,
                                                             const Math::Vector3F &target,
                                                             const Math::Vector3F &upAxis)
{
    if (!SceneManager::getInstance()->isExisting(levelIdentifier))
    {
        return nullptr;
    }
    const size_t size = m_pool[levelIdentifier].size();
    std::string identifier = "CAMERA_" + std::to_string(size);

    return createCamera(levelIdentifier, identifier, position, target, upAxis);
}

object::Camera * object::CameraManager::findCamera(const std::string &levelIdentifier, const std::string &cameraIdentifier)
{
    if (!SceneManager::getInstance()->isExisting(levelIdentifier))
    {
        return nullptr;
    }

    auto search = m_pool[levelIdentifier].find(cameraIdentifier);

    if (search != m_pool[levelIdentifier].end()) {
        return m_pool[levelIdentifier][cameraIdentifier];
    }
    ERROR_MESSAGE("Camera doesn't exist");
    ASSERT_ALWAYS();
    return nullptr;
}

bool object::CameraManager::deleteCamera(const std::string &levelIdentifier, const std::string &cameraIdentifier)
{
    if (m_pool.find(levelIdentifier) == m_pool.end() ||
        m_pool[levelIdentifier].find(cameraIdentifier) == m_pool[levelIdentifier].end()) {
        return false;
    }

    delete m_pool[levelIdentifier][cameraIdentifier];
    m_pool[levelIdentifier][cameraIdentifier] = nullptr;
    return true;
}

void object::CameraManager::release()
{
    for (auto & map : m_pool)
    {
        for (auto & camera : map.second)
        {
            delete camera.second;
            camera.second = nullptr;
        }
    }
}

void object::CameraManager::releaseScene(const std::string &levelIdentifier)
{
    for (auto & camera : m_pool[levelIdentifier])
    {
        delete camera.second;
        camera.second = nullptr;
    }
}