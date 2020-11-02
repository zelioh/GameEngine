#pragma once

#include "../Vector3F.h"

using namespace Math;

class IntersectData
{
public:
	IntersectData(const bool DoesIntersect, const Vector3F& Direction);
	~IntersectData();

	bool GetDoesIntersect()const { return doesIntersect; };
	float GetDistance()const { return direction.Length(); };
	const Vector3F GetDirection() const { return direction; };

private:
	Vector3F direction;
	bool doesIntersect;

};

