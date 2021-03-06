//
// Created by tangt on 26/10/2020.
//
// Use for create a cube Instance
//

#include "GraphicsEngine/CubeManager.h"
#include "GraphicsEngine/Cube.h"
#include "GraphicsEngine/SceneManager.h"
#include "Debug_utils.h"

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
                                               const Math::SRotation & rotate /*=Math::Vector3F(0,0,0)*/
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
        WARNING_MESSAGE("Cube: " + cubeIdentifier + " already exist");
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
                                                       const Math::SRotation & rotate /*=Math::Vector3F(0,0,0)*/
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
    ERROR_MESSAGE("Cube doesn't exist");
    ASSERT_ALWAYS();
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

void object::CubeManager::releaseScene(const std::string &levelIdentifier)
{
    for (auto & obj : m_pool[levelIdentifier])
    {
        obj.second->release();
        delete obj.second;
        obj.second = nullptr;
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