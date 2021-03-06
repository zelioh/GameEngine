//
// Created by tangt on 26/10/2020.
//
// Use for create a cube Instance
//

#ifndef GAMEENGINE_CUBEMANAGER_H
#define GAMEENGINE_CUBEMANAGER_H

#include <unordered_map>
#include <string>
#include "Vector3F.h"
#include "GraphicsEngine/LogicalDevice.h"
#include "SRotation.h"
#include "public/GraphicsEngine/GraphicsEngine.h"

namespace object {

    class Cube;
    class GameObject;

    class GRAPHICS_ENGINE_EXPORT CubeManager {
    public:

        friend class Scene;

        static CubeManager * getInstance();

        /**
         * Create a cube instance. If the identifier already existe in the pool return the existing instance
         * @param identifier    Identifier in the pool of the cube
         * @param position      Position of the cube in the world
         * @param color         Color of the cube
         * @param scale         Scale of the cube
         * @return  instance of Cube
         */
        Cube * createCube(const std::string & levelIdentifier,
                          const std::string & identifier,
                          const Math::Vector3F & position,
                          const Math::Vector3F & color = Math::Vector3F(1.f, 1.f, 1.f),
                          const Math::Vector3F & scale = Math::Vector3F(1.f, 1.f, 1.f),
                          const Math::SRotation & rotate = {0.f, Math::Vector3F(0.f, 0.f, 0.f)});

        /**
         * Work like createCube but the identifier is create automaticly
         * with the patern CUBE_XXX where XXX is it number in the pool
         * @param position  Position of the cube in the world
         * @param color     Color of the cube
         * @param scale     Scale of the cube
         * @return  instance of Cube
         */
        Cube * createCubeAutoName(const std::string & levelIdentifier,
                                  const Math::Vector3F & position,
                                  const Math::Vector3F & color = Math::Vector3F(1.f, 1.f, 1.f),
                                  const Math::Vector3F & scale = Math::Vector3F(1.f, 1.f, 1.f),
                                  const Math::SRotation & rotate = {0.f, Math::Vector3F(0.f, 0.f, 0.f)});
        /**
         * Find a Cube instance in the pool. Assert if the cube doesn't exist
         * @param identifier    Cube identifier in the pool
         * @return Cube instance if find else nullptr
         */
        Cube * findCube(const std::string & cubeIdentifier, const std::string & levelIdentifier);

        /**
         * Delete a Cube instance in the pool
         * @param identifier    Identifier of the Cube
         * @return true if success else false if the Cube identifier doesn't exist in the pool
         */
        bool deleteCube(const std::string & identifier,
                        const std::string & levelIdentifier);

        void release(); ///< Release all element in the pool

        void releaseScene(const std::string & levelIdentifier);

    private:
        CubeManager() = default;

        std::vector<GameObject *> getObjectOfLevel(const std::string & levelIdentifier);

        std::unordered_map<std::string, std::unordered_map<std::string, Cube *>> m_pool;
    };

}
#endif //GAMEENGINE_CUBEMANAGER_H
