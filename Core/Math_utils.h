//
// Created by tangt on 03/11/2020.
//

#ifndef GAMEENGINE_MATH_UTILS_H
#define GAMEENGINE_MATH_UTILS_H

namespace Math
{
    class Matrix4F;

    namespace utils
    {
        inline Matrix4F perspective(float fovy, float aspect, float zNear, float zFar);
    }
}

#include "Math_utils.inl"

#endif //GAMEENGINE_MATH_UTILS_H
