#pragma once

#include "Collider.h"
#include "BoundingBox.h"
#include "BoundingSphere.h"

class Plane :public Collider
{
public:
	Plane(const Vector3F& normal, float distance);
	~Plane();

	Plane Normalized() const;
	IntersectData IntersectBoundingSphere(const BoundingSphere& other);
	IntersectData IntersectBoundingBox(const BoundingBox& other);

	//getter
	const Vector3F& GetNormal() const { return normal; }
	float GetDistance() const { return distance; }

private:
	const Vector3F normal;
	const float    distance;
};

