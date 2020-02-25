#include "RigidBody.h"
#include <iostream>


using namespace std;
using namespace glm;

RigidBody::RigidBody(ShapeType id, glm::vec2 pos, glm::vec2 vel, float objectRotation, float objectMass)
{
	position = pos;
	velocity = vel;
	rotation = objectRotation;
	mass = objectMass;
	this->shapeID = id;
	linearDrag = 0.3f;
	angularDrag = 0.3f;
	elasticity = 1;
	angularVelocity = 0.01f;
}

RigidBody::~RigidBody()
{

}

void RigidBody::ApplyForce(glm::vec2 force)
{
	glm::vec2 acceleration = force / mass;

	velocity += acceleration;
}

void RigidBody::ApplyForceToActor(RigidBody* actor2, glm::vec2 force)
{
	actor2->ApplyForce(force);
	ApplyForce(-force);
}

void RigidBody::FixedUpdate(glm::vec2 g, float ts)
{
	//gravity * mass * time step
	ApplyForce(g * mass * ts);
	position += velocity * ts;
	velocity -= velocity * linearDrag * ts;
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

void RigidBody::ResolveCollision(RigidBody* actor2)
{
	vec2 normal = normalize(actor2->GetPosition() - position);
	vec2 relVel = actor2->GetVelocity() - velocity;

	elasticity = (elasticity + actor2->GetElasticity()) / 2.0f;
	float j = dot(-(1 + elasticity) * (relVel), normal) / dot(normal, normal * ((1/mass) + (1/actor2->GetMass())));

	vec2 force = normal * j;

	ApplyForceToActor(actor2, force);
}

void RigidBody::Debug()
{

}