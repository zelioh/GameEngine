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

        Vector4F operator[](int rowIndex);
    };

}

#endif //GAMEENGINE_MATRIX4F_H
