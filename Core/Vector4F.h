#pragma once
namespace Math {
	class Vector4F
	{
	public:
		float X;
		float Y;
		float Z;
		float W;

	public:
		Vector4F();
		Vector4F(const float inX, const float inY, const float inZ, const float inW);
		~Vector4F();

		// operator 

		Vector4F operator+(const Vector4F& value) const;
		Vector4F operator+=(const Vector4F& value);
		Vector4F operator-(const Vector4F& value) const;
		Vector4F operator-=(const Vector4F& value);
		Vector4F operator*(const Vector4F& value) const;
		Vector4F operator*=(const Vector4F& value);
		Vector4F operator/(const Vector4F& value) const;
		Vector4F operator/=(const Vector4F& value);
		bool operator==(const Vector4F& value) const;
		bool operator!=(const Vector4F& value) const;
	};
};
