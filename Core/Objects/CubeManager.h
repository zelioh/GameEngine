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
#include "LogicalDevice.h"

namespace object {

    class Cube;

    class CubeManager {
    public:
        static CubeManager * getInstance();

        /**
         * Create a cube instance. If the identifier already existe in the pool return the existing instance
         * @param identifier    Identifier in the pool of the cube
         * @param position      Position of the cube in the world
         * @param color         Color of the cube
         * @param scale         Scale of the cube
         * @return  instance of Cube
         */
        Cube * createCube(const graphics::LogicalDevice & logicalDevice,
                          const std::string & identifier,
                          const Math::Vector3F & position,
                          const Math::Vector3F & color,
                          const Math::Vector3F & scale = Math::Vector3F(1.f, 1.f, 1.f),
                          const Math::Vector3F & rotate = Math::Vector3F(0.f, 0.f, 0.f));
        /**
         * Work like createCube but the identifier is create automaticly
         * with the patern CUBE_XXX where XXX is it number in the pool
         * @param position  Position of the cube in the world
         * @param color     Color of the cube
         * @param scale     Scale of the cube
         * @return  instance of Cube
         */
        Cube * createCubeAutoName(const graphics::LogicalDevice & logicalDevice,
                                  const Math::Vector3F & position,
                                  const Math::Vector3F & color,
                                  const Math::Vector3F & scale = Math::Vector3F(1.f, 1.f, 1.f),
                                  const Math::Vector3F & rotate = Math::Vector3F(0.f, 0.f, 0.f));
        /**
         * Find a Cube instance in the pool. Assert if the cube doesn't exist
         * @param identifier    Cube identifier in the pool
         * @return Cube instance if find else nullptr
         */
        Cube * findCube(const std::string identifier);

        /**
         * Delete a Cube instance in the pool
         * @param identifier    Identifier of the Cube
         * @return true if success else false if the Cube identifier doesn't exist in the pool
         */
        bool deleteCube(const std::string identifier, const graphics::LogicalDevice & logicalDevice);

        void release(const graphics::LogicalDevice & logicalDevice); ///< Release all element in the pool

    private:
        CubeManager() = default;

        std::unordered_map<const char *, Cube *> m_pool;
    };

}
#endif //GAMEENGINE_CUBEMANAGER_H
