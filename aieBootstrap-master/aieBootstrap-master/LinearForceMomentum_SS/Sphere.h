#pragma once
#include "PhysicsObject.h"
#include <glm\ext.hpp>
#include <iostream>
#include "RigidBody.h"

using namespace std;
using namespace glm;

class Sphere : public RigidBody
{
public:

	Sphere(glm::vec2 pos, glm::vec2 vel, float sphereRadius, float sphereMass, float seg, vec4 objectColour);
	~Sphere() {}

	virtual void MakeGizmo();
	virtual bool CheckCollision(PhysicsObject* pOther);

	float GetRadius() { return radius; }
	float GetSegments() { return segments; }
	vec4 GetColour() { return colour; }
	void SetPosition(vec2 newPos) { position = newPos; }

protected:

	float radius;
	vec4 colour;
	float segments;
};