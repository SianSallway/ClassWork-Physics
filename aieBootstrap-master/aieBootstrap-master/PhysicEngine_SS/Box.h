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

	Box(vec2 boxLocalX, vec2 boxLocalY, vec2 boxExtents, vec4 objectColour);
	~Box() {}

	virtual void FixedUpdate(vec2 grav, float ts);
	virtual void MakeGizmo();
	virtual bool CheckCollision(PhysicsObject* pOther);

protected:

	vec2 localX;				//store local x and y axis of box based on its angle of rotation 
	vec2 localY;
	vec2 extents;				//the halfedge lengths
	vec4 colour;

};

