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

	Box(vec2 pos, vec2 vel, vec2 boxExtents, vec4 objectColour);
	~Box() {}

	virtual void FixedUpdate(vec2 grav, float ts);
	virtual void MakeGizmo();
	virtual bool CheckCollision(PhysicsObject* pOther);

	vec2 GetExtents() { return extents; }
	vec2 GetLocalX() { return localX; }
	vec2 GetLocalY() { return localY; }
	vec2 GetCenter() { return center; }
	float GetWidth() { return  extents.x * 2; }
	float GetHeight() { return extents.y * 2; }
	
	//check if any of the other box's corners are inside this box
	bool CheckCorners(const Box& box, vec2& contact, int& numContacts, float& pen, vec2& edgeNormal);


protected:

	vec2 localX;				//store local x and y axis of box based on its angle of rotation 
	vec2 localY;
	vec2 extents;				//the halfedge lengths
	vec2 center;
	vec4 colour;
};

