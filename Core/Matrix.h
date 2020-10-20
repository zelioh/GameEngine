#pragma once

#include "Vector4F.h"

using namespace Math;

namespace Math {
	class Matrix
	{
	public:
		Vector4F X;
		Vector4F Y;
		Vector4F Z;
		Vector4F W;

	public:
		Matrix();
		Matrix(const Vector4F& InX, const Vector4F& InY, const Vector4F& InZ, const Vector4F& InW);
		~Matrix();

		Matrix operator* (const Matrix& Other) const;
		void operator*=(const Matrix& Other);
		Matrix operator+ (const Matrix& Other) const;
		void operator+=(const Matrix& Other);
		bool operator==(const Matrix& Other) const;
		bool operator!=(const Matrix& Other) const;
	};
}

