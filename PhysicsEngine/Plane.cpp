#include "Plane.h"

Plane::Plane(const Vector3F& normal, float distance) : m_normal(normal), m_distance(distance), Collider(Collider::COLLIDER_PLANE)
{
	float magnitude = normal.Length();

	m_normal = m_normal / magnitude;
	m_distance = m_distance / magnitude;
}

Plane::~Plane()
{
}

Plane Plane::Normalized() const
{
	float magnitude = m_normal.Length();

	return Plane(m_normal / magnitude, m_distance / magnitude);
}

IntersectData Plane::IntersectBoundingSphere(const BoundingSphere& other)
{
	float distanceFromSphereCenter = (float)fabs(m_normal.Dot(other.GetCenter()) + m_distance);
	float distanceFromSphere = distanceFromSphereCenter - other.GetRadius();

	return IntersectData(distanceFromSphere < 0, m_normal * distanceFromSphere);
}

IntersectData Plane::IntersectBoundingBox(const BoundingBox& other)
{
	//Calculate distance between Box and Plane
	return IntersectData(false, Vector3F(0,0,0));
}
