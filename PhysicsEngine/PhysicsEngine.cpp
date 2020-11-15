#include "PhysicsEngine.h"
#include <iostream>

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
        std::cout << "Object : " << i << "  " <<"  X = " <<this->PhysicsObjectList[i]->GetPosition().X <<
                  "  Y = " << this->PhysicsObjectList[i]->GetPosition().Y <<
                  "  Z = " << this->PhysicsObjectList[i]->GetPosition().Z << "\n\n";
	}
}

void PhysicsEngine::CollisionHandler()
{
	for (int i = 0; i < PhysicsObjectList.size(); i++) {
		for (int j = i + 1; j < PhysicsObjectList.size(); j++) {
			IntersectData intersectData = PhysicsObjectList[i]->GetCollider().Intersect(PhysicsObjectList[j]->GetCollider());

			if (intersectData.GetDoesIntersect()){
				std::cout << "Collison Happened\n";
				Vector3F direction = intersectData.GetDirection().Normalized();
				Vector3F otherDirection = Vector3F(direction.Reflection(PhysicsObjectList[i]->GetVelocity().Normalized()));
				PhysicsObjectList[i]->SetVelocity(Vector3F(PhysicsObjectList[i]->GetVelocity().Reflection(otherDirection)));
				PhysicsObjectList[j]->SetVelocity(Vector3F(PhysicsObjectList[j]->GetVelocity().Reflection(direction)));
			}
		}
	}
}
