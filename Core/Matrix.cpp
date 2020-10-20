#include "Matrix.h"

Math::Matrix::Matrix()
{
	this->X = Vector4F(0, 0, 0, 0);
	this->Y = Vector4F(0, 0, 0, 0);
	this->Z = Vector4F(0, 0, 0, 0);
	this->W = Vector4F(0, 0, 0, 0);
}

Math::Matrix::Matrix(const Vector4F& InX, const Vector4F& InY, const Vector4F& InZ, const Vector4F& InW)
{
	this->X = InX;
	this->Y = InY;
	this->Z = InZ;
	this->W = InW;

}

Math::Matrix::~Matrix()
{
}

Matrix Math::Matrix::operator*(const Matrix& Other) const
{
	return Matrix();
}

void Math::Matrix::operator*=(const Matrix& Other)
{
}

Matrix Math::Matrix::operator+(const Matrix& Other) const
{
	return Matrix();
}

void Math::Matrix::operator+=(const Matrix& Other)
{
}

bool Math::Matrix::operator==(const Matrix& Other) const
{
	return false;
}

bool Math::Matrix::operator!=(const Matrix& Other) const
{
	return false;
}
