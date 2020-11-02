//
// Created by tangt on 31/10/2020.
//

#ifndef GAMEENGINE_SCENEMANAGER_H
#define GAMEENGINE_SCENEMANAGER_H

#include <string>
#include <unordered_map>

namespace object {

    class Scene;

    class SceneManager
    {
    public:
        static SceneManager * getInstance();
        Scene * createScene(const std::string & identifier);
        bool setCurrentScene(const std::string & identifier);
        Scene * getCurrentScene();
        const std::string & getCurrentSceneIdentifier() const;
        bool releaseScene(const std::string & identifier);

        void release();

        bool isExisting(const std::string & identifier);

    private:
        SceneManager();

        std::unordered_map<std::string, Scene *> m_pool; ///< const char * == sceneIdentifier, Scene * == scene
        std::string m_currentSceneId;
    };

}

#endif //GAMEENGINE_SCENEMANAGER_H
