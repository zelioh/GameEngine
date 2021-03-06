#pragma once

#include "../Math/Vector3F.h"
#include "PhysicsEngine_public.h"

class PHYSICS_ENGINE_EXPORT IntersectData
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

