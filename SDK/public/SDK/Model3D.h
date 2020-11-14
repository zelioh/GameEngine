//
// Created by FiercePC on 09/11/2020.
//

#ifndef GAMEENGINE_SDK_MODEL3D_H
#define GAMEENGINE_SDK_MODEL3D_H

#include "GameObject.h"
#include "SDK.h"

namespace object
{
    class Model3D;
}

namespace sdk {

    class SDK_EXPORT Model3D: public GameObject
    {

        friend class Model3DManager;

    private:
        Model3D(object::Model3D * pEngineModel3D);
    };

}

#endif //GAMEENGINE_MODEL3D_H
