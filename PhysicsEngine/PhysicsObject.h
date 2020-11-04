#pragma once

#include "Collider.h"

using namespace Math;

class PhysicsObject
{
public:
	PhysicsObject(Collider *Collider, Vector3F& Velocity);
	PhysicsObject(const PhysicsObject& other);
	~PhysicsObject();
	
	void Calculate(float DeltaTime);
	Vector3F GetPosition() const { return position; };
	Vector3F GetOldPosition() const { return oldPosition; };
	Vector3F GetVelocity() const { return velocity; };
	const Collider& GetCollider();
	void SetPosition(Vector3F& Pos) { this->position = Pos; };
	void SetOldPosition(Vector3F& OldPos) { this->oldPosition = OldPos; };
	void SetVelocity(Vector3F& Velocity) { this->velocity = Velocity; };


private:
	Vector3F position;
	Vector3F velocity;
	Vector3F oldPosition;
	Collider* collider;
};

