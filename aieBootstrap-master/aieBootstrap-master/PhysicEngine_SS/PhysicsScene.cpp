#include "PhysicsScene.h"
#include <iostream>
#include <list>
#include "RigidBody.h"

using namespace std;

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

		//check for collisions 
		for (auto pActor : actors)
		{
			for (auto pOther : actors)
			{
				if (pActor == pOther)
				{
					continue;
				}

				if (find(dirty.begin(), dirty.end(), pActor) != dirty.end() && find(dirty.begin(), dirty.end(), pOther) != dirty.end())
				{
					continue;
				}

				RigidBody* pRigid = dynamic_cast<RigidBody*>(pActor);

				if (pRigid->CheckCollision(pOther) == true)
				{
					//combined mass of two spheres
					float comMass = (pRigid->GetMass() * dynamic_cast<RigidBody*>(pOther)->GetMass()) / (pRigid->GetMass() + dynamic_cast<RigidBody*>(pOther)->GetMass()) * 0.5;
					
					//relative velocity of two spheres
					glm::vec2 relVel = pRigid->GetVelocity() - dynamic_cast<RigidBody*>(pOther)->GetVelocity();

					glm::vec2 impact = glm::normalize(dynamic_cast<RigidBody*>(pOther)->GetPosition() - pRigid->GetPosition());

					float transmittedForce = glm::dot(relVel, impact);

					//addforcetoactor(pOther, relative velocity * combinedmass
					pRigid->ApplyForceToActor(dynamic_cast<RigidBody*>(pOther), relVel * transmittedForce * comMass);
					
					//one solution
					//pRigid->ApplyForceToActor(dynamic_cast<RigidBody*>(pOther), pRigid->GetVelocity() * pRigid->GetMass() + dynamic_cast<RigidBody*>(pOther)->GetMass());

					dirty.push_back(pRigid);
					dirty.push_back(pOther);
				}
			}
		}
		dirty.clear();
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
	PhysicsScene::plane2Plane, PhysicsScene::plane2Sphere, PhysicsScene::sphere2Plane, PhysicsScene::sphere2Sphere,
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