//
// Created by FiercePC on 09/11/2020.
//

#ifndef GAMEENGINE_SDK_SCENEMANAGER_H
#define GAMEENGINE_SDK_SCENEMANAGER_H

#include <string>

namespace sdk {

    class Scene;

    class SceneManager
    {
    public:
        static Scene createScene(const std::string & identifier);
        static bool setCurrentScene(const std::string & identifier);
        static Scene getCurrentScene();
        static const std::string & getCurrentSceneIdentifier();
        static bool releaseScene(const std::string & identifier);
    };

}

#endif //GAMEENGINE_SCENEMANAGER_H
