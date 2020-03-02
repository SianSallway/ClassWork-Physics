#pragma once
#include "PhysicsObject.h"
#include <glm\ext.hpp>
#include <iostream>
#include "RigidBody.h"

using namespace std;
using namespace glm;

//handles sphere object properties amd inherits from the RigidBody class
class Sphere : public RigidBody
{
public:

	//contsructor
	Sphere(vec2 pos, vec2 vel, float sphereRadius, float sphereMass, float seg, vec4 objectColour);

	//de-constructor
	~Sphere() {}

	//handles sphere graphics 
	virtual void MakeGizmo();

	//checks for collision with another sphere
	virtual bool CheckCollision(PhysicsObject* pOther);

	//returns the radius of sphere
	float GetRadius() { return radius; }

	//returns the amount of segments in sphere
	float GetSegments() { return segments; }

	//returns the colour vector of sphere
	vec4 GetColour() { return colour; }

	//sets spheres position to the vector 2 value passed in
	void SetPosition(vec2 newPos) { position = newPos; }

protected:

	float radius;				//stores the radius of the sphere object
	vec4 colour;				//stores the colour values of the sphere object
	float segments;				//stores the amount of segments the sphere object has 
};