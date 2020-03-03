#include "PhysicsScene.h"
#include <iostream>
#include <list>
#include "RigidBody.h"
#include "Sphere.h"
#include "Plane.h"
#include "Box.h"
#include <algorithm>

using namespace std;
using namespace glm;

PhysicsScene::PhysicsScene() : timeStep(0.01f), gravity(vec2(0, 0))
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

//removes physics objects that were added my the player one by one
void PhysicsScene::RemoveActor()
{
	if (actors.back()->GetShapeType() != PLANE)
	{
		actors.pop_back();
	}	
}


bool PhysicsScene::isRemovalble(int j)
{

		if (actors[j]->GetShapeType() == SPHERE || actors[j]->GetShapeType() == BOX)
		{
			return true;
		}
		else if (actors[j]->GetShapeType() == PLANE)
		{
			return false;
		}


	
}

void PhysicsScene::RemoveAll()
{
	//bool removableShape;
	for (int i = 0; 1 < actors.size(); i++)
	{
		//remove(actors.begin(), actors.end(), isRemovalble(i));
	}


}

void PhysicsScene::ApplyContactForces(RigidBody* body1, RigidBody* body2, vec2 norm, float pen)
{
	float body1Factor;

	if (body1->IsKinematic())
	{
		body1Factor = 0;
	}

	if (body2->IsKinematic())
	{
		body1Factor = 1.0f;
	}
	else
	{
		body1Factor = 0.5f;
	}

	body1->SetPosition(body1->GetPosition() - body1Factor * norm * pen);
	body2->SetPosition(body2->GetPosition() + (1 - body1Factor) * norm * pen);
}


//function pointer for collisions
typedef bool(*fn)(PhysicsObject*, PhysicsObject*);

//function array
static fn collisionFuncArray[] =
{
	PhysicsScene::plane2Plane, PhysicsScene::plane2Sphere, PhysicsScene::plane2Box,
	PhysicsScene::sphere2Plane, PhysicsScene::sphere2Sphere, PhysicsScene::sphere2Box,
	PhysicsScene::box2Plane, PhysicsScene::box2Sphere, PhysicsScene::box2Box,	 
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
				/*RigidBody* obj1R = dynamic_cast<RigidBody*>(object1);
				RigidBody* obj2R = dynamic_cast<RigidBody*>(object2);

				//total kinetic engery before collision
				float kePre = obj1R->GetKineticEnergy() + obj2R->GetKineticEnergy();*/

				//check if a collision occured
				collisionFuncPtr(object1, object2);

				//total kinetic engery after collision
				/*float kePost = obj1R->GetKineticEnergy() + obj2R->GetKineticEnergy();

				float deltaKe = kePost - kePre;

				if (deltaKe < -0.01f || deltaKe > 0.01f)
				{
					cout << "Engery change detected" << endl;
				}*/


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
		float disLength = length(distance);
		//float distanceMag = distance.x * distance.x + distance.y * distance.y;
		float intersection = sphere1->GetRadius() + sphere2->GetRadius() - disLength;

		//float r = sphere1->GetRadius() + sphere2->GetRadius();
		//distanceMag <= (r * r)

		if (intersection > 0)
		{
			//adding contact forces so objects don't overlap 
			vec2 contactForce = 0.5f * (disLength - (sphere1->GetRadius() + sphere2->GetRadius())) * distance / disLength;

			sphere1->SetPosition(sphere1->GetPosition() - contactForce);
			sphere2->SetPosition(sphere2->GetPosition() + contactForce);
			
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
		float contactVel = 0;
		float radius = 0.5f * fminf(box->GetWidth(), box->GetHeight());
		float penetration = 0;

		//which side is the centre of mass (COM) on
		vec2 planeOrigin = plane->GetNormal() * plane->GetDistance();
		float comFromPlane = dot(box->GetPosition() - planeOrigin, plane->GetNormal());

		//check corners to see if they've hit the plane
		for (float x = -box->GetExtents().x; x < box->GetWidth(); x += box->GetWidth())
		{
			for (float y = -box->GetExtents().y; y < box->GetHeight(); y += box->GetHeight())
			{
				//get position of the corner in world space
				vec2 pos = box->GetPosition() + x * box->GetLocalX() + y * box->GetLocalY();

				float distanceFromPlane = dot(pos - planeOrigin, plane->GetNormal());

				//total velocity of the point
				float velIntoPlane = dot(box->GetVelocity() + box->GetAngularVelocity() * 
					(-y * box->GetLocalX() + x * box->GetLocalY()), plane->GetNormal());

				//if this corner is on the opposite side from the COM and moving further in the 
				//collision needs to be solved
				if ((distanceFromPlane > 0 && comFromPlane < 0 && velIntoPlane > 0) || (distanceFromPlane < 0 && comFromPlane > 0 && velIntoPlane < 0))
				{
					numContacts++;
					contact += pos;
					contactVel += velIntoPlane;

					//adding contact forces
					if (comFromPlane >= 0)
					{
						if (penetration > distanceFromPlane)
						{
							penetration = distanceFromPlane;
						}
						else
						{
							if (penetration < distanceFromPlane)
							{
								penetration = distanceFromPlane;
							}
						}
					}
				}
			}
		}

		//if contact has been made
		if (numContacts > 0)
		{
			//get avg collision velocity into plane
			float collisionVel = contactVel / (float)numContacts;

			//get acceleration to stop (0) or reverse (1) the avg velocity in place 
			vec2 acceleration = -plane->GetNormal() * ((1.0f + box->GetElasticity()) * collisionVel);

			//get avg position to apply the force to
			vec2 localContact = (contact / (float)numContacts) - box->GetPosition();

			//perpendicular distance we apply force at relative to the COM, Torque = F * r
			float r = dot(localContact, vec2(plane->GetNormal().y, -plane->GetNormal().x));

			// get the effective mass - this is a combination of moment of inertia and mass, and tells us how much the contact point velocity
			// will change with the force we're applying
			float mass0 = 1.0f / (1.0f / box->GetMass() + (r * r) / box->GetMoment());

			//apply the force
			box->ApplyForce(acceleration * mass0, localContact);

			//contact forces
			box->SetPosition(box->GetPosition() - plane->GetNormal() * penetration);
		}
	}
	else if (box == nullptr)
	{
		cout << "Box cast unsuccessful" << endl;
	}
	else if (plane == nullptr)
	{
		cout << "Plane cast unsuccessful" << endl;
	}
	else if (box == nullptr && plane == nullptr)
	{
		cout << "All casts unsuccessful" << endl;
	}

	return false;
}

