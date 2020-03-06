#include "Box.h"
#include <iostream>
#include <Gizmos.h>
#include "Plane.h"

using namespace std;

Box::Box(vec2 pos, vec2 vel, vec2 boxExtents, vec4 objectColour, bool kinematic) : RigidBody(BOX, pos, vel, 0, mass, kinematic)
{
	position = pos;
	velocity = vel;
	extents = boxExtents;
	colour = objectColour;
	center = position;
}

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

bool Box::CheckCorners(const Box& box, vec2& contact, int& numContacts, float& pen, vec2& edgeNormal)
{
	float minX, maxX, minY, maxY;
	float boxWidth = box.extents.x * 2;
	float boxHeight = box.extents.y * 2;
	int numLocalContacts = 0;
	vec2 localContact(0, 0);

	bool first = true;

	for (float x = -box.extents.x; x < boxWidth; x += boxWidth)
	{
		for (float y = -box.extents.y; y < boxHeight; y += boxHeight)
		{
			//pos in world space     replace position??
			vec2 pos = box.center + x * box.localX + y * box.localY;

			//pos in box's space     replace position??
			vec2 pos0(dot(pos - center, localX), dot(pos - center, localY));

			if (first || pos0.x < minX)
			{
				minX = pos0.x;
			}

			if (first || pos0.x > maxX)
			{
				maxX = pos0.x;
			}

			if (first || pos0.y < minY)
			{
				minY = pos0.y;
			}

			if (first || pos0.y < maxY)
			{
				maxY = pos0.y;
			}

			if (pos0.x >= -extents.x && pos0.x <= extents.x && pos0.y >= -extents.y && pos0.y <= extents.y)
			{
				numLocalContacts++;
				localContact += pos0;
			}

			first = false;
		}
	}

	if (maxX <-extents.x || minX > extents.x || maxY <-extents.y || minY < extents.y)
	{
		return false;
	}

	if (numLocalContacts == 0)
	{
		return false;
	}

	bool res = false;

	contact += position + (localContact.x * localX + localContact.y * localY) / (float)numLocalContacts;

	numContacts++;

	float pen0 = extents.x - minX;

	if (pen0 > 0 && (pen0 < pen || pen == 0))
	{
		edgeNormal = localX;
		pen = pen0;
		res = true;
	}

	pen0 = maxX + extents.x;

	if (pen0 > 0 && (pen0 < pen || pen == 0))
	{
		edgeNormal = -localX;
		pen = pen0;
		res = true;
	}

	pen0 = extents.y - minY;

	if (pen0 > 0 && (pen0 < pen || pen == 0))
	{
		edgeNormal = localY;
		pen = pen0;
		res = true;
	}

	pen0 = maxY + extents.y;

	if (pen0 > 0 && (pen0 < pen || pen == 0))
	{
		edgeNormal = -localY;
		pen = pen0;
		res = true;
	}

	return res;
}
