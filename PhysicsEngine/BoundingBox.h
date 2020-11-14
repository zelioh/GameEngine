#pragma once

#include "Collider.h"
#include "PhysicsEngine_public.h"

class PHYSICS_ENGINE_EXPORT BoundingBox : public Collider
{
public:
	BoundingBox(const Math::Vector3F& Position, const Math::Vector3F& scale);
	~BoundingBox();

	IntersectData IntersectBoundingBox(const BoundingBox& other);
	virtual void Transform(const Math::Vector3F& translation);
	virtual Math::Vector3F GetCenter() const { return center; }


private:
	Math::Vector3F center;
	const Math::Vector3F m_scale;
};

