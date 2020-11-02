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
	float centerDistance = (other.GetCenter() - center).Length();
	float distance = direction.Length();
	direction = direction / centerDistance;

	return IntersectData(distance < 0, direction * distance);
}

void BoundingSphere::Transform(const Vector3F& translation)
{
	center += translation;
}
