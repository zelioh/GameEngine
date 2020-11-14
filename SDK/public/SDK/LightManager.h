//
// Created by FiercePC on 09/11/2020.
//

#ifndef GAMEENGINE_SDK_LIGHTMANAGER_H
#define GAMEENGINE_SDK_LIGHTMANAGER_H

#include "Light.h"

namespace sdk {

    class LightManager
    {
    public:
        static Light createLight(  const std::string & levelIdentifier,
                              const std::string & LightIdentifier,
                              const Math::Vector3F & position,
                              float strength,
                              float specular,
                              const Math::Vector3F & color = Math::Vector3F(1.f, 1.f, 1.f));

        static Light createLightAutoName(const std::string& levelIdentifier,
                                    const Math::Vector3F& position,
                                    float strength,
                                    float specular,
                                    const Math::Vector3F & color = Math::Vector3F(1.f, 1.f, 1.f));

        static Light findLight(const std::string & levelIdentifier, const std::string & LightIdentifier);

        static bool deleteLight(const std::string & levelIdentifier, const std::string & LightIdentifier);
    };

}

#endif //GAMEENGINE_LIGHTMANAGER_H
