#include "Box.h"
#include <iostream>
#include <Gizmos.h>
#include "Plane.h"

using namespace std;

/*Box::Box(vec2 pos, vec2 vel, float mass, float w, float l, vec4 objectColour) : RigidBody(BOX, pos, vel, 0, mass)
{
	position = pos;
	velocity = vel;
	width = w;
	legnth = l;
	colour = objectColour;
}*/

void Box::MakeGizmo()
{
	//aie::Gizmos::add2DAABB(position, );
}

bool Box::CheckCollision(PhysicsObject* pOther)
{
	return false;
}