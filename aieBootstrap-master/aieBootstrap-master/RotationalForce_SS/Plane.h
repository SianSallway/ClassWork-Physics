#pragma once
#include "PhysicsObject.h"
#include "RigidBody.h"
#include <iostream>

using namespace std;
using namespace glm;

class Plane : public PhysicsObject
{
public:

	Plane() {};
	Plane(vec2 planeNormal, float distance, vec4 planeColour);
	~Plane() {};

	virtual void FixedUpdate(vec2 gravity, float timeStep);
	virtual void Debug();
	virtual void MakeGizmo();
	virtual void ResetPosition();
	virtual bool CheckCollision(PhysicsObject* pOther);

	void ResolveCollision(RigidBody* actor2, vec2 contact);

	vec2 GetNormal() { return normal; }
	float GetDistance() { return distanceToOrigin; }

protected:

	vec2 normal;
	float distanceToOrigin;
	vec4 colour;
};