bool PhysicsScene::box2Sphere(PhysicsObject* obj1, PhysicsObject* obj2)
{
	Box* box = dynamic_cast<Box*>(obj1);
	Sphere* sphere = dynamic_cast<Sphere*>(obj2);

	if (box != nullptr && sphere != nullptr)
	{
		vec2 spherePos = sphere->GetPosition() - box->GetPosition();

		float w2 = box->GetWidth() / 2;
		float h2 = box->GetHeight() / 2;

		int numContacts = 0;
		//contact is in our box coordinates
		vec2 contact = vec2(0, 0);

		//check the four corners to see if any of them are inside the sphere 
		for (float x = -w2; x <= w2; x += box->GetWidth())
		{
			for (float y = -h2; y <= h2; y += box->GetHeight())
			{
				vec2 pos = x * box->GetLocalX() + y * box->GetLocalY();
				vec2 dp = pos - spherePos;

				if (dp.x * dp.x + dp.y * dp.y < sphere->GetRadius() * sphere->GetRadius())
				{
					numContacts++;
					contact += vec2(x, y);
				}
			}
		}

		vec2* direction = nullptr;

		//get local position of sphere centre
		vec2 localPos = vec2(dot(box->GetLocalX(), spherePos), dot(box->GetLocalY(), spherePos));

		if (localPos.y < h2 && localPos.y > -h2)
		{
			if (localPos.x > 0 && localPos.x < w2 + sphere->GetRadius())
			{
				numContacts++;
				contact += vec2(w2, localPos.y);
				direction = new vec2(box->GetLocalX());
			}

			if (localPos.x < 0 && localPos.x > -(w2 + sphere->GetRadius()))
			{
				numContacts++;
				contact += vec2(-w2, localPos.y);
				direction = new vec2(-box->GetLocalX());
			}
		}

		if (localPos.x < w2 && localPos.x > -w2)
		{
			if (localPos.y > 0 && localPos.y < h2 + sphere->GetRadius())
			{
				numContacts++;
				contact += vec2(localPos.x, h2);
				direction = new vec2(box->GetLocalY());
			}

			if (localPos.y < 0 && localPos.y > -(h2 + sphere->GetRadius()))
			{
				numContacts++;
				contact += vec2(localPos.x, -h2);
				direction = new vec2(-box->GetLocalY());
			}
		}

		if (numContacts > 0)
		{
			//avg and convert back into world coords
			contact = box->GetPosition() + (1.0f / numContacts) *
				(box->GetLocalX() * contact.x + box->GetLocalY() * contact.y);

			box->ResolveCollision(sphere, contact, direction);

			float pen = sphere->GetRadius() - length(contact - sphere->GetPosition());

			vec2 normal = normalize(sphere->GetPosition() - contact);

			sphere->SetPosition(sphere->GetPosition() + normal * pen);
		}

		delete direction;
	}

	return false;
}

bool PhysicsScene::box2Box(PhysicsObject* obj1, PhysicsObject* obj2)
{
	Box* box1 = dynamic_cast<Box*>(obj1);
	Box* box2 = dynamic_cast<Box*>(obj2);

	if (box1 != nullptr && box2 != nullptr)
	{
		vec2 boxPos = box2->GetCenter() - box1->GetCenter();

		vec2 normal = vec2(0, 0);
		vec2 contact = vec2(0, 0);
		float pen = 0;
		int numContacts = 0;

		box1->CheckCorners(*box2, contact, numContacts, pen, normal);

		if (box2->CheckCorners(*box1, contact, numContacts, pen, normal))
		{
			normal = -normal;
		}

		if (pen > 0)
		{
			box1->ResolveCollision(box2, contact / (float)numContacts, &normal);
		}

		return true;
	}

	return false;
}

bool PhysicsScene::plane2Box(PhysicsObject* obj1, PhysicsObject* obj2)
{
	return box2Plane(obj2, obj1);
}

bool PhysicsScene::sphere2Box(PhysicsObject* obj1, PhysicsObject* obj2)
{
	return box2Sphere(obj2, obj1);
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