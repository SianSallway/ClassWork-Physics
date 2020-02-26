#include "PhysicsScene.h"
#include <iostream>
#include <list>
#include "RigidBody.h"
#include "Sphere.h"
#include "Plane.h"
#include "Box.h"

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

		CheckForCollision();
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

//function pointer for collisions
typedef bool(*fn)(PhysicsObject*, PhysicsObject*);

//function array
static fn collisionFuncArray[] =
{
	PhysicsScene::plane2Plane, PhysicsScene::plane2Sphere, PhysicsScene::sphere2Plane, PhysicsScene::sphere2Sphere, PhysicsScene::box2Plane,
};

void PhysicsScene::CheckForCollision()
{
	int  actorCount = actors.size();

	//check for all collision against all objects except this one
	for (int outer = 0; outer < actorCount - 1; outer++)
	{
		for (int inner = outer + 1; inner < actorCount; inner++)
		{
			PhysicsObject* object1 = actors[outer];
			PhysicsObject* object2 = actors[inner];
			int shapeID1 = object1->GetShapeType();
			int shapeID2 = object2->GetShapeType();

			//use function pointers
			int functionIndex = (shapeID1 * SHAPE_COUNT) + shapeID2;
			fn collisionFuncPtr = collisionFuncArray[functionIndex];

			if (collisionFuncPtr != nullptr)
			{
				//check if a collision occured
				collisionFuncPtr(object1, object2);
			}
		}
	}
}

bool PhysicsScene::sphere2Sphere(PhysicsObject* obj1, PhysicsObject* obj2)
{
	Sphere* sphere1 = dynamic_cast<Sphere*>(obj1);
	Sphere* sphere2 = dynamic_cast<Sphere*>(obj2);

	//if cast successful test for collision
	if (sphere1 != nullptr && sphere2 != nullptr)
	{
		vec2 distance = sphere1->GetPosition() - sphere2->GetPosition();
		float distanceMag = distance.x * distance.x + distance.y * distance.y;

		float r = sphere1->GetRadius() + sphere2->GetRadius();

		if (distanceMag <= (r * r))
		{
			sphere1->ResolveCollision(sphere2, 0.5f * (sphere1->GetPosition() + sphere2->GetPosition()));

			return true;
		}
	}

	return false;
}

bool PhysicsScene::sphere2Plane(PhysicsObject* obj1, PhysicsObject* obj2)
{
	Sphere* sphere = dynamic_cast<Sphere*>(obj1);
	Plane* plane = dynamic_cast<Plane*>(obj2);

	//if cast successful test for collision
	if (sphere != nullptr && plane != nullptr)
	{
		vec2 collisionNormal = plane->GetNormal();
		float sphereToPlane = dot(sphere->GetPosition(), plane->GetNormal()) - plane->GetDistance();

		//if behind plane flip normal
		if (sphereToPlane < 0)
		{
			collisionNormal *= -1;
			sphereToPlane *= -1;
		}

		float intersection = sphere->GetRadius() - sphereToPlane;
		vec2 contact = sphere->GetPosition() + (collisionNormal * -sphere->GetRadius());

		if (intersection >= 0)
		{
			plane->ResolveCollision(sphere, contact);
			sphere->SetPosition(sphere->GetPosition() + (collisionNormal * intersection));

			return true;
		}
	}

	return false;
}

bool PhysicsScene::plane2Sphere(PhysicsObject* obj1, PhysicsObject* obj2)
{
	return sphere2Plane(obj2, obj1);
}

bool PhysicsScene::plane2Plane(PhysicsObject* obj1, PhysicsObject* obj2)
{
	return false;
}

bool PhysicsScene::box2Plane(PhysicsObject* obj1, PhysicsObject* obj2)
{
	Box* box = dynamic_cast<Box*>(obj1);
	Plane* plane = dynamic_cast<Plane*>(obj2);
	
	//if cast successful test for collision
	if (box != nullptr && plane != nullptr)
	{
		int numContacts = 0;
		vec2 contact = vec2(0, 0);
		float contactV = 0;
		float radius = 0.5f * fminf(box->GetWidth(), box->GetHeight());

		//left off here
	}
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