#pragma once
#include <glm\ext.hpp>
#include <iostream>
#include "PhysicsObject.h"

using namespace std;
using namespace glm;

class RigidBody : public PhysicsObject
{
public:

	RigidBody(ShapeType id, vec2 pos, vec2 vel, float objectRotation, float objectMass);

	~RigidBody();

	virtual void FixedUpdate(glm::vec2 grav, float ts);
	virtual void Debug();
	//void ApplyForce(vec2 force);
	void ApplyForce(vec2 force, vec2 pos);
	//void ApplyForceToActor(RigidBody* actor2, vec2 force);

	virtual bool CheckCollision(PhysicsObject* pOther) = 0;
	//void ResolveCollision(RigidBody* actor2);
	void ResolveCollision(RigidBody* actor2, vec2 contact, vec2* collisionNormal = nullptr);

	vec2 GetPosition() { return position; }
	vec2 GetVelocity() { return velocity; }
	void SetVelocity(glm::vec2 newVel) { velocity = newVel; }
	float GetRotation() { return rotation; }
	float GetMass() { return mass; }
	float GetElasticity() { return elasticity; }
	void SetLinearDrag(float linDrag) { linearDrag = linDrag; };
	void SetAngularDrag(float angDrag) { angularDrag = angDrag; };

protected:

	vec2 position;
	vec2 velocity;
	float mass;
	float rotation;
	float linearDrag;
	float angularDrag;
	const float  MIN_LINEAR_THRESHOLD = 0.1f;
	const float  MIN_ROTATION_THRESHOLD = 0.01f;
	float angularVelocity;
	float elasticity;
	float moment;										//moment of inertia
};