//
// Created by theos on 03/11/2020.
//

#ifndef GAMEENGINE_LIGHTMANAGER_H
#define GAMEENGINE_LIGHTMANAGER_H

#include <string>
#include <unordered_map>

namespace Math
{
    class Vector3F;
}

namespace object {

    class Light;

    class LightManager
    {
    public:
        /**
         * Get a singleton instance of LightManager
         * @return LightManager instance
         */
        static LightManager * getInstance();

        /**
         * Create a Light instance. If Light already exist return the existing Light
		 * @param levelIdentifier       Identifier of the scene where the light is created
		 * @param cameraIdentifier      Identifier of the light in a scene
         * @param position				Light position in the world
		 * @param strength				Light strength
         * @param specular              Light reflection by an object
         * @param color					Light color
         * @return new Light instance or existing instance
         */
        Light * createLight(  const std::string & levelIdentifier,
                              const std::string & LightIdentifier,
                              const Math::Vector3F & position,
                              const float & strength,
							  const float & specular,
                              const Math::Vector3F & color);

        /**
         * Work like createCube but the identifier is create automaticly
         * with the patern Light_XXX where XXX is it number in the pool
        * @param levelIdentifier       Identifier of the scene where the light is created
		 * @param cameraIdentifier      Identifier of the light in a scene
         * @param position				Light position in the world
		 * @param strength				Light strength
         * @param specular              Light reflection by an object
         * @param color					Light color
         * @return new Light instance or existing instance
         */
        Light * createLightAutoName(const std::string& levelIdentifier,
									const std::string& LightIdentifier,
									const Math::Vector3F& position,
									const float & strength,
									const float & specular,
									const Math::Vector3F& color);

        /**
         * Find a Light in the pool
         * @param levelIdentifier   Identifier of the scene where the Light was created
         * @param LightIdentifier  Identifier of the Light in the pool
         * @return Light instance or nullptr if the Light doesn't exist
         */
        Light * findLight(const std::string & levelIdentifier, const std::string & LightIdentifier);

        /**
         * Delete a Light in a scene
         * @param levelIdentifier   Identifier of the scene where the Light was created
         * @param LightIdentifier  Identifier of the Light in the pool
         * @return true if Light was delete or false instead
         */
        bool deleteLight(const std::string & levelIdentifier, const std::string & LightIdentifier);

        /**
         * Release all Lights in all scenes
         */
        void release();
    private:
        LightManager() = default;

        std::unordered_map<std::string, std::unordered_map<std::string, Light *>> m_pool;
    };

}

#endif //GAMEENGINE_LIGHTMANAGER_H
