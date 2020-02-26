#include "Plane.h"
#include "Sphere.h"
#include <Gizmos.h>
#include <iostream>

using namespace std;

Plane::Plane(vec2 planeNormal, float distance, vec4 planeColour) : PhysicsObject(ShapeType::PLANE) //: RigidBody(ShapeType::PLANE, normal, vec2(0,0), 0, 0)
{
	normal = normalize(planeNormal);
	distanceToOrigin = distance;
	colour = planeColour;
}

/*Plane::Plane() : PhysicsObject(ShapeType::PLANE)
{
	normal = vec2(0, 1);
	distanceToOrigin = 0;
}*/

void Plane::FixedUpdate(vec2 gravity, float timeStep)
{

}

void Plane::ResetPosition()
{
	distanceToOrigin = this->GetDistance();
}

void Plane::ResolveCollision(RigidBody* actor2, vec2 contact)
{
	/*float elasticity = 1;
	vec2 newVelocity = actor2->GetVelocity() - dot((1 + elasticity) * actor2->GetVelocity(), normal) * normal;

	actor2->SetVelocity(newVelocity);*/

	vec2 relVel = actor2->GetVelocity();
	float elasticity = actor2->GetElasticity();
	float j = dot(-(1 + elasticity) * (relVel), normal / (1 / actor2->GetMass()));

	vec2 force = normal * j;

	actor2->ApplyForce(force, contact - actor2->GetPosition());
}

bool Plane::CheckCollision(PhysicsObject* pOther)
{
	Sphere* otherSphere = dynamic_cast<Sphere*>(pOther);

	if (otherSphere != NULL)
	{
		vec2 collisionNormal = GetNormal();
		float sphereToPlane = dot(otherSphere->GetPosition(), GetNormal()) - GetDistance();

		//if behind plane flip normal
		if (sphereToPlane < 0)
		{
			collisionNormal *= -1;
			sphereToPlane *= -1;
		}

		float intersection = otherSphere->GetRadius() - sphereToPlane;

		if (intersection > 0)
		{
			cout << "Sphere and plane have collided" << endl;
			return true;
		}
	}

	cout << "Sphere and plane have not collided" << endl;
	return false;
}

void Plane::MakeGizmo()
{
	float lineLength = 300;
	vec2 centerPoint = normal * distanceToOrigin;

	//rotate normal throught 90 degrees around z
	vec2 parallel(normal.y, -normal.x);
	vec4 testcolour(1, 1, 1, 1);
	vec2 start = centerPoint + (parallel * lineLength);
	vec2 end = centerPoint - (parallel * lineLength);

	//draw gizmo
	//std::cout << start.x << " " << start.y << " " << end.x << " " << end.y << std::endl;
	aie::Gizmos::add2DLine(start, end, colour);
}

void Plane::Debug()
{

}