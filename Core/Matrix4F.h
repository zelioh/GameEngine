//
// Created by tangt on 28/10/2020.
//

#ifndef GAMEENGINE_MATRIX4F_H
#define GAMEENGINE_MATRIX4F_H

#include "Matrix.h"
#include "Vector4F.h"

namespace Math {
    class Matrix4F : public Matrix<float, 4, 4>
    {
    public:
        Matrix4F();
        Matrix4F(const Vector4F & firstLine,
                 const Vector4F & secondLine,
                 const Vector4F & thirdLine,
                 const Vector4F & lastLine);
        Matrix4F(float values[4][4]);

        Matrix4F operator*(const Matrix4F & other);
    };

#define MATRIX4F_IDENTITY Math::Matrix4F({ \
                                    {1.f, 0.f, 0.f, 0.f}, \
                                    {0.f, 1.f, 0.f, 0.f}, \
                                    {0.f, 0.f, 1.f, 0.f}, \
                                    {0.f, 0.f, 0.f, 1.f}  \
                                    })
}

#endif //GAMEENGINE_MATRIX4F_H
