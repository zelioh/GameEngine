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
	//std::cout << "other min extent  : X = " << other.getMinBoxExtent().X << " Y = " << other.getMinBoxExtent().Y << " Z = " << other.getMinBoxExtent().Z << std::endl;

	//std::cout << "this max extent  : X = " << this->getMaxBoxExtent().X << " Y = " << this->getMaxBoxExtent().Y << " Z = " << this->getMaxBoxExtent().Z << std::endl;

	std::cout << "distance 1 : X = " << distances1.X << " Y = " << distances1.Y << " Z = " << distances1.Z << std::endl;
	std::cout << "distance 2 : X = " << distances2.X << " Y = " << distances2.Y << " Z = " << distances2.Z << std::endl;
	Vector3F distances = Vector3F(distances1.Max(distances2));
	std::cout << "distance compute : X = " << distances.X << " Y = " << distances.Y << " Z = " << distances.Z << std::endl;
	float maxDistance = distances.Max();
	std::cout << " max distance = " << maxDistance << std::endl;
	return IntersectData(maxDistance <= 0, distances);
}

const Vector3F& BoundingBox::getMaxBoxExtent() const
{
	return this->center + this->m_scale;
}

const Vector3F& BoundingBox::getMinBoxExtent() const
{
	return this->center - this->m_scale;
}


void BoundingBox::Transform(const Vector3F& translation)
{
	this->center += translation;
}
