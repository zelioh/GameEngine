//
// Created by tangt on 26/10/2020.
//
// Use for create a cube Instance
//

#include "CubeManager.h"
#include "Cube.h"

/*static*/ object::CubeManager * object::CubeManager::getInstance()
{
    static CubeManager * manager = nullptr;

    if (nullptr == manager)
    {
        manager = new CubeManager();
    }
    return manager;
}

object::Cube * object::CubeManager::createCube(const std::string &identifier,
                                               const Math::Vector3F &position,
                                               const Math::Vector3F &color)
{
    //
    // Search if cube already exist
    auto search = m_pool.find(identifier.c_str());

    if (search != m_pool.end() && m_pool[identifier.c_str()] != nullptr) {
        return m_pool[identifier.c_str()];
    }

    // Create cube instance
    m_pool[identifier.c_str()] = new Cube(identifier, position, color);
    return m_pool[identifier.c_str()];
}

object::Cube * object::CubeManager::createCubeAutoName(const Math::Vector3F &position, const Math::Vector3F &color)
{
    const size_t size = m_pool.size();
    std::string identifier = "CUBE_" + std::to_string(size);

    return createCube(identifier, position, color);
}

object::Cube * object::CubeManager::findCube(const std::string identifier)
{
    auto search = m_pool.find(identifier.c_str());

    if (search != m_pool.end()) {
        return m_pool[identifier.c_str()];
    }
    return nullptr;
}

bool object::CubeManager::deleteCube(const std::string identifier)
{
    auto search = m_pool.find(identifier.c_str());

    if (search == m_pool.end()) {
        return false;
    }
    delete m_pool[identifier.c_str()];
    m_pool[identifier.c_str()] = nullptr;
    return true;
}