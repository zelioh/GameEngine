#include "PhysicsObject.h"

using namespace Math;

PhysicsObject::PhysicsObject(Collider* Collider, const Vector3F& Velocity):
velocity(Velocity),
collider(Collider),
position(Collider->GetCenter()),
oldPosition(Collider->GetCenter())
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

const Collider& PhysicsObject::GetCollider()
{
	Vector3F translation = position - oldPosition;
	//Update old position
	oldPosition = position;
	//Move collider by distance moved.
	collider->Transform(translation);
	return *collider;
}


