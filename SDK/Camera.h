//
// Created by FiercePC on 09/11/2020.
//

#ifndef GAMEENGINE_SDK_CAMERA_H
#define GAMEENGINE_SDK_CAMERA_H

#include "../Math/Vector3F.h"
#include <string>

namespace object
{
    class Camera;
}

namespace sdk {

    class Camera {

        friend class CameraManager;
        friend class Scene;

    public:
        const Math::Vector3F & getPosition() const;
        const Math::Vector3F & getTarget() const;
        const Math::Vector3F & getUpAxis() const;
        const std::string & getLevelIdentifier() const;
        const std::string & getIndentifier() const;

        void setPosition(const Math::Vector3F & position);
        void setTarget(const Math::Vector3F & target);
        void setUpAxis(const Math::Vector3F & upAxis);

    private:
        Camera(object::Camera * pEngineCamera);

        object::Camera * m_pObjectCamera;
    };

}

#endif //GAMEENGINE_CAMERA_H
