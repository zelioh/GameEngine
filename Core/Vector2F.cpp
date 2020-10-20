#include "Vector2F.h"
using namespace Math;

Math::Vector2F::Vector2F()
{
	X = 0;
	Y = 0;
}

Math::Vector2F::Vector2F(const float inX, const float inY)
{
	this->X = inX;
	this->Y = inY;
}

Math::Vector2F::~Vector2F()
{
}


Vector2F Math::Vector2F::operator+(const Vector2F& V) const
{
	return Vector2F(X + V.X, Y + V.Y);
}

Vector2F Math::Vector2F::operator+=(const Vector2F& V)
{
	X += V.X; 
	Y += V.Y;
	return *this;
}

Vector2F Math::Vector2F::operator-(const Vector2F& V) const
{
	return Vector2F(X - V.X, Y - V.Y);
}

Vector2F Math::Vector2F::operator-=(const Vector2F& V)
{
	X -= V.X;
	Y -= V.Y;
	return *this;
}

Vector2F Math::Vector2F::operator*(const Vector2F& V) const
{
	return Vector2F(X * V.X, Y * V.Y);
}

Vector2F Math::Vector2F::operator*=(const Vector2F& V)
{
	X *= V.X; 
	Y *= V.Y;
	return *this;
}

Vector2F Math::Vector2F::operator/(const Vector2F& V) const
{
	return Vector2F(X / V.X, Y / V.Y);
}

Vector2F Math::Vector2F::operator/=(const Vector2F& V)
{
	X/= V.X;
	Y/= V.Y;
	return *this;
}


bool Math::Vector2F::operator==(const Vector2F& V) const
{
	return X == V.X && Y == V.Y;
}

bool Math::Vector2F::operator!=(const Vector2F& V) const
{
	return X != V.X || Y != V.Y;
}
