//
// Created by tangt on 03/11/2020.
//

#ifndef GAMEENGINE_PLANEMANAGER_H
#define GAMEENGINE_PLANEMANAGER_H


#include <unordered_map>
#include <string>
#include "../Math/Vector3F.h"
#include "LogicalDevice.h"
#include "../Math/SRotation.h"

#include "public/GraphicsEngine/GraphicsEngine.h"

namespace object {

    class Plane;
    class GameObject;

    class GRAPHICS_ENGINE_EXPORT PlaneManager {
    public:

        friend class Scene;

        static PlaneManager *getInstance();

        /**
         * Create a cube instance. If the identifier already existe in the pool return the existing instance
         * @param identifier    Identifier in the pool of the cube
         * @param position      Position of the cube in the world
         * @param color         Color of the cube
         * @param scale         Scale of the cube
         * @return  instance of Plane
         */
        Plane *createPlane(
                         const std::string &levelIdentifier,
                         const std::string &identifier,
                         const Math::Vector3F &position,
                         const Math::Vector3F &color = Math::Vector3F(1.f, 1.f, 1.f),
                         const Math::Vector3F &scale = Math::Vector3F(1.f, 1.f, 1.f),
                         const Math::SRotation &rotate = {0.f, Math::Vector3F(0.f, 0.f, 0.f)});

        /**
         * Work like createPlane but the identifier is create automaticly
         * with the patern PLANE_XXX where XXX is it number in the pool
         * @param position  Position of the cube in the world
         * @param color     Color of the cube
         * @param scale     Scale of the cube
         * @return  instance of Plane
         */
        Plane *createPlaneAutoName(
                                 const std::string &levelIdentifier,
                                 const Math::Vector3F &position,
                                 const Math::Vector3F &color = Math::Vector3F(1.f, 1.f, 1.f),
                                 const Math::Vector3F &scale = Math::Vector3F(1.f, 1.f, 1.f),
                                 const Math::SRotation &rotate = {0.f, Math::Vector3F(0.f, 0.f, 0.f)});

        /**
         * Find a Plane instance in the pool. Assert if the cube doesn't exist
         * @param identifier    Plane identifier in the pool
         * @return Plane instance if find else nullptr
         */
        Plane *findPlane(const std::string &cubeIdentifier, const std::string &levelIdentifier);

        /**
         * Delete a Plane instance in the pool
         * @param identifier    Identifier of the Plane
         * @return true if success else false if the Plane identifier doesn't exist in the pool
         */
        bool deletePlane(const std::string &identifier,
                        const std::string &levelIdentifier);

        void release(); ///< Release all element in the pool

        void releaseScene(const std::string & levelIdentifier);

    private:
        PlaneManager() = default;

        std::vector<GameObject *> getObjectOfLevel(const std::string &levelIdentifier);

        std::unordered_map<std::string, std::unordered_map<std::string, Plane *>> m_pool;
    };
}

#endif //GAMEENGINE_PLANEMANAGER_H
