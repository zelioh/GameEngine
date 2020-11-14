//
// Created by tangt on 03/11/2020.
//

#ifndef GAMEENGINE_MATH_UTILS_H
#define GAMEENGINE_MATH_UTILS_H

#include "MathEngine.h"

namespace Math
{
    class Matrix4F;
    class Vector3F;

    namespace utils
    {
        MATH_EXPORT inline Matrix4F perspective(float fovy, float aspect, float zNear, float zFar);
        MATH_EXPORT inline Vector3F normalize(const Vector3F & vector);
        MATH_EXPORT inline Vector3F cross(const Vector3F & first, const Vector3F & second);
        MATH_EXPORT inline float dot(const Vector3F & first, const Vector3F & second);
    }
}

#include "Math_utils.inl"

#endif //GAMEENGINE_MATH_UTILS_H
