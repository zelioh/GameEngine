//
// Created by tangt on 31/10/2020.
//

#ifndef GAMEENGINE_SCENE_H
#define GAMEENGINE_SCENE_H

#include <string>
#include <vector>
#include "GameObject.h"

namespace object {

    class Camera;

    class Scene {

        friend class SceneManager;

    public:
        std::vector<object::GameObject *> getSceneObjects() const;

        const std::string & getIndentifier();

        bool setCurrentCamera(Camera * camera);
        bool setCurrentCamera(const std::string & cameraIdentifier);

        Camera * getCurrentCamera() const;

    private:
        Scene(const std::string &identifier);

        const std::string m_strIdentifier;
        Camera * m_camera;
    };

}

#endif //GAMEENGINE_SCENE_H
