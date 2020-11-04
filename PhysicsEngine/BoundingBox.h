#pragma once


#include "Collider.h"

using namespace Math;

class BoundingBox : public Collider
{
public:
	BoundingBox(const Vector3F& MinBoxExtent, const Vector3F& MaxBoxExtent);
	~BoundingBox();

	IntersectData IntersectBoundingBox(const BoundingBox& other);
	const Vector3F& getMaxBoxExtent() const { return MaxBoxExtent; };
	const Vector3F& getMinBoxExtent() const { return MinBoxExtent; };
	virtual void Transform(const Vector3F& translation);

private:
	const Vector3F MinBoxExtent;
	const Vector3F MaxBoxExtent;
};

