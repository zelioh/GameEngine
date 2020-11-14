//
// Created by FiercePC on 09/11/2020.
//

#ifndef GAMEENGINE_SDK_SCENE_H
#define GAMEENGINE_SDK_SCENE_H

#include <string>
#include "Camera.h"

namespace object
{
    class Scene;
}

namespace sdk {

    class Scene {

        friend class SceneManager;

    public:
        const std::string & getIdentifier() const;
        sdk::Camera getCurrentCamera() const;
        void setCurrentCamera(const sdk::Camera & camera);
        bool setCurrentCamera(const std::string & cameraIdentifier);

    private:
        Scene(object::Scene * pEngineScene);

        object::Scene * m_pScene;
    };

}

#endif //GAMEENGINE_SCENE_H
