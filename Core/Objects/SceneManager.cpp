//
// Created by tangt on 31/10/2020.
//

#include "SceneManager.h"
#include "Scene.h"

object::SceneManager * object::SceneManager::getInstance()
{
    static SceneManager * manager = nullptr;

    if (nullptr == manager)
    {
        manager = new SceneManager();
    }
    return manager;
}

object::Scene * object::SceneManager::createScene(const std::string &identifier)
{
    //
    // Search if scene already exist
    auto search = m_pool.find(identifier);

    if (search != m_pool.end() && m_pool[identifier] != nullptr) {
        return m_pool[identifier];
    }

    // Create scene instance
    m_pool[identifier] = new Scene(identifier);
    return m_pool[identifier];
}

bool object::SceneManager::setCurrentScene(const std::string &identifier)
{
    //
    // Search if scene already exist
    auto search = m_pool.find(identifier);

    if (search == m_pool.end()) {
        return false;
    }
    m_currentSceneId = identifier;
    return true;
}

object::Scene * object::SceneManager::getCurrentScene()
{
    return m_pool[m_currentSceneId];
}

const std::string & object::SceneManager::getCurrentSceneIdentifier() const
{
    return m_currentSceneId;
}

bool object::SceneManager::releaseScene(const std::string &identifier)
{
    //
    // Search if scene already exist
    auto search = m_pool.find(identifier);

    if (search == m_pool.end()) {
        return false;
    }
    //m_pool[identifier]->release(); ///< TODO
    delete m_pool[identifier];
    m_pool[identifier] = nullptr;
    return true;
}

void object::SceneManager::release()
{
    for (std::pair<std::string const, Scene *> & element : m_pool)
    {
        //element.second->release() ///< TODO
        delete element.second;
        element.second = nullptr;
    }
}

bool object::SceneManager::isExisting(const std::string &identifier)
{
    return m_pool.find(identifier) != m_pool.end();
}

object::SceneManager::SceneManager():
m_currentSceneId("")
{}