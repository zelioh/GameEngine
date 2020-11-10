//
// Created by tangt on 03/11/2020.
//

#ifndef GAMEENGINE_CAMERAMANAGER_H
#define GAMEENGINE_CAMERAMANAGER_H

#include <string>
#include <unordered_map>

namespace Math
{
    class Vector3F;
}

namespace object {

    class Camera;

    class CameraManager
    {
    public:
        /**
         * Get a singleton instance of CameraManager
         * @return cameraManager instance
         */
        static CameraManager * getInstance();

        /**
         * Create a camera instance. If camera already exist return the existing camera
         * @param levelIdentifier       Identifier of the scene where the camera is create
         * @param cameraIdentifier      Identifier of the camera in a scene
         * @param position              Camera position in the world
         * @param target                Where the camera is looking
         * @param upAxis                The up axis of the world. In this engine Z.
         * @return new camera instance or existing instance
         */
        Camera * createCamera(const std::string & levelIdentifier,
                              const std::string & cameraIdentifier,
                              const Math::Vector3F & position,
                              const Math::Vector3F & target,
                              const Math::Vector3F & upAxis);

        /**
         * Work like createCube but the identifier is create automaticly
         * with the patern CAMERA_XXX where XXX is it number in the pool
         * @param levelIdentifier   Identifier of scene where the camera must be create
         * @param position          Camera position in the world
         * @param target            Where the camera is looking
         * @param upAxis            Up axis of the world. In this engine Z.
         * @return new camera instance or existing instance
         */
        Camera * createCameraAutoName(const std::string & levelIdentifier,
                                      const Math::Vector3F & position,
                                      const Math::Vector3F & target,
                                      const Math::Vector3F & upAxis);

        /**
         * Find a camera in the pool
         * @param levelIdentifier   Identifier of the scene where the camera was created
         * @param cameraIdentifier  Identifier of the camera in the pool
         * @return camera instance or nullptr if the camera doesn't exist
         */
        Camera * findCamera(const std::string & levelIdentifier, const std::string & cameraIdentifier);

        /**
         * Delete a camera in a scene
         * @param levelIdentifier   Identifier of the scene where the camera was created
         * @param cameraIdentifier  Identifier of the camera in the pool
         * @return true if camera was delete or false instead
         */
        bool deleteCamera(const std::string & levelIdentifier, const std::string & cameraIdentifier);

        /**
         * Release all cameras in all scenes
         */
        void release();

        void releaseScene(const std::string & levelIdentifier);
    private:
        CameraManager() = default;

        std::unordered_map<std::string, std::unordered_map<std::string, Camera *>> m_pool;
    };

}

#endif //GAMEENGINE_CAMERAMANAGER_H
