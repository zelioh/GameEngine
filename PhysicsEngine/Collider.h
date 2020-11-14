#pragma once

#include "IntersectData.h"
#include "../Math/Vector3F.h"
#include "PhysicsEngine_public.h"

using namespace Math;

class PHYSICS_ENGINE_EXPORT Collider
{
public:
	enum {
		COLLIDER_BOX,
		COLLIDER_SPHERE,
		COLLIDER_PLANE
	};

public:
	Collider(int Collider_type);
	~Collider();

	IntersectData Intersect(const Collider& other) const;
	virtual void Transform(const Vector3F& translation) {}
	virtual Vector3F GetCenter() const { return Vector3F(0, 0, 0); }
	int GetColliderType() const { return ColliderType; }

private:
	int ColliderType;
};

