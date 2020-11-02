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
