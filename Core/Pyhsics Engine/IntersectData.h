#pragma once
class IntersectData
{
public:
	IntersectData(const bool DoesIntersect, const float Distance);
	~IntersectData();

	bool GetDoesIntersect()const { return doesIntersect; };
	float GetDistance()const { return distance; };

private:
	float distance;
	bool doesIntersect;

};

