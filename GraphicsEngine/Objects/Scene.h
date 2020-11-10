//
// Created by tangt on 31/10/2020.
//

#ifndef GAMEENGINE_SCENE_H
#define GAMEENGINE_SCENE_H

#include <string>
#include <vector>
#include "GameObject.h"
#include "PhysicsEngine.h"

namespace object {

    class Camera;
    class Light;

    class Scene {

        friend class SceneManager;

    public:
        std::vector<object::GameObject *> getSceneObjects();

        const std::string & getIndentifier();

        bool setCurrentCamera(Camera * camera);
        bool setCurrentCamera(const std::string & cameraIdentifier);

        Camera * getCurrentCamera() const;
        PhysicsEngine & getPhysicsEngine();
        Light * getLight() const;

        void update();
        void release();
    private:
        Scene(const std::string &identifier);

        const std::string m_strIdentifier;
        Camera * m_camera;
        PhysicsEngine m_physicsEngine;
        Light * m_light;
    };

}

#endif //GAMEENGINE_SCENE_H
