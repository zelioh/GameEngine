#include "PhysicsEngine.h"

PhysicsEngine::PhysicsEngine()
{
}

PhysicsEngine::~PhysicsEngine()
{
}

void PhysicsEngine::AddPhysicsObject(const PhysicsObject& object)
{
	this->PhysicsObjectList.push_back(object);
}

void PhysicsEngine::Update(float DeltaTime)
{
	for (int i = 0; i < this->PhysicsObjectList.size(); i++) {
		this->PhysicsObjectList[i].Calculate(DeltaTime);
	}
}

void PhysicsEngine::CollisionHandler()
{
}
