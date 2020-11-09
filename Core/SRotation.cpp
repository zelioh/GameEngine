//
// Created by tangt on 02/11/2020.
//

#include "SRotation.h"
#include <cmath>

Math::Matrix4F Math::SRotation::toMatrix() const
{
    Math::Matrix4F identity = MATRIX4F_IDENTITY;
    float radian = (angle * (PI / 180.f));
    float cRadian = cos(radian);
    float sRadian = sin(radian);

    Math::Vector3F normalized = axis / sqrt((axis.X * axis.X) + (axis.Y * axis.Y) + (axis.Z * axis.Z));
    Math::Vector3F tmp(normalized * (1.f - cRadian));

    Math::Matrix4F rotateMatrix;

    rotateMatrix(0, 0) = cRadian + tmp.X * normalized.X;
    rotateMatrix(0, 1) = tmp.X * normalized.Y + sRadian * normalized.Z;
    rotateMatrix(0, 2) = tmp.X * normalized.Z - sRadian * normalized.Y;

    rotateMatrix(1, 0) = tmp.Y * normalized.X - sRadian * normalized.Z;
    rotateMatrix(1, 1) = cRadian + tmp.Y * normalized.Y;
    rotateMatrix(1, 2) = tmp.Y * normalized.Z + sRadian * normalized.X;

    rotateMatrix(2, 0) = tmp.Z * normalized.X + sRadian * normalized.Y;
    rotateMatrix(2, 1) = tmp.Z * normalized.Y - sRadian * normalized.X;
    rotateMatrix(2, 2) = cRadian + tmp.Z * normalized.Z;

    Math::Matrix4F result;

    //
    // First line
    result(0, 0) = identity(0, 0) * rotateMatrix(0, 0) + identity(1, 0) * rotateMatrix(0 ,1) + identity(2, 0) * rotateMatrix(0, 2);
    result(0, 1) = identity(0, 1) * rotateMatrix(0, 0) + identity(1, 1) * rotateMatrix(0 ,1) + identity(2, 1) * rotateMatrix(0, 2);
    result(0, 2) = identity(0, 2) * rotateMatrix(0, 0) + identity(1, 2) * rotateMatrix(0 ,1) + identity(2, 2) * rotateMatrix(0, 2);
    result(0, 3) = identity(0, 3) * rotateMatrix(0, 0) + identity(1, 3) * rotateMatrix(0 ,1) + identity(2, 3) * rotateMatrix(0, 2);

    //
    // Second line
    result(1, 0) = identity(0, 0) * rotateMatrix(1, 0) + identity(1, 0) * rotateMatrix(1 ,1) + identity(2, 0) * rotateMatrix(1, 2);
    result(1, 1) = identity(0, 1) * rotateMatrix(1, 0) + identity(1, 1) * rotateMatrix(1 ,1) + identity(2, 1) * rotateMatrix(1, 2);
    result(1, 2) = identity(0, 2) * rotateMatrix(1, 0) + identity(1, 2) * rotateMatrix(1 ,1) + identity(2, 2) * rotateMatrix(1, 2);
    result(1, 3) = identity(0, 3) * rotateMatrix(1, 0) + identity(1, 3) * rotateMatrix(1 ,1) + identity(2, 3) * rotateMatrix(1, 2);

    //
    // Third line
    result(2, 0) = identity(0, 0) * rotateMatrix(2, 0) + identity(1, 0) * rotateMatrix(2,1) + identity(2, 0) * rotateMatrix(2, 2);
    result(2, 1) = identity(0, 1) * rotateMatrix(2, 0) + identity(1, 1) * rotateMatrix(2,1) + identity(2, 1) * rotateMatrix(2, 2);
    result(2, 2) = identity(0, 2) * rotateMatrix(2, 0) + identity(1, 2) * rotateMatrix(2,1) + identity(2, 2) * rotateMatrix(2, 2);
    result(2, 3) = identity(0, 3) * rotateMatrix(2, 0) + identity(1, 3) * rotateMatrix(2,1) + identity(2, 3) * rotateMatrix(2, 2);

    //
    // Fourth line
    result(3, 0) = identity(3, 0);
    result(3, 1) = identity(3, 1);
    result(3, 2) = identity(3, 2);
    result(3, 3) = identity(3, 3);
    return result;
}

