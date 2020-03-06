#pragma once
#include "PhysicsObject.h"
#include <glm\ext.hpp>
#include <iostream>
#include "RigidBody.h"

using namespace std;
using namespace glm;

//handles box object properties amd inherits from the RigidBody class
class Box : public RigidBody
{
public:

	//constructor
	Box(vec2 pos, vec2 vel, vec2 boxExtents, vec4 objectColour, bool kinematic);

	//de-constructor 
	~Box() {}

	virtual void FixedUpdate(vec2 grav, float ts);

	//handles box graphics 
	virtual void MakeGizmo();

	//checks for collision with another sphere
	virtual bool CheckCollision(PhysicsObject* pOther);

	//sets box's position to the vector 2 value passed in 
	void SetPosition(vec2 newpos) { position = newpos; }

	//returns box extents 
	vec2 GetExtents() { return extents; }

	//returns box's local x value
	vec2 GetLocalX() { return localX; }

	//returns box's local y value
	vec2 GetLocalY() { return localY; }

	//return box's center value 
	vec2 GetCenter() { return center; }

	//returns the box's width stored in the x axis of the extents vector2
	float GetWidth() { return  extents.x * 2; }

	//returns the box's height stored in the y axis of the extents vector2
	float GetHeight() { return extents.y * 2; }
	
	//check if any of the other box's corners are inside this box
	bool CheckCorners(const Box& box, vec2& contact, int& numContacts, float& pen, vec2& edgeNormal);


protected:

	vec2 localX;				//store local x axis of box based on its angle of rotation 
	vec2 localY;				//store local y axis of box based on its angle of rotation
	vec2 extents;				//the halfedge lengths
	vec2 center;				//stores the center of the shape (equal to its world space position)
	vec4 colour;				//stores colour values
};

