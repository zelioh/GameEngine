//
// Created by tangt on 03/11/2020.
//

#include "Math_utils.h"
#include "Matrix4F.h"
#include <cmath>
#include "Objects/SRotation.h"

Math::Matrix4F Math::utils::perspective(float fovy, float aspect, float zNear, float zFar)
{
    float rFovy = (fovy * (PI / 180.f));
    float tHalfFovy = tan(rFovy / 2.f);
    Matrix4F result;

    result(0, 0) = 1.f / (aspect * tHalfFovy);
    result(1, 1) = 1.f / tHalfFovy;
    result(2, 2) = zFar / (zNear - zFar);
    result(2, 3) = -1.f;
    result(3, 2) = -(zFar * zNear) / (zFar - zNear);
    return result;
}

Math::Vector3F Math::utils::normalize(const Vector3F &vector)
{
    return vector / sqrt((vector.X * vector.X) + (vector.Y * vector.Y) + (vector.Z * vector.Z));
}

Math::Vector3F Math::utils::cross(const Vector3F &first, const Vector3F &second)
{
    return Vector3F(first.Y * second.Z - second.Y * first.Z,
                    first.Z * second.X - second.Z * first.X,
                    first.X * second.Y - second.X * first.Y);
}

float Math::utils::dot(const Vector3F &first, const Vector3F &second)
{
    Vector3F tmp = first * second;

    return tmp.X + tmp.Y + tmp.Z;
}