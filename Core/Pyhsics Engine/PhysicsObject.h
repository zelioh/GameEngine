#pragma once

#include "Collider.h"

using namespace Math;

class PhysicsObject
{
public:
	PhysicsObject(Vector3F& Velocity ,Collider *Collider);
	PhysicsObject(const PhysicsObject& other);
	~PhysicsObject();
	
	void Calculate(float DeltaTime);
	Vector3F GetPosition() const { return position; };
	Vector3F GetOldPosition() const { return oldPosition; };
	Vector3F GetVelocity() const { return velocity; };
	void SetPosition(Vector3F& Pos) { this->position = Pos; };
	void SetOldPosition(Vector3F& OldPos) { this->oldPosition = OldPos; };
	void SetVelocity(Vector3F& Velocity) { this->velocity = Velocity; };


private:
	Vector3F position;
	Vector3F velocity;
	Vector3F oldPosition;
	Collider* collider;
};

