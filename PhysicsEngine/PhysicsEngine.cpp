#include "PhysicsEngine.h"
#include <iostream>
#include "Debug_utils.h"

PhysicsEngine::PhysicsEngine()
{
}

PhysicsEngine::~PhysicsEngine()
{
}

void PhysicsEngine::AddPhysicsObject(PhysicsObject * object)
{
	this->PhysicsObjectList.push_back(object);
}

void PhysicsEngine::Update(float DeltaTime)
{
	for (int i = 0; i < this->PhysicsObjectList.size(); i++) {
		this->PhysicsObjectList[i]->Calculate(DeltaTime);
		DEBUG_MESSAGE("Object : " + std::to_string(i) + "  " + "  X = " +
		                std::to_string(this->PhysicsObjectList[i]->GetPosition().X) +
                                  "  Y = " + std::to_string(this->PhysicsObjectList[i]->GetPosition().Y) +
                                  "  Z = " + std::to_string(this->PhysicsObjectList[i]->GetPosition().Z));
	}
}

void PhysicsEngine::CollisionHandler()
{
	for (int i = 0; i < PhysicsObjectList.size(); i++) {
		for (int j = i + 1; j < PhysicsObjectList.size(); j++) {
			IntersectData intersectData = PhysicsObjectList[i]->GetCollider().Intersect(PhysicsObjectList[j]->GetCollider());
			
			if (intersectData.GetDoesIntersect()){
                DEBUG_MESSAGE("Collison Happened");
				if (PhysicsObjectList[i]->GetCollider().GetColliderType() == Collider::COLLIDER_SPHERE
					&& PhysicsObjectList[j]->GetCollider().GetColliderType() == Collider::COLLIDER_SPHERE) {
					
					Vector3F direction = intersectData.GetDirection().Normalized();
					Vector3F otherDirection = Vector3F(direction.Reflection(PhysicsObjectList[i]->GetVelocity().Normalized()));
					PhysicsObjectList[i]->SetVelocity(Vector3F(PhysicsObjectList[i]->GetVelocity().Reflection(otherDirection)));
					PhysicsObjectList[j]->SetVelocity(Vector3F(PhysicsObjectList[j]->GetVelocity().Reflection(direction)));
				}
				
				if (PhysicsObjectList[i]->GetCollider().GetColliderType() == Collider::COLLIDER_BOX 
					&& PhysicsObjectList[j]->GetCollider().GetColliderType() == Collider::COLLIDER_BOX) {
					Vector3F tempvel = PhysicsObjectList[i]->GetVelocity();
					PhysicsObjectList[i]->SetVelocity(Vector3F(PhysicsObjectList[j]->GetVelocity()));
					PhysicsObjectList[j]->SetVelocity(tempvel);
				}
			}
		}
	}
}
