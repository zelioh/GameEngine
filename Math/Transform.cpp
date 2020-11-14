#include "Transform.h"

Math::Transform::Transform()
{
	this->Position = Vector3F(0, 0, 0);
	this->Rotation = Vector3F(0, 0, 0);
	this->Scale = Vector3F(0, 0, 0);
	this->Weight = 0;
}

Math::Transform::Transform(const Vector3F inPosition, const Vector3F inRotation, const Vector3F inScale, const int inWeight)
{
	this->Position = inPosition;
	this->Rotation = inRotation;
	this->Scale = inScale;
	this->Weight = inWeight;
}

Math::Transform::~Transform()
{
}
