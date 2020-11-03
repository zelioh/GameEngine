//
// Created by theos on 03/11/2020.
//

#ifndef GAMEENGINE_LIGHT_H
#define GAMEENGINE_LIGHT_H

#include "Vector3F.h"
#include "Matrix4F.h"

#include <string>

namespace object {

    class Light
    {
        friend class LightManager;

    public:
        const Math::Vector3F & getPosition() const;
        const float & getStrength() const;
        const float & getSpecular() const;
		const Math::Vector3F & getColor() const;

        void setPosition(const Math::Vector3F & position);
        void setStrength(const float & strength);
        void setSpecular(const float & specular);
		void setColor(const Math::Vector3F & color);

    private:
        Light( const Math::Vector3F & position,
               const Math::float & strength,
			   const Math::float & specular,
               const Math::Vector3F & color);

        Math::Vector3F m_position;
        float m_strength;
        float m_specular;
        Math::Vector3F m_color;
    };

}

#endif //GAMEENGINE_LIGHT_H
