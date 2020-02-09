#pragma once
#include <glm\ext.hpp>
#include <iostream>

using namespace std;

enum ShapeType
{
	PLANE = 0,
	SPHERE,
	BOX
};

//pure abstract base class
class PhysicsObject
{
protected:

	PhysicsObject(ShapeType id) : shapeID() {}

public: 

	PhysicsObject() {}

	virtual void FixedUpdate(glm::vec2 grav, float ts) = 0;
	virtual void Debug() = 0;
	virtual void MakeGizmo() = 0;
	virtual void ResetPosition() {};

protected:

	ShapeType shapeID;
};