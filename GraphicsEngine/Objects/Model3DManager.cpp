//
// Created by tangt on 04/11/2020.
//

#include "Model3DManager.h"
#include "Model3D.h"
#include "GameObject.h"
#include "LogicalDevice.h"
#include "SceneManager.h"
#include "Scene.h"

/*static*/ object::Model3DManager * object::Model3DManager::getInstance()
{
    static Model3DManager * manager = nullptr;

    if (nullptr == manager)
    {
        manager = new Model3DManager();
    }
    return manager;
}

object::Model3D * object::Model3DManager::createModel3D(const graphics::LogicalDevice & logicalDevice,
                                               const std::string & levelIdentifier,
                                               const std::string & model3DIdentifier,
                                               const std::string & fileName,
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
    auto search = m_pool[levelIdentifier].find(model3DIdentifier);

    if (search != m_pool[levelIdentifier].end() && m_pool[levelIdentifier][model3DIdentifier] != nullptr) {
        return m_pool[levelIdentifier][model3DIdentifier];
    }

    // Create cube instance
    m_pool[levelIdentifier][model3DIdentifier] = new Model3D(logicalDevice,
                                                             levelIdentifier,
                                                             model3DIdentifier,
                                                             fileName,
                                                             position, color, scale, rotate);
    return m_pool[levelIdentifier][model3DIdentifier];
}

object::Model3D * object::Model3DManager::createModel3DAutoName(const graphics::LogicalDevice & logicalDevice,
                                                       const std::string & levelIdentifier,
                                                       const std::string & fileName,
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
    std::string identifier = "CUBE_" + std::to_string(size);

    return createModel3D(logicalDevice, identifier, levelIdentifier, fileName, position, color, scale, rotate);
}

object::Model3D * object::Model3DManager::findModel3D(const std::string & levelIdentifier, const std::string & model3DIdentifier)
{
    if (!SceneManager::getInstance()->isExisting(levelIdentifier))
    {
        return nullptr;
    }

    auto search = m_pool[levelIdentifier].find(model3DIdentifier);

    if (search != m_pool[levelIdentifier].end()) {
        return m_pool[levelIdentifier][model3DIdentifier];
    }
    return nullptr;
}

bool object::Model3DManager::deleteModel3D(const std::string & identifier,
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

void object::Model3DManager::release(const graphics::LogicalDevice &logicalDevice)
{
    for (auto & map : m_pool)
    {
        for (auto & cube : map.second)
        {
            cube.second->release(logicalDevice);
            delete cube.second;
            cube.second = nullptr;
        }
    }
}

std::vector<object::GameObject *> object::Model3DManager::getObjectOfLevel(const std::string &levelIdentifier)
{
    std::vector<object::GameObject *> objects;

    for (const std::pair<std::string const, Model3D *> & pair : m_pool[levelIdentifier])
    {
        objects.emplace_back(pair.second);
    }
    return objects;
}