#pragma once

#include "Collider.h"
#include "PhysicsEngine_public.h"

class PHYSICS_ENGINE_EXPORT PhysicsObject
{
public:
	PhysicsObject(Collider *Collider, const Math::Vector3F& Velocity);
	PhysicsObject(const PhysicsObject& other);
	~PhysicsObject();
	
	void Calculate(float DeltaTime);
    Math::Vector3F GetPosition() const { return position; };
    Math::Vector3F GetOldPosition() const { return oldPosition; };
    Math::Vector3F GetVelocity() const { return velocity; };
	const Collider& GetCollider();
	void SetPosition(const Math::Vector3F& Pos) { this->position = Pos; };
	void SetOldPosition(Math::Vector3F& OldPos) { this->oldPosition = OldPos; };
	void SetVelocity(Math::Vector3F& Velocity) { this->velocity = Velocity; };


private:
    Math::Vector3F position;
    Math::Vector3F velocity;
    Math::Vector3F oldPosition;
	Collider* collider;
};

