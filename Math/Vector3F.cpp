#include "Vector3F.h"
#include "Debug_utils.h"
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

Vector3F Math::Vector3F::operator*(float scalar) const
{
    return Vector3F(X * scalar, Y * scalar, Z * scalar);
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
    ASSERT_MESSAGE(V.X != 0.f, "Can't divide by 0");
    ASSERT_MESSAGE(V.Y != 0.f, "Can't divide by 0");
    ASSERT_MESSAGE(V.Z != 0.f, "Can't divide by 0");

	return Vector3F(X / V.X, Y / V.Y, Z / V.Z);
}

Vector3F Math::Vector3F::operator/(float scalar) const
{
    ASSERT_MESSAGE(scalar != 0.f, "Can't divide by 0");

    return (0.f == scalar) ? Vector3F(0.f, 0.f, 0.f) : Vector3F(X / scalar, Y / scalar, Z / scalar);
}

Vector3F Math::Vector3F::operator/=(const Vector3F& V)
{
    ASSERT_MESSAGE(V.X != 0.f, "Can't divide by 0");
    ASSERT_MESSAGE(V.Y != 0.f, "Can't divide by 0");
    ASSERT_MESSAGE(V.Z != 0.f, "Can't divide by 0");

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

float Math::Vector3F::Max() const
{
	float MaxValue = this->X;
	MaxValue = MaxValue > this->Y ? MaxValue : this->Y;
	MaxValue = MaxValue > this->Z ? MaxValue : this->Z;

	return MaxValue;
}

Vector3F Math::Vector3F::Max(const Vector3F& value) const
{
	float MaxX = this->X > value.X ? this->X : value.X;
	float MaxY = this->Y > value.Y ? this->Y : value.Y;
	float MaxZ = this->Z > value.Z ? this->Z : value.Z;
	return Vector3F(MaxX, MaxY, MaxZ);
}

Vector3F Math::Vector3F::Normalized() const
{
		float length = Length();
		return Vector3F(X / length, Y / length, Z / length);
}

Vector3F Math::Vector3F::Reflection(Vector3F& normal) const
{
	Vector3F temp = *this - (normal * (this->Dot(normal) * 2));
	return temp;
}
