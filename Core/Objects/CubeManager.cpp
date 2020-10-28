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

object::Cube * object::CubeManager::createCube(const graphics::LogicalDevice & logicalDevice,
                                               const std::string &identifier,
                                               const Math::Vector3F &position,
                                               const Math::Vector3F &color,
                                               const Math::Vector3F & scale /*=Math::Vector3F(1,1,1)*/,
                                               const Math::Vector3F & rotate /*=Math::Vector3F(0,0,0)*/
                                               )
{
    //
    // Search if cube already exist
    auto search = m_pool.find(identifier.c_str());

    if (search != m_pool.end() && m_pool[identifier.c_str()] != nullptr) {
        return m_pool[identifier.c_str()];
    }

    // Create cube instance
    m_pool[identifier.c_str()] = new Cube(logicalDevice, identifier, position, color, scale, rotate);
    return m_pool[identifier.c_str()];
}

object::Cube * object::CubeManager::createCubeAutoName(const graphics::LogicalDevice & logicalDevice,
                                                       const Math::Vector3F &position,
                                                       const Math::Vector3F &color,
                                                       const Math::Vector3F & scale /*=Math::Vector3F(1,1,1)*/,
                                                       const Math::Vector3F & rotate /*=Math::Vector3F(0,0,0)*/
                                                        )
{
    const size_t size = m_pool.size();
    std::string identifier = "CUBE_" + std::to_string(size);

    return createCube(logicalDevice, identifier, position, color, scale, rotate);
}

object::Cube * object::CubeManager::findCube(const std::string identifier)
{
    auto search = m_pool.find(identifier.c_str());

    if (search != m_pool.end()) {
        return m_pool[identifier.c_str()];
    }
    return nullptr;
}

bool object::CubeManager::deleteCube(const std::string identifier, const graphics::LogicalDevice & logicalDevice)
{
    auto search = m_pool.find(identifier.c_str());

    if (search == m_pool.end()) {
        return false;
    }
    m_pool[identifier.c_str()]->release(logicalDevice);
    delete m_pool[identifier.c_str()];
    m_pool[identifier.c_str()] = nullptr;
    return true;
}

void object::CubeManager::release(const graphics::LogicalDevice &logicalDevice)
{
    for (std::pair<const char *const, Cube *> & cube : m_pool)
    {
        cube.second->release(logicalDevice);
        delete cube.second;
        cube.second = nullptr;
    }
}