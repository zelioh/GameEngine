#include "IntersectData.h"

IntersectData::IntersectData(const bool DoesIntersect, const Math::Vector3F& Direction):
doesIntersect(DoesIntersect),
direction(Direction)
{
}

IntersectData::~IntersectData()
{
}
