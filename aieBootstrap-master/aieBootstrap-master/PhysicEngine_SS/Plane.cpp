#include "Plane.h"
#include <Gizmos.h>

Plane::Plane(vec2 planeNormal, float distance, vec4 planeColour)
{
	normal = planeNormal;
	distanceToOrigin = distance;
	colour = planeColour;
}

Plane::Plane() : PhysicsObject(ShapeType::PLANE)
{
	normal = vec2(0, 1);
	distanceToOrigin = 0;
}

void Plane::FixedUpdate(vec2 gravity, float timeStep)
{

}

void Plane::ResetPosition()
{
	distanceToOrigin = this->GetDistance();
}

void Plane::MakeGizmo()
{
	float lineLength = 300;
	vec2 centerPoint = normal * distanceToOrigin;

	//rotate normal throught 90 degrees around z
	vec2 parallel(normal.y, -normal.x);
	//vec4 colour(1, 1, 1, 1);
	vec2 start = centerPoint + (parallel * lineLength);
	vec2 end = centerPoint - (parallel * lineLength);
	
	//draw gizmo
	aie::Gizmos::add2DLine(start, end, colour);
}

void Plane::Debug()
{

}