//
// Created by FiercePC on 10/11/2020.
//

#ifndef GAMEENGINE_SDK_APPLICATION_H
#define GAMEENGINE_SDK_APPLICATION_H

#include <functional>
#include "public/GraphicsEngine/InstanceParameter.h"
#include "public/GraphicsEngine/WindowParameters.h"
#include "Matrix4F.h"

#include "SDK.h"

namespace core
{
    class Application;
}

namespace sdk {

    class SDK_EXPORT Application
    {
    public:
        Application();

        using PreInitializeCallback = std::function<void(graphics::InstanceParameter & instanceParameter,
                                                         graphics::WindowParameters & windowParameter)>;
        using PostInitializeCallback = std::function<void()>;
        using UpdateCallback = std::function<void(float, Math::Matrix4F & projectionMatrix)>;
        using ReleaseCallback = std::function<void()>;

        void setPreInitializeCallback(const PreInitializeCallback & function);
        void setPostInitializeCallback(const PostInitializeCallback & function);
        void setPreUpdateFunction(const UpdateCallback & function);
        void setPostUpdateFunction(const UpdateCallback & function);
        void setPreReleaseCallback(const ReleaseCallback & function);
        void setPostReleaseCallback(const ReleaseCallback & function);

        void run();
    private:
        core::Application * m_pApplication;
    };

}

#endif //GAMEENGINE_APPLICATION_H
