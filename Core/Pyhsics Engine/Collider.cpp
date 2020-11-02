#include "Collider.h"
#include "BoundingBox.h"
#include "BoundingSphere.h"

Collider::Collider(int Collider_type) : ColliderType(Collider_type)
{
}

Collider::~Collider()
{
}

IntersectData Collider::Intersect(const Collider& other) const
{
	if (ColliderType == COLLIDER_SPHERE && other.GetColliderType() == COLLIDER_SPHERE)
	{
		BoundingSphere* self = (BoundingSphere*)this;
		return self->IntersectBoundingSphere((BoundingSphere&)other);
	}

	if (ColliderType == COLLIDER_BOX && other.GetColliderType() == COLLIDER_BOX) {
		BoundingBox* self = (BoundingBox*)this;
		return self->IntersectBoundingBox((BoundingBox&)other);
	}
	// add other Collider


	return IntersectData(false, 0);
}
