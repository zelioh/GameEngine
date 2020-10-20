#include "Vector3F.h"
using namespace Math;

Math::Vector3F::Vector3F()
{
	X = 0;
	Y = 0;
	Z = 0;
}

Math::Vector3F::Vector3F(const float inX, const float inY, const float inZ)
{
	this->X = inX;
	this->Y = inY;
	this->Z = inZ;
}

Math::Vector3F::~Vector3F()
{
}

Vector3F Math::Vector3F::operator+(const Vector3F& V) const
{
	return Vector3F(X + V.X, Y + V.Y, Z + V.Z);
}

Vector3F Math::Vector3F::operator+=(const Vector3F& V) 
{
	X += V.X; 
	Y += V.Y; 
	Z += V.Z;
	return *this;
}

Vector3F Math::Vector3F::operator-(const Vector3F& V) const
{
	return Vector3F(X - V.X, Y - V.Y, Z - V.Z);
}

Vector3F Math::Vector3F::operator-=(const Vector3F& V)
{
	X -= V.X;
	Y -= V.Y;
	Z -= V.Z;
	return *this;
}

Vector3F Math::Vector3F::operator*(const Vector3F& V) const
{
	return Vector3F(X * V.X, Y * V.Y, Z * V.Z);
}

Vector3F Math::Vector3F::operator*=(const Vector3F& V)
{
	X *= V.X;
	Y *= V.Y;
	Z *= V.Z;
	return *this;
}

Vector3F Math::Vector3F::operator/(const Vector3F& V) const
{
	return Vector3F(X / V.X, Y / V.Y, Z / V.Z);
}

Vector3F Math::Vector3F::operator/=(const Vector3F& V)
{
	X /= V.X;
	Y /= V.Y;
	Z /= V.Z;
	return *this;
}

bool Math::Vector3F::operator==(const Vector3F& V) const
{
	return X == V.X && Y == V.Y && Z == V.Z;
}

bool Math::Vector3F::operator!=(const Vector3F& V) const
{
	return X != V.X || Y != V.Y || Z != V.Z;
}
