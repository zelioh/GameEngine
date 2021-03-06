#include "Vector2F.h"
#include "Debug_utils.h"

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


Math::Vector2F Math::Vector2F::operator+(const Vector2F& V) const
{
	return Vector2F(X + V.X, Y + V.Y);
}

Math::Vector2F Math::Vector2F::operator+=(const Vector2F& V)
{
	X += V.X; 
	Y += V.Y;
	return *this;
}

Math::Vector2F Math::Vector2F::operator-(const Vector2F& V) const
{
	return Vector2F(X - V.X, Y - V.Y);
}

Math::Vector2F Math::Vector2F::operator-=(const Vector2F& V)
{
	X -= V.X;
	Y -= V.Y;
	return *this;
}

Math::Vector2F Math::Vector2F::operator*(const Vector2F& V) const
{
	return Vector2F(X * V.X, Y * V.Y);
}

Math::Vector2F Math::Vector2F::operator*=(const Vector2F& V)
{
	X *= V.X; 
	Y *= V.Y;
	return *this;
}

Math::Vector2F Math::Vector2F::operator/(const Vector2F& V) const
{
    ASSERT_MESSAGE(V.X != 0.f, "Can't divide by 0");
    ASSERT_MESSAGE(V.Y != 0.f, "Can't divide by 0");

	return Vector2F(X / V.X, Y / V.Y);
}

Math::Vector2F Math::Vector2F::operator/=(const Vector2F& V)
{
    ASSERT_MESSAGE(V.X != 0.f, "Can't divide by 0");
    ASSERT_MESSAGE(V.Y != 0.f, "Can't divide by 0");

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
