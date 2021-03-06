#pragma once

#include "Collider.h"
#include "BoundingBox.h"
#include "BoundingSphere.h"

#include "PhysicsEngine_public.h"

class PHYSICS_ENGINE_EXPORT Plane :public Collider
{
public:
	Plane(const Vector3F& normal, float distance);
	~Plane();

	Plane Normalized() const;
	IntersectData IntersectBoundingSphere(const BoundingSphere& other);
	IntersectData IntersectBoundingBox(const BoundingBox& other);

	//getter
	const Vector3F& GetNormal() const { return m_normal; }
	float GetDistance() const { return m_distance; }
	virtual void Transform(const Vector3F& translation) {}
	virtual Vector3F GetCenter() const { return Vector3F(0, 0, 0); }

private:
	Vector3F m_normal;
	float    m_distance;
};

