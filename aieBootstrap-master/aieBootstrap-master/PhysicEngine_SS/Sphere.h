#pragma once
#include "PhysicsObject.h"
#include <glm\ext.hpp>
#include <iostream>
#include "RigidBody.h"

using namespace std;

class Sphere : public RigidBody
{
public:

	Sphere(glm::vec2 pos, glm::vec2 vel, float sphereRadius, float sphereMass, float seg, glm::vec4 objectColour);
	~Sphere();

	virtual void MakeGizmo();
	virtual bool CheckCollision(PhysicsObject* pOther);

	float GetRadius() { return radius; }
	float GetSegments() { return segments; }
	glm::vec4 GetColour() { return colour; }

protected:

	float radius;
	glm::vec4 colour;
	float segments;
};