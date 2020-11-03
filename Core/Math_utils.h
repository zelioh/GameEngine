//
// Created by tangt on 03/11/2020.
//

#ifndef GAMEENGINE_MATH_UTILS_H
#define GAMEENGINE_MATH_UTILS_H

namespace Math
{
    class Matrix4F;
    class Vector3F;

    namespace utils
    {
        inline Matrix4F perspective(float fovy, float aspect, float zNear, float zFar);
        inline Vector3F normalize(const Vector3F & vector);
        inline Vector3F cross(const Vector3F & first, const Vector3F & second);
        inline float dot(const Vector3F & first, const Vector3F & second);
    }
}

#include "Math_utils.inl"

#endif //GAMEENGINE_MATH_UTILS_H
