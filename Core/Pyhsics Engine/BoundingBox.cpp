#include "BoundingBox.h"

BoundingBox::BoundingBox(const Vector3F& MinBoxExtent, const Vector3F& MaxBoxExtent) : 
	MinBoxExtent(MinBoxExtent), MaxBoxExtent(MaxBoxExtent), Collider(Collider::COLLIDER_BOX)
{
}

BoundingBox::~BoundingBox()
{

}

IntersectData BoundingBox::IntersectBoundingBox(const BoundingBox& other)
{
	Vector3F distances1 = other.getMinBoxExtent() - MaxBoxExtent;
	Vector3F distances2 = MinBoxExtent - other.getMaxBoxExtent();
	Vector3F distances = Vector3F(distances1.Max(distances2));
	float maxDistance = distances.Max();
	return IntersectData(maxDistance < 0, maxDistance);
}

void BoundingBox::Transform(const Vector3F& translation)
{
}
