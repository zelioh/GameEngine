#pragma once

#include <vector>
#include "PhysicsObject.h"

class PhysicsEngine
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

