#include "PhysicsEngine.h"
#include "Collider.h"
#include "BoundingSphere.h"
#include <iostream>
#include <chrono>
#include <thread>

int main(void) {
	PhysicsEngine physicsEngineInstance;

	physicsEngineInstance.AddPhysicsObject(PhysicsObject(new BoundingSphere(Vector3F(0.0f, 0.0f, 0.0f), 1.0f), Vector3F(0.1f, 0.0f, 0.0f)));

	physicsEngineInstance.AddPhysicsObject(PhysicsObject(new BoundingSphere(Vector3F(10.0f, 0.0f, 0.0f), 1.0f), Vector3F(-0.1f, 0.0f, 0.0f)));

	while (true)
	{
		//std::cout << "Update";
		//printf("Update");
		physicsEngineInstance.CollisionHandler();
		physicsEngineInstance.Update(2);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}