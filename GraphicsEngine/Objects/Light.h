//
// Created by theos on 03/11/2020.
//

#ifndef GAMEENGINE_LIGHT_H
#define GAMEENGINE_LIGHT_H

#include "Vector3F.h"
#include "Matrix4F.h"
#include "Cube.h"

#include <string>

namespace object {

    class Light: public Cube
    {
        friend class LightManager;

    public:
        float getStrength() const;
        float getSpecular() const;

        void setStrength(float strength);
        void setSpecular(float specular);

    private:
        Light( const std::string & levelIdentifier,
			   const std::string & identifier,
			   const Math::Vector3F & position,
               float strength,
			   float specular,
               const Math::Vector3F & color);

        Math::Vector3F m_position;
        float m_strength;
        float m_specular;
        Math::Vector3F m_color;

		std::string m_strLevelIdentifier;
		std::string m_strIdentifier;
    };

}

#endif //GAMEENGINE_LIGHT_H
