#pragma once

#include "Collider.h"

class Plane :public Collider
{
public:
	Plane(const Vector3F& normal, float distance);
	~Plane();

	Plane Normalized() const;

	const Vector3F& GetNormal() const { return normal; }
	float GetDistance() const { return distance; }

private:
	const Vector3F normal;
	const float    distance;
};

