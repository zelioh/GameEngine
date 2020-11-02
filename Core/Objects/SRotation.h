//
// Created by tangt on 02/11/2020.
//

#ifndef GAMEENGINE_SROTATION_H
#define GAMEENGINE_SROTATION_H

#include "Vector3F.h"
#include "Matrix4F.h"

#define PI 3.14159265359f

namespace object
{
    struct SRotation {
        float angle; ///< degree value of the rotation
        Math::Vector3F axis; ///< axis value of rotation

        Math::Matrix4F toMatrix();
    };
}

#endif //GAMEENGINE_SROTATION_H
