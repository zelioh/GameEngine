#pragma once
namespace Math {
	class Vector2F
	{
	public:
		float X;
		float Y;

	public:
		Vector2F();
		Vector2F(const float inX, const float inY);
		~Vector2F();

		// operator

		Vector2F operator+(const Vector2F& value) const;
		Vector2F operator+=(const Vector2F& value);
		Vector2F operator-(const Vector2F& value) const;
		Vector2F operator-=(const Vector2F& value);
		Vector2F operator*(const Vector2F& value) const;
		Vector2F operator*=(const Vector2F& value);
		Vector2F operator/(const Vector2F& value) const;
		Vector2F operator/=(const Vector2F& value);
		bool operator==(const Vector2F& value) const;
		bool operator!=(const Vector2F& value) const;
	};
};

