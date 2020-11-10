#pragma once


#include "Collider.h"

using namespace Math;

class BoundingBox : public Collider
{
public:
	BoundingBox(const Vector3F& Position, const Vector3F& scale);
	~BoundingBox();

	IntersectData IntersectBoundingBox(const BoundingBox& other);
	virtual void Transform(const Vector3F& translation);
	virtual Vector3F GetCenter() const { return center; }


private:
	Vector3F center;
	const Vector3F m_scale;
};

