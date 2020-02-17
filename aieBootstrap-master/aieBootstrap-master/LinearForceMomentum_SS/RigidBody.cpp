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
}

void RigidBody::ResolveCollision(RigidBody* actor2)
{
	vec2 normal = normalize(actor2->GetPosition() - position);
	vec2 relVel = actor2->GetVelocity() - velocity;

	float elasticity = 1;
	float j = dot(-(1 + elasticity) * (relVel), normal) / dot(normal, normal * ((1 / mass) + (1 / actor2->GetMass())));

	vec2 force = normal * j;

	ApplyForceToActor(actor2, force);
}

void RigidBody::Debug()
{

}