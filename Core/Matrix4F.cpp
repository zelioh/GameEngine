//
// Created by tangt on 28/10/2020.
//

#include "Matrix4F.h"

Math::Matrix4F::Matrix4F():
Matrix<float, 4, 4>(0.f)
{
}

Math::Matrix4F::Matrix4F(const Vector4F & firstLine,
                         const Vector4F & secondLine,
                         const Vector4F & thirdLine,
                         const Vector4F & lastLine):
Matrix<float, 4, 4>(0.f)
{
    m_matrix[0][0] = firstLine.X;
    m_matrix[0][1] = firstLine.Y;
    m_matrix[0][2] = firstLine.Z;
    m_matrix[0][3] = firstLine.W;

    m_matrix[1][0] = secondLine.X;
    m_matrix[1][1] = secondLine.Y;
    m_matrix[1][2] = secondLine.Z;
    m_matrix[1][3] = secondLine.W;

    m_matrix[2][0] = thirdLine.X;
    m_matrix[2][1] = thirdLine.Y;
    m_matrix[2][2] = thirdLine.Z;
    m_matrix[2][3] = thirdLine.W;

    m_matrix[3][0] = lastLine.X;
    m_matrix[3][1] = lastLine.Y;
    m_matrix[3][2] = lastLine.Z;
    m_matrix[3][3] = lastLine.W;
}

Math::Matrix4F::Matrix4F(float values[4][4]):
Matrix<float, 4, 4>(values)
{}

Math::Matrix4F Math::Matrix4F::operator*(const Matrix4F &other)
{
    Matrix4F matrix;

    matrix(0, 0) = m_matrix[0][0] * other.m_matrix[0][0] + m_matrix[0][1] * other.m_matrix[1][0] + m_matrix[0][2] * other.m_matrix[2][0] + m_matrix[0][3] * other.m_matrix[3][0];
    matrix(0, 1) = m_matrix[0][0] * other.m_matrix[0][1] + m_matrix[0][1] * other.m_matrix[1][1] + m_matrix[0][2] * other.m_matrix[2][1] + m_matrix[0][3] * other.m_matrix[3][1];
    matrix(0, 2) = m_matrix[0][0] * other.m_matrix[0][2] + m_matrix[0][1] * other.m_matrix[1][2] + m_matrix[0][2] * other.m_matrix[2][2] + m_matrix[0][3] * other.m_matrix[3][2];
    matrix(0, 3) = m_matrix[0][0] * other.m_matrix[0][3] + m_matrix[0][1] * other.m_matrix[1][3] + m_matrix[0][2] * other.m_matrix[2][3] + m_matrix[0][3] * other.m_matrix[3][3];

    matrix(1, 0) = m_matrix[1][0] * other.m_matrix[0][0] + m_matrix[1][1] * other.m_matrix[1][0] + m_matrix[1][2] * other.m_matrix[2][0] + m_matrix[1][3] * other.m_matrix[3][0];
    matrix(1, 1) = m_matrix[1][0] * other.m_matrix[0][1] + m_matrix[1][1] * other.m_matrix[1][1] + m_matrix[1][2] * other.m_matrix[2][1] + m_matrix[1][3] * other.m_matrix[3][1];
    matrix(1, 2) = m_matrix[1][0] * other.m_matrix[0][2] + m_matrix[1][1] * other.m_matrix[1][2] + m_matrix[1][2] * other.m_matrix[2][2] + m_matrix[1][3] * other.m_matrix[3][2];
    matrix(1, 3) = m_matrix[1][0] * other.m_matrix[0][3] + m_matrix[1][1] * other.m_matrix[1][3] + m_matrix[1][2] * other.m_matrix[2][3] + m_matrix[1][3] * other.m_matrix[3][3];

    matrix(2, 0) = m_matrix[2][0] * other.m_matrix[0][0] + m_matrix[2][1] * other.m_matrix[1][0] + m_matrix[2][2] * other.m_matrix[2][0] + m_matrix[2][3] * other.m_matrix[3][0];
    matrix(2, 1) = m_matrix[2][0] * other.m_matrix[0][1] + m_matrix[2][1] * other.m_matrix[1][1] + m_matrix[2][2] * other.m_matrix[2][1] + m_matrix[2][3] * other.m_matrix[3][1];
    matrix(2, 2) = m_matrix[2][0] * other.m_matrix[0][2] + m_matrix[2][1] * other.m_matrix[1][2] + m_matrix[2][2] * other.m_matrix[2][2] + m_matrix[2][3] * other.m_matrix[3][2];
    matrix(2, 3) = m_matrix[2][0] * other.m_matrix[0][3] + m_matrix[2][1] * other.m_matrix[1][3] + m_matrix[2][2] * other.m_matrix[2][3] + m_matrix[2][3] * other.m_matrix[3][3];

    matrix(3, 0) = m_matrix[3][0] * other.m_matrix[0][0] + m_matrix[3][1] * other.m_matrix[1][0] + m_matrix[3][2] * other.m_matrix[2][0] + m_matrix[3][3] * other.m_matrix[3][0];
    matrix(3, 1) = m_matrix[3][0] * other.m_matrix[0][1] + m_matrix[3][1] * other.m_matrix[1][1] + m_matrix[3][2] * other.m_matrix[2][1] + m_matrix[3][3] * other.m_matrix[3][1];
    matrix(3, 2) = m_matrix[3][0] * other.m_matrix[0][2] + m_matrix[3][1] * other.m_matrix[1][2] + m_matrix[3][2] * other.m_matrix[2][2] + m_matrix[3][3] * other.m_matrix[3][2];
    matrix(3, 3) = m_matrix[3][0] * other.m_matrix[0][3] + m_matrix[3][1] * other.m_matrix[1][3] + m_matrix[3][2] * other.m_matrix[2][3] + m_matrix[3][3] * other.m_matrix[3][3];

    return matrix;
}