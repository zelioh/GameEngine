#include "BoundingBox.h"
#include <iostream>

BoundingBox::BoundingBox(const Vector3F& Position, const Vector3F& scale) : 
	center(Position), m_scale(scale), Collider(Collider::COLLIDER_BOX)
{
}

BoundingBox::~BoundingBox()
{

}

IntersectData BoundingBox::IntersectBoundingBox(const BoundingBox& other)
{
	Vector3F distances1 = (other.center - other.m_scale) - (this->center + this->m_scale);//other.getMinBoxExtent() - this->getMaxBoxExtent();
	Vector3F distances2 = (this->center - this->m_scale) - (other.center + other.m_scale); //this->getMinBoxExtent() - other.getMaxBoxExtent();
	Vector3F distances = Vector3F(distances1.Max(distances2));
	float maxDistance = distances.Max();
	return IntersectData(maxDistance < 0, distances);
}

void BoundingBox::Transform(const Vector3F& translation)
{
	this->center += translation;
}
