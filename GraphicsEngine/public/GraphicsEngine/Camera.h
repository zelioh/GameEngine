//
// Created by tangt on 03/11/2020.
//

#ifndef GAMEENGINE_CAMERA_H
#define GAMEENGINE_CAMERA_H

#include "Vector3F.h"
#include "Matrix4F.h"

#include "public/GraphicsEngine/GraphicsEngine.h"

#include <string>

namespace object {

    class GRAPHICS_ENGINE_EXPORT Camera
    {
        friend class CameraManager;

    public:
        const Math::Vector3F & getPosition() const;
        const Math::Vector3F & getTarget() const;
        const Math::Vector3F & getUpAxis() const;
        const std::string & getLevelIdentifier() const;
        const std::string & getIdentifier() const;

        void setPosition(const Math::Vector3F & position);
        void setTarget(const Math::Vector3F & target);
        void setUpAxis(const Math::Vector3F & upAxis);

        const Math::Matrix4F & getViewMatrix() const;

    private:
        Camera(const std::string & levelIdentifier,
               const std::string & identifier,
               const Math::Vector3F & position,
               const Math::Vector3F & target,
               const Math::Vector3F & upAxis);

        void computeViewMatrix();

        Math::Vector3F m_position;
        Math::Vector3F m_target;
        Math::Vector3F m_upAxis;
        Math::Matrix4F m_viewMatrix;

        std::string m_strLevelIdentifier;
        std::string m_strIdentifier;
    };

}

#endif //GAMEENGINE_CAMERA_H
