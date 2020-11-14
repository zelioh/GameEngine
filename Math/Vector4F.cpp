#include "Vector4F.h"
#include "Debug_utils.h"

using namespace Math;

Math::Vector4F::Vector4F()
{
	X = 0;
	Y = 0;
	Z = 0;
	W = 0;
}

Math::Vector4F::Vector4F(const float inX, const float inY, const float inZ, const float inW)
{
	this->X = inX;
	this->Y = inY;
	this->Z = inZ;
	this->W = inW;
}

Math::Vector4F::~Vector4F()
{
}

Vector4F Math::Vector4F::operator+(const Vector4F& V) const
{
	return Vector4F(X + V.X, Y + V.Y, Z + V.Z, W + V.W);
}

Vector4F Math::Vector4F::operator+=(const Vector4F& V)
{
	X += V.X; 
	Y += V.Y; 
	Z += V.Z; 
	W += V.W;
	return *this;
}

Vector4F Math::Vector4F::operator-(const Vector4F& V) const
{
	return Vector4F(X - V.X, Y - V.Y, Z - V.Z, W - V.W);
}

Vector4F Math::Vector4F::operator-=(const Vector4F& V)
{
	X -= V.X;
	Y -= V.Y;
	Z -= V.Z;
	W -= V.W;
	return *this;
}

Vector4F Math::Vector4F::operator*(const Vector4F& V) const
{
	return Vector4F(X * V.X, Y * V.Y, Z * V.Z, W * V.W);
}

Vector4F Math::Vector4F::operator*=(const Vector4F& V)
{
	X *= V.X;
	Y *= V.Y;
	Z *= V.Z;
	W *= V.W;
	return *this;
}

Vector4F Math::Vector4F::operator/(const Vector4F& V) const
{
    ASSERT_MESSAGE(V.X != 0.f, "Can't divide by 0");
    ASSERT_MESSAGE(V.Y != 0.f, "Can't divide by 0");
    ASSERT_MESSAGE(V.Z != 0.f, "Can't divide by 0");

	return Vector4F(X / V.X, Y / V.Y, Z / V.Z, W / V.W);
}

Vector4F Math::Vector4F::operator/=(const Vector4F& V)
{
    ASSERT_MESSAGE(V.X != 0.f, "Can't divide by 0");
    ASSERT_MESSAGE(V.Y != 0.f, "Can't divide by 0");
    ASSERT_MESSAGE(V.Z != 0.f, "Can't divide by 0");
    ASSERT_MESSAGE(V.W != 0.f, "Can't divide by 0");

	X /= V.X;
	Y /= V.Y;
	Z /= V.Z;
	W /= V.W;
	return *this;
}

bool Math::Vector4F::operator==(const Vector4F& V) const
{
	return ((X == V.X) && (Y == V.Y) && (Z == V.Z) && (W == V.W));
}

bool Math::Vector4F::operator!=(const Vector4F& V) const
{
	return ((X != V.X) || (Y != V.Y) || (Z != V.Z) || (W != V.W));
}

Vector4F Math::Vector4F::operator*(float scalar) const
{
    return Math::Vector4F(X * scalar, Y * scalar, Z * scalar, W * scalar);
}