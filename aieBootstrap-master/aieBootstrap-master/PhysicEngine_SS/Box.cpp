#include "Box.h"
#include <iostream>
#include <Gizmos.h>
#include "Plane.h"

using namespace std;

/*Box::Box(vec2 pos, vec2 vel, vec2 boxExtents, vec4 objectColour) : RigidBody(BOX, pos, vel, 0, mass)
{
	position = pos;
	velocity = vel;
	extents = boxExtents;
	colour = objectColour;
}*/

void Box::FixedUpdate(vec2 grav, float ts)
{
	RigidBody::FixedUpdate(grav, ts);

	//store local axes
	float cs = cosf(rotation);
	float sn = sinf(rotation);
	localX = normalize(vec2(cs, sn));
	localY = normalize(vec2(-sn, cs));
}

void Box::MakeGizmo()
{
	//draw using local axes
	vec2 p1 = position - localX * extents.x - localY * extents.y;
	vec2 p2 = position + localX * extents.x - localY * extents.y;
	vec2 p3 = position - localX * extents.x + localY * extents.y;
	vec2 p4 = position + localX * extents.x + localY * extents.y;

	aie::Gizmos::add2DTri(p1, p2, p4, colour);
	aie::Gizmos::add2DTri(p1, p4, p3, colour);
}

bool Box::CheckCollision(PhysicsObject* pOther)
{
	return false;
}