#pragma once

#include <math.h>

namespace Math {
	class Vector3F
	{
	public:
		float X;
		float Y;
		float Z;

	public:
		Vector3F();
		Vector3F(const float inX, const float inY, const float inZ);
		~Vector3F();

		// operator 


		Vector3F operator+(const Vector3F& value) const;
		Vector3F operator+=(const Vector3F& value);
		Vector3F operator-(const Vector3F& value) const;
		Vector3F operator-=(const Vector3F& value);
		Vector3F operator*(const Vector3F& value) const;
		Vector3F operator*(float scalar) const;
		Vector3F operator*=(const Vector3F& value);
		Vector3F operator/(const Vector3F& value) const;
		Vector3F operator/(float scalar) const;
		Vector3F operator/=(const Vector3F& value);
		bool operator==(const Vector3F& value) const;
		bool operator!=(const Vector3F& value) const;
			
		float Max() const;
		Vector3F Max(const Vector3F& value) const;
		float Length() const { return sqrtf(this->X * this->X + this->Y * this->Y + this->Z * this->Z); }
		float Dot(const Vector3F& v) const { return this->X * v.X + this->Y * v.Y + this->Z * v.Z; }
		Vector3F Normalized() const;
		Vector3F Reflection(Vector3F& normal) const;
		
	};
};

