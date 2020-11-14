//
// Created by FiercePC on 09/11/2020.
//

#ifndef GAMEENGINE_SDK_LIGHT_H
#define GAMEENGINE_SDK_LIGHT_H

#include "../Math/Vector3F.h"
#include <string>

namespace object
{
    class Light;
}

namespace sdk {

    class Light
    {

        friend class LightManager;

    public:
        const Math::Vector3F & getPosition() const;
        const Math::Vector3F & getColor() const;
        float getStrength() const;
        float getSpecular() const;
        const std::string & getLevelIdentifier() const;
        const std::string & getIdentifier() const;

        void setPosition(const Math::Vector3F & position);
        void setColor(const Math::Vector3F & color);
        void setStrength(float strength);
        void setSpecular(float specular);
    private:
        Light(object::Light * pLight);

        object::Light * m_pLight;
    };

}

#endif //GAMEENGINE_LIGHT_H
