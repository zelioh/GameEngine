//
// Created by FiercePC on 09/11/2020.
//

#ifndef GAMEENGINE_SDK_PLANE_H
#define GAMEENGINE_SDK_PLANE_H

#include "GameObject.h"

namespace object
{
    class Plane;
}

namespace sdk {

    class Plane: public GameObject {

        friend class PlaneManager;

    private:
        Plane(object::Plane * pEnginePlane);
    };

}

#endif //GAMEENGINE_PLANE_H
