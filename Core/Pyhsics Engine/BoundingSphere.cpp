#include "BoundingSphere.h"

BoundingSphere::BoundingSphere(const Vector3F& center, float radius) : center(center), radius(radius), Collider(Collider::COLLIDER_SPHERE)
{
}

BoundingSphere::~BoundingSphere()
{
}

IntersectData BoundingSphere::IntersectBoundingSphere(const BoundingSphere& other) const
{
	float radiusDistance = radius + other.GetRadius(); 
	// calculate distance between 2 center
	float centerDistance = (other.GetCenter() - center).Length();

	float distance = centerDistance - radiusDistance;

	return IntersectData(distance < 0, distance);
}

void BoundingSphere::Transform(const Vector3F& translation)
{
}
