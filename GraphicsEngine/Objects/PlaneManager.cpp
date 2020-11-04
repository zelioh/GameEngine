//
// Created by tangt on 03/11/2020.
//

#include "PlaneManager.h"
#include "Plane.h"
#include "SceneManager.h"

/*static*/ object::PlaneManager * object::PlaneManager::getInstance()
{
    static PlaneManager * manager = nullptr;

    if (nullptr == manager)
    {
        manager = new PlaneManager();
    }
    return manager;
}

object::Plane * object::PlaneManager::createPlane(const graphics::LogicalDevice & logicalDevice,
                                               const std::string & levelIdentifier,
                                               const std::string & cubeIdentifier,
                                               const Math::Vector3F &position,
                                               const Math::Vector3F &color,
                                               const Math::Vector3F & scale /*=Math::Vector3F(1,1,1)*/,
                                               const SRotation & rotate /*=Math::Vector3F(0,0,0)*/
)
{
    if (!SceneManager::getInstance()->isExisting(levelIdentifier))
    {
        return nullptr;
    }

    //
    // Search if cube already exist
    auto search = m_pool[levelIdentifier].find(cubeIdentifier);

    if (search != m_pool[levelIdentifier].end() && m_pool[levelIdentifier][cubeIdentifier] != nullptr) {
        return m_pool[levelIdentifier][cubeIdentifier];
    }

    // Create cube instance
    m_pool[levelIdentifier][cubeIdentifier] = new Plane(logicalDevice, levelIdentifier, cubeIdentifier, position, color, scale, rotate);
    return m_pool[levelIdentifier][cubeIdentifier];
}

object::Plane * object::PlaneManager::createPlaneAutoName(const graphics::LogicalDevice & logicalDevice,
                                                       const std::string & levelIdentifier,
                                                       const Math::Vector3F &position,
                                                       const Math::Vector3F &color,
                                                       const Math::Vector3F & scale /*=Math::Vector3F(1,1,1)*/,
                                                       const SRotation & rotate /*=Math::Vector3F(0,0,0)*/
)
{
    if (!SceneManager::getInstance()->isExisting(levelIdentifier))
    {
        return nullptr;
    }
    const size_t size = m_pool[levelIdentifier].size();
    std::string identifier = "PLANE_" + std::to_string(size);

    return createPlane(logicalDevice, identifier, levelIdentifier, position, color, scale, rotate);
}

object::Plane * object::PlaneManager::findPlane(const std::string & levelIdentifier, const std::string & cubeIdentifier)
{
    if (!SceneManager::getInstance()->isExisting(levelIdentifier))
    {
        return nullptr;
    }

    auto search = m_pool[levelIdentifier].find(cubeIdentifier);

    if (search != m_pool[levelIdentifier].end()) {
        return m_pool[levelIdentifier][cubeIdentifier];
    }
    return nullptr;
}

bool object::PlaneManager::deletePlane(const std::string & identifier,
                                     const std::string & levelIdentifier,
                                     const graphics::LogicalDevice & logicalDevice)
{
    if (m_pool.find(levelIdentifier) == m_pool.end() ||
        m_pool[levelIdentifier].find(identifier) == m_pool[levelIdentifier].end()) {
        return false;
    }

    m_pool[levelIdentifier][identifier]->release(logicalDevice);
    delete m_pool[levelIdentifier][identifier];
    m_pool[levelIdentifier][identifier] = nullptr;
    return true;
}

void object::PlaneManager::release(const graphics::LogicalDevice &logicalDevice)
{
    for (auto & map : m_pool)
    {
        for (auto & plane : map.second)
        {
            plane.second->release(logicalDevice);
            delete plane.second;
            plane.second = nullptr;
        }
    }
}

std::vector<object::GameObject *> object::PlaneManager::getObjectOfLevel(const std::string &levelIdentifier)
{
    std::vector<object::GameObject *> objects;

    for (const std::pair<std::string const, Plane *> & pair : m_pool[levelIdentifier])
    {
        objects.emplace_back(pair.second);
    }
    return objects;
}