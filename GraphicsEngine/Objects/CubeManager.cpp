//
// Created by tangt on 26/10/2020.
//
// Use for create a cube Instance
//

#include "CubeManager.h"
#include "Cube.h"
#include "SceneManager.h"
#include "GameObject.h"

/*static*/ object::CubeManager * object::CubeManager::getInstance()
{
    static CubeManager * manager = nullptr;

    if (nullptr == manager)
    {
        manager = new CubeManager();
    }
    return manager;
}

object::Cube * object::CubeManager::createCube(const std::string & levelIdentifier,
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
    m_pool[levelIdentifier][cubeIdentifier] = new Cube(levelIdentifier, cubeIdentifier, position, color, scale, rotate);
    return m_pool[levelIdentifier][cubeIdentifier];
}

object::Cube * object::CubeManager::createCubeAutoName(const std::string & levelIdentifier,
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

    return createCube(identifier, levelIdentifier, position, color, scale, rotate);
}

object::Cube * object::CubeManager::findCube(const std::string & levelIdentifier, const std::string & cubeIdentifier)
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

bool object::CubeManager::deleteCube(const std::string & identifier,
                                     const std::string & levelIdentifier)
{
    if (m_pool.find(levelIdentifier) == m_pool.end() ||
        m_pool[levelIdentifier].find(identifier) == m_pool[levelIdentifier].end()) {
        return false;
    }
    
    m_pool[levelIdentifier][identifier]->release();
    delete m_pool[levelIdentifier][identifier];
    m_pool[levelIdentifier][identifier] = nullptr;
    return true;
}

void object::CubeManager::release()
{
    for (auto & map : m_pool)
    {
        for (auto & cube : map.second)
        {
            cube.second->release();
            delete cube.second;
            cube.second = nullptr;
        }
    }
}

std::vector<object::GameObject *> object::CubeManager::getObjectOfLevel(const std::string &levelIdentifier)
{
    std::vector<object::GameObject *> objects;

    for (const std::pair<std::string const, Cube *> & pair : m_pool[levelIdentifier])
    {
        objects.emplace_back(pair.second);
    }
    return objects;
}