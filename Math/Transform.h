#pragma once

#include "Vector3F.h"
#include "MathEngine.h"

using namespace Math;

namespace Math {
	class MATH_EXPORT Transform
	{
	public:
		Vector3F Position;
		Vector3F Rotation;
		Vector3F Scale;
		int Weight;

	public:
		Transform();
		Transform(const Vector3F inPosition, const Vector3F inRotation, const Vector3F inScale, const int inWeight);
		~Transform();
	};
}

