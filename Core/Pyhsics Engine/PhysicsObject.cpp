#include "PhysicsObject.h"

PhysicsObject::PhysicsObject(Vector3F& Velocity, Collider* Collider) : velocity(Velocity), collider(Collider), position(Collider->GetCenter()), oldPosition(Collider->GetCenter())
{
}

PhysicsObject::PhysicsObject(const PhysicsObject& other) : velocity(other.velocity), collider(other.collider), position(other.position), oldPosition(other.oldPosition)
{
}

PhysicsObject::~PhysicsObject()
{
}

void PhysicsObject::Calculate(float DeltaTime)
{
	// calculate new position 
	this->position += this->velocity * DeltaTime;
}


