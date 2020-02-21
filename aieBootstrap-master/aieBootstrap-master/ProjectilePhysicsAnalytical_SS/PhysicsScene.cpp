#include "PhysicsScene.h"
#include <iostream>
#include <list>
#include "RigidBody.h"
#include "Sphere.h"

using namespace std;
using namespace glm;

PhysicsScene::PhysicsScene() : timeStep(0.01f), gravity(glm::vec2(0, 0))
{
}

PhysicsScene::~PhysicsScene()
{
	for (auto pActor : actors)
	{
		delete pActor;
	}
}

//updates physical simulation, calls update function of each actor, handles collison detection and response 
void PhysicsScene::Update(float deltaTime)
{
	static std::list<PhysicsObject*> dirty;

	//update physics at a fixed time step
	static float accumulatedTime = 0.0f;
	accumulatedTime += deltaTime;

	while (accumulatedTime >= timeStep)
	{
		for (auto pActor : actors)
		{
			pActor->FixedUpdate(gravity, timeStep);
		}

		accumulatedTime -= timeStep;
	}
}

//handles the drawing of physical objects 
void PhysicsScene::UpdateGizmos()
{
	for (auto pActor : actors)
	{
		pActor->MakeGizmo();
	}
}

//adds PhysicsObject pointer to the end of the actors vector
void PhysicsScene::AddActor(PhysicsObject* actor)
{
	actors.push_back(actor);
}

//removes PhysicsObject pointer from the end of the actors vector
void PhysicsScene::RemoveActor(PhysicsObject* actor)
{
	actors.pop_back();
}

//calls debug function of each actor
void PhysicsScene::DebugScene()
{
	int count = 0;

	for (auto pActor : actors)
	{
		cout << count << " : ";
		pActor->Debug();
		count++;
	}
}