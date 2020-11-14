#pragma once

#include "Collider.h"
#include "PhysicsEngine_public.h"

using namespace Math;

class PHYSICS_ENGINE_EXPORT BoundingSphere : public Collider
{
public:
	BoundingSphere(const Vector3F& center, float radius);
	~BoundingSphere();

	IntersectData IntersectBoundingSphere(const BoundingSphere& other) const;

	virtual void Transform(const Vector3F& translation);
	virtual Vector3F GetCenter() const { return center; }

	float GetRadius()const { return radius; }
private:
	Vector3F center;
	const float radius;

};

