#include "RigidBody.h"
#include "Sphere.h"
#include <iostream>

using namespace std;
using namespace glm;

RigidBody::RigidBody(ShapeType id, glm::vec2 pos, glm::vec2 vel, float objectRotation, float objectMass, bool kinematic)
{
	position = pos;
	velocity = vel;
	rotation = objectRotation;
	mass = objectMass;
	this->shapeID = id;
	linearDrag = 0.3f;
	angularDrag = 0.3f;
	elasticity = 0.9f;
	angularVelocity = 0.01f;

	if (kinematic == true)
	{
		isKinematic = true;
	}
	else
	{
		isKinematic = false;
	}
}

RigidBody::~RigidBody()
{

}

void RigidBody::ApplyForce(vec2 force, vec2 pos)
{
	vec2 acceleration = force / mass;
	velocity += acceleration;

	if (shapeID == SPHERE)
	{
		angularVelocity += (force.y * pos.x + force.x * pos.y) / (moment);
	}
	else if (shapeID == BOX)
	{
		angularVelocity += (force.y * pos.x - force.x * pos.y) / (moment);
	}
}

float RigidBody::GetKineticEnergy()
{
	return 0.5f * (mass * dot(velocity, velocity) + moment * angularVelocity * angularVelocity);
}

void RigidBody::FixedUpdate(glm::vec2 g, float ts)
{
	if (isKinematic == true)
	{
		//gravity * mass * time step
		ApplyForce(g * mass * ts, vec2(0, 0));
		position += velocity * ts;

		velocity -= velocity * linearDrag * ts;
		rotation += angularVelocity * angularDrag * ts;
		angularVelocity -= angularVelocity * angularDrag * ts;

		if (length(velocity) < MIN_LINEAR_THRESHOLD)
		{
			velocity = vec2(0, 0);
		}

		if (abs(angularVelocity) < MIN_ROTATION_THRESHOLD)
		{
			angularVelocity = 0;
		}
	}
}

void RigidBody::ResolveCollision(RigidBody* actor2, vec2 contact, vec2* collisionNormal)
{
	//find vector between their centres, or use provided dir of force and normalize it
	vec2 normal = normalize(collisionNormal ? *collisionNormal : actor2->GetPosition() - position);

	//get vector perpendicular to collisionNormal
	vec2 perpendicular(normal.y, -normal.x);

	//determine total vel of contact points for both objects, linear and rotational	
	//r = radius from axis to application of force
	float r1 = dot(contact - position, -perpendicular);
	float r2 = dot(contact - actor2->GetPosition(), perpendicular);

	//vel of contact point on this obj
	float v1 = dot(velocity, normal) - r2 * angularVelocity;

	//vel of contact point on actor2
	float v2 = dot(actor2->GetVelocity(), normal) + r2 * actor2->angularVelocity;

	if (v1 > v2)
	{
		//calc effectiv mass as contact point for both objects
		float mass1 = 1.0f / (1.0f / mass + (r1 * r1) / moment);
		float mass2 = 1.0f / (1.0f / actor2->GetMass() + (r2 * r2) / actor2->moment);

		elasticity = (elasticity + actor2->GetElasticity()) / 2.0f;

		vec2 force = (1.0f + elasticity) * mass1 * mass2 / (mass1 + mass2) * (v1 - v2) * normal;

		//apply equal and opposite forces
		ApplyForce(-force, contact - position);
		actor2->ApplyForce(force, contact - actor2->GetPosition());
	}
}

void RigidBody::Debug()
{

}