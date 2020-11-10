#pragma once

#include "Vector3F.h"

class IntersectData
{
public:
	IntersectData(const bool DoesIntersect, const Math::Vector3F& Direction);
	~IntersectData();

	bool GetDoesIntersect()const { return doesIntersect; };
	float GetDistance()const { return direction.Length(); };
	const Math::Vector3F GetDirection() const { return direction; };

private:
	Math::Vector3F direction;
	bool doesIntersect;

};

