#pragma once
#include <glm\ext.hpp>
#include <iostream>
#include "PhysicsObject.h"

using namespace std;
using namespace glm;

class RigidBody : public PhysicsObject
{
public:

	//constructor
	RigidBody(ShapeType id, vec2 pos, vec2 vel, float objectRotation, float objectMass);

	//de-constructor
	~RigidBody();

	virtual void FixedUpdate(glm::vec2 grav, float ts);
	virtual void Debug();
	//void ApplyForce(vec2 force);
	void ApplyForce(vec2 force, vec2 pos);
	//void ApplyForceToActor(RigidBody* actor2, vec2 force);

	virtual bool CheckCollision(PhysicsObject* pOther) = 0;
	//void ResolveCollision(RigidBody* actor2);
	void ResolveCollision(RigidBody* actor2, vec2 contact, vec2* collisionNormal = nullptr);

	//returns position vector of the rigidbody
	vec2 GetPosition() { return position; }
	
	//returns velocity vector of the rigidbody
	vec2 GetVelocity() { return velocity; }
	
	//returns angular velocity value of the rigidbody
	float GetAngularVelocity() { return angularVelocity; }
	
	//sets the velocity to the vector 2 parameter passed in
	void SetVelocity(glm::vec2 newVel) { velocity = newVel; }

	void SetPosition(vec2 newpos) { position = newpos; }
	
	//returns rotation value of rigidbody
	float GetRotation() { return rotation; }
	
	//returns mass value of rigidbody
	float GetMass() { return mass; }
	
	//returns elasticity value of rigidbody
	float GetElasticity() { return elasticity; }
	
	//returns the moment of inertia
	float GetMoment() { return moment; }

	//calculates the Kinetic energy of the rigidbody
	float GetKineticEnergy();

	//sets the linear drag to the float parameter passed in
	void SetLinearDrag(float linDrag) { linearDrag = linDrag; };

	//sets the angular drag to the float parameter passed in
	void SetAngularDrag(float angDrag) { angularDrag = angDrag; };

	bool IsKinematic() { return isKinematic == true; }

	void ApplyContactForces(RigidBody* body1, RigidBody* body2, vec2 norm, float pen);

protected:

	vec2 position;										//x and y axis position of rigidbody in world space
	vec2 velocity;										//x and y axis velocity of rigidbody
	float mass;											//rigidbody mass
	float rotation;										//rigidbody rotation value used for rotational force
	float linearDrag;
	float angularDrag;
	const float  MIN_LINEAR_THRESHOLD = 0.1f;
	const float  MIN_ROTATION_THRESHOLD = 0.01f;
	float angularVelocity;
	float elasticity;
	float moment;										//moment of inertia
	bool isKinematic;
};