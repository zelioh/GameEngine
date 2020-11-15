#include "PhysicsEngine.h"
#include "Collider.h"
#include "BoundingSphere.h"
#include "BoundingBox.h"
#include <iostream>
#include <chrono>
#include <thread>

int main(void) {
	PhysicsEngine physicsEngineInstance;

	physicsEngineInstance.AddPhysicsObject(new PhysicsObject(new BoundingBox(Vector3F(0.0f, 0.0f, 0.0f), Vector3F(1.0f, 1.0f, 1.0f)), Vector3F(1.0f, 1.0f, 1.0f)));

	physicsEngineInstance.AddPhysicsObject(new PhysicsObject(new BoundingBox(Vector3F(10.0f, 10.0f, 10.0f), Vector3F(1.0f, 1.0f, 1.0f)), Vector3F(-1.0f, -1.0f, -1.0f)));

	while (true)
	{
		//std::cout << "Update";
		//printf("Update");
		physicsEngineInstance.Update(1);
		physicsEngineInstance.CollisionHandler();

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}