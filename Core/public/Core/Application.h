//
// Created by FiercePC on 09/11/2020.
//

#ifndef GAMEENGINE_APPLICATION_H
#define GAMEENGINE_APPLICATION_H

#include <functional>
#include <Window.h>

namespace graphics
{
    class InstanceParameter;
    class WindowParameters;
}

namespace core {

    class Application
    {
    public:
        using PreInitializeCallback = std::function<void(graphics::InstanceParameter & instanceParameter,
                                                         graphics::WindowParameters & windowParameter)>;
        using PostInitializeCallback = std::function<void(void)>;
        using UpdateCallback = std::function<void(float)>;
        using ReleaseCallback = std::function<void()>;

        Application();

        void setPreInitializeCallback(const PreInitializeCallback & function);
        void setPostInitializeCallback(const PostInitializeCallback & function);
        void setPreUpdateFunction(const UpdateCallback & function);
        void setPostUpdateFunction(const UpdateCallback & function);
        void setPreReleaseCallback(const ReleaseCallback & function);
        void setPostReleaseCallback(const ReleaseCallback & function);

        void run();
        void stop();

    private:
        void intialize();
        void update(float deltaTime);
        void release();

        bool m_isRunning;

        PreInitializeCallback m_preInitCallback;
        PostInitializeCallback m_postInitCallback;
        UpdateCallback m_preUploadCallback;
        UpdateCallback m_postUploadCallback;
        ReleaseCallback m_preReleaseCallback;
        ReleaseCallback m_postReleaseCallback;

        float m_fDeltaTime;
    };

}

#endif //GAMEENGINE_APPLICATION_H
