//
// Created by tangt on 02/11/2020.
//

#ifndef GAMEENGINE_SROTATION_H
#define GAMEENGINE_SROTATION_H

#include "Vector3F.h"
#include "Matrix4F.h"
#include "MathEngine.h"

#define PI 3.14159265359f

namespace Math
{
    struct MATH_EXPORT SRotation {
        float angle; ///< degree value of the rotation
        Math::Vector3F axis; ///< axis value of rotation

        Math::Matrix4F toMatrix() const;
        void rotateMatrix(Math::Matrix4F & matrix) const;
    };
}

#endif //GAMEENGINE_SROTATION_H
