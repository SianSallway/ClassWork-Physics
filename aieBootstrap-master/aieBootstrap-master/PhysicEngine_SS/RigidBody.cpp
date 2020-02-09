#include "RigidBody.h"
#include <iostream>

using namespace std;

RigidBody::RigidBody(ShapeType id, glm::vec2 pos, glm::vec2 vel, float objectRotation, float objectMass)
{
	position = pos;
	velocity = vel;
	rotation = objectRotation;
	mass = objectMass;
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

void RigidBody::Debug()
{

}