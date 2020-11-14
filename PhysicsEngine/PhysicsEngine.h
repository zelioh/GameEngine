#pragma once

#include <vector>
#include "PhysicsObject.h"

#include "PhysicsEngine_public.h"

class PHYSICS_ENGINE_EXPORT PhysicsEngine
{
public:
	PhysicsEngine();
	~PhysicsEngine();

	void AddPhysicsObject(PhysicsObject * object);
	void Update(float DeltaTime);
	void CollisionHandler();

	PhysicsObject * GetPhysicsObject(int index) { return PhysicsObjectList[index]; }

private:
	std::vector<PhysicsObject *> PhysicsObjectList;

};

