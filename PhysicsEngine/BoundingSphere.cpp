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
	Vector3F direction = (other.GetCenter() - center);
	float centerDistance = direction.Length();
	direction = direction / centerDistance;
	float distance = centerDistance - radiusDistance;


	return IntersectData(distance < 0, direction * distance);
}

void BoundingSphere::Transform(const Vector3F& translation)
{
	center += translation;
}
