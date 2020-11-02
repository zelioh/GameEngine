#include "Plane.h"

Plane::Plane(const Vector3F& normal, float distance) : normal(normal), distance(distance), Collider(Collider::COLLIDER_PLANE)
{
}

Plane::~Plane()
{
}

Plane Plane::Normalized() const
{
	float magnitude = normal.Length();

	return Plane(normal / magnitude, distance / magnitude);
}

IntersectData Plane::IntersectBoundingSphere(const BoundingSphere& other)
{
	float distanceFromSphereCenter = (float)fabs(normal.Dot(other.GetCenter()) + distance);
	float distanceFromSphere = distanceFromSphereCenter - other.GetRadius();

	return IntersectData(distanceFromSphere < 0, normal * distanceFromSphere);
}

IntersectData Plane::IntersectBoundingBox(const BoundingBox& other)
{
	//Calculate distance between Box and Plane
	return IntersectData(false, Vector3F(0,0,0));
}