void Math::SRotation::rotateMatrix(Math::Matrix4F &matrix) const
{
    float radian = (angle * (PI / 180.f));
    float cRadian = cos(radian);
    float sRadian = sin(radian);

    Math::Vector3F normalized = axis / sqrt((axis.X * axis.X) + (axis.Y * axis.Y) + (axis.Z * axis.Z));
    Math::Vector3F tmp(normalized * (1.f - cRadian));

    Math::Matrix4F rotateMatrix;

    rotateMatrix(0, 0) = cRadian + tmp.X * normalized.X;
    rotateMatrix(0, 1) = tmp.X * normalized.Y + sRadian * normalized.Z;
    rotateMatrix(0, 2) = tmp.X * normalized.Z - sRadian * normalized.Y;

    rotateMatrix(1, 0) = tmp.Y * normalized.X - sRadian * normalized.Z;
    rotateMatrix(1, 1) = cRadian + tmp.Y * normalized.Y;
    rotateMatrix(1, 2) = tmp.Y * normalized.Z + sRadian * normalized.X;

    rotateMatrix(2, 0) = tmp.Z * normalized.X + sRadian * normalized.Y;
    rotateMatrix(2, 1) = tmp.Z * normalized.Y - sRadian * normalized.X;
    rotateMatrix(2, 2) = cRadian + tmp.Z * normalized.Z;

    Math::Matrix4F result;

    //
    // First line
    result(0, 0) = matrix(0, 0) * rotateMatrix(0, 0) + matrix(1, 0) * rotateMatrix(0 ,1) + matrix(2, 0) * rotateMatrix(0, 2);
    result(0, 1) = matrix(0, 1) * rotateMatrix(0, 0) + matrix(1, 1) * rotateMatrix(0 ,1) + matrix(2, 1) * rotateMatrix(0, 2);
    result(0, 2) = matrix(0, 2) * rotateMatrix(0, 0) + matrix(1, 2) * rotateMatrix(0 ,1) + matrix(2, 2) * rotateMatrix(0, 2);
    result(0, 3) = matrix(0, 3) * rotateMatrix(0, 0) + matrix(1, 3) * rotateMatrix(0 ,1) + matrix(2, 3) * rotateMatrix(0, 2);

    //
    // Second line
    result(1, 0) = matrix(0, 0) * rotateMatrix(1, 0) + matrix(1, 0) * rotateMatrix(1 ,1) + matrix(2, 0) * rotateMatrix(1, 2);
    result(1, 1) = matrix(0, 1) * rotateMatrix(1, 0) + matrix(1, 1) * rotateMatrix(1 ,1) + matrix(2, 1) * rotateMatrix(1, 2);
    result(1, 2) = matrix(0, 2) * rotateMatrix(1, 0) + matrix(1, 2) * rotateMatrix(1 ,1) + matrix(2, 2) * rotateMatrix(1, 2);
    result(1, 3) = matrix(0, 3) * rotateMatrix(1, 0) + matrix(1, 3) * rotateMatrix(1 ,1) + matrix(2, 3) * rotateMatrix(1, 2);

    //
    // Third line
    result(2, 0) = matrix(0, 0) * rotateMatrix(2, 0) + matrix(1, 0) * rotateMatrix(2,1) + matrix(2, 0) * rotateMatrix(2, 2);
    result(2, 1) = matrix(0, 1) * rotateMatrix(2, 0) + matrix(1, 1) * rotateMatrix(2,1) + matrix(2, 1) * rotateMatrix(2, 2);
    result(2, 2) = matrix(0, 2) * rotateMatrix(2, 0) + matrix(1, 2) * rotateMatrix(2,1) + matrix(2, 2) * rotateMatrix(2, 2);
    result(2, 3) = matrix(0, 3) * rotateMatrix(2, 0) + matrix(1, 3) * rotateMatrix(2,1) + matrix(2, 3) * rotateMatrix(2, 2);

    //
    // Fourth line
    result(3, 0) = matrix(3, 0);
    result(3, 1) = matrix(3, 1);
    result(3, 2) = matrix(3, 2);
    result(3, 3) = matrix(3, 3);

    matrix = result;
}