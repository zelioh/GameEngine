#pragma once
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
		Vector3F operator*=(const Vector3F& value);
		Vector3F operator/(const Vector3F& value) const;
		Vector3F operator/=(const Vector3F& value);
		bool operator==(const Vector3F& value) const;
		bool operator!=(const Vector3F& value) const;
	};
};

