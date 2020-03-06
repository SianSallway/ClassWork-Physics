#include "Sphere.h"
#include <iostream>
#include <Gizmos.h>
#include "Plane.h"

using namespace std;
using namespace glm;

Sphere::Sphere(glm::vec2 pos, glm::vec2 vel, float sphereRadius, float sphereMass, float seg, glm::vec4 objectColour, bool kinematic) : RigidBody(SPHERE, pos, vel, 0, sphereMass, kinematic)
{
	radius = sphereRadius;
	colour = objectColour;
	segments = seg;
	moment = 0.5f * mass * radius * radius;
	//cout << "moment:" << moment << endl;
}

void Sphere::MakeGizmo()
{	
	vec2 end = glm::vec2(cos(rotation), sin(rotation)) * radius;
	
	aie::Gizmos::add2DCircle(position, radius, segments, colour);
	aie::Gizmos::add2DLine(position, position + end, glm::vec4(1, 1, 1, 1));
}

bool Sphere::CheckCollision(PhysicsObject* pOther)
{
	Sphere* otherSphere = dynamic_cast<Sphere*>(pOther);

	if (!otherSphere == NULL)
	{
		float distance = glm::distance(position, otherSphere->position);

		float r = radius * otherSphere->radius;
		
		if (distance < r)
		{
			return true;
			cout << "Spheres have collided" << endl;
		}
		else
		{
			return false;
		}
	}
	else
	{
		cout << "No collision with sphere" << endl;
	}
}