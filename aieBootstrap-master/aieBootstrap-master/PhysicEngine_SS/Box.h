#pragma once
#include "PhysicsObject.h"
#include <glm\ext.hpp>
#include <iostream>
#include "RigidBody.h"

using namespace std;
using namespace glm;

class Box : public RigidBody
{
public:

	Box(vec2 pos, vec2 vel, float mass, float w, float l, vec4 objectColour);
	~Box() {}


	virtual void MakeGizmo();
	virtual bool CheckCollision(PhysicsObject* pOther);

protected:

	float width;
	float legnth;
	vec4 colour;

};

