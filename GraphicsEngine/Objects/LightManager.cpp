//
// Created by theos on 03/11/2020.
//

#include "LightManager.h"
#include "Light.h"
#include "SceneManager.h"

object::LightManager * object::LightManager::getInstance()
{
    static LightManager * manager = nullptr;

    if (nullptr == manager)
    {
        manager = new LightManager();
    }
    return manager;
}

object::Light * object::LightManager::createLight(const std::string& levelIdentifier,
												  const std::string& LightIdentifier,
												  const Math::Vector3F& position,
												  float strength,
												  float specular,
												  const Math::Vector3F& color)
{
    if (!SceneManager::getInstance()->isExisting(levelIdentifier))
    {
        return nullptr;
    }

    //
    // Search if light already exist
    auto search = m_pool[levelIdentifier].find(LightIdentifier);

    if (search != m_pool[levelIdentifier].end() && m_pool[levelIdentifier][LightIdentifier] != nullptr) {
        WARNING_MESSAGE("Ligth: " + LightIdentifier + " already exist");
        return m_pool[levelIdentifier][LightIdentifier];
    }

    // Create light instance
    m_pool[levelIdentifier][LightIdentifier] = new Light(levelIdentifier, LightIdentifier, position, strength, specular, color);
    return m_pool[levelIdentifier][LightIdentifier];
}

object::Light * object::LightManager::createLightAutoName(const std::string& levelIdentifier,
														  const Math::Vector3F& position,
														  float strength,
														  float specular,
														  const Math::Vector3F& color)
{
    if (!SceneManager::getInstance()->isExisting(levelIdentifier))
    {
        return nullptr;
    }
    const size_t size = m_pool[levelIdentifier].size();
    std::string identifier = "LIGHT_" + std::to_string(size);

    return createLight(levelIdentifier, identifier, position, strength, specular, color);
}

object::Light * object::LightManager::findLight(const std::string &levelIdentifier, const std::string &LightIdentifier)
{
    if (!SceneManager::getInstance()->isExisting(levelIdentifier))
    {
        return nullptr;
    }

    auto search = m_pool[levelIdentifier].find(LightIdentifier);

    if (search != m_pool[levelIdentifier].end()) {
        return m_pool[levelIdentifier][LightIdentifier];
    }
    ERROR_MESSAGE("Light doesn't exist");
    ASSERT_ALWAYS();
    return nullptr;
}

bool object::LightManager::deleteLight(const std::string &levelIdentifier, const std::string &LightIdentifier)
{
    if (m_pool.find(levelIdentifier) == m_pool.end() ||
        m_pool[levelIdentifier].find(LightIdentifier) == m_pool[levelIdentifier].end()) {
        return false;
    }

    delete m_pool[levelIdentifier][LightIdentifier];
    m_pool[levelIdentifier][LightIdentifier] = nullptr;
    return true;
}

void object::LightManager::release()
{
    for (auto & map : m_pool)
    {
        for (auto & Light : map.second)
        {
            Light.second->release();
            delete Light.second;
            Light.second = nullptr;
        }
    }
}

std::vector<object::Light *> object::LightManager::getLightOfScene(const std::string &levelIdentifier)
{
    std::vector<object::Light *> lights;

    for (auto level : m_pool)
    {
        for (auto element : level.second)
        {
            lights.emplace_back(element.second);
        }
    }
    return lights;
}