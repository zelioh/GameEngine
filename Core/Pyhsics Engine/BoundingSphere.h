#pragma once


#include "Collider.h"

using namespace Math;

class BoundingSphere : public Collider
{
public:
	BoundingSphere(const Vector3F& center, float radius);
	~BoundingSphere();

	IntersectData IntersectBoundingSphere(const BoundingSphere& other) const;

	virtual void Transform(const Vector3F& translation);
	virtual Vector3F GetCenter() const { return center; }

	float GetRadius()const { return radius; }
private:
	const Vector3F center;
	const float radius;

};

