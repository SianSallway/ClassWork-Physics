#pragma once
#include <glm\ext.hpp>
#include <iostream>
#include "PhysicsObject.h"

using namespace std;
using namespace glm;

class RigidBody : public PhysicsObject
{
public:

	RigidBody(ShapeType id, glm::vec2 pos, glm::vec2 vel, float objectRotation, float objectMass);

	~RigidBody();

	virtual void FixedUpdate(glm::vec2 grav, float ts);
	virtual void Debug();
	void ApplyForce(glm::vec2 force);
	void ApplyForceToActor(RigidBody* actor2, glm::vec2 force);

	virtual bool CheckCollision(PhysicsObject* pOther) = 0;
	void ResolveCollision(RigidBody* actor2);

	//returns position vector of the rigidbody
	vec2 GetPosition() { return position; }

	//returns velocity vector of the rigidbody
	vec2 GetVelocity() { return velocity; }

	//sets the velocity to the vector 2 parameter passed in
	void SetVelocity(glm::vec2 newVel) { velocity = newVel; }

	//returns rotation value of rigidbody
	float GetRotation() { return rotation; }

	//returns mass value of rigidbody
	float GetMass() { return mass; }
	//ShapeType GetShapeType() { return shapeID; };

protected:

	glm::vec2 position;
	glm::vec2 velocity;
	float mass;
	float rotation;
};

