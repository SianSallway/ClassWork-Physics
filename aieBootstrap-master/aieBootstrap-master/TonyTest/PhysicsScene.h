#pragma once
#include <glm\ext.hpp>
#include "PhysicsObject.h"
#include <iostream>
#include <vector>

using namespace std;
using namespace glm;

//handles interactions of objects and properties of the scene
class PhysicsScene
{
public:

	//constructor
	PhysicsScene();

	//de-constructor
	~PhysicsScene();

	//adds PhysicsObject pointer to the end of the actors vector
	void AddActor(PhysicsObject* actor);

	//removes PhysicsObject pointer from the end of the actors vector
	void RemoveActor(PhysicsObject* actor);
	//void RemoveActor();

	//updates physical simulation, calls update function of each actor, handles collison detection and response 
	void Update(float deltaTime);

	//handles the drawing of physical objects
	void UpdateGizmos();

	//sets the force of gravity that will be applied to the objects in the scene
	void SetGravity(const vec2 g) { gravity = g; };

	//returns gravity vector of scene
	vec2 GetGravity() const { return gravity; };

	//sets the time step to the float value passed in 
	void SetTimeStep(const float ts) { timeStep = ts; };

	//returns the time step of the scene
	float GetTimeStep() const { return timeStep; };

	//checks if collisions have occured between obvject and calls functions based on their shape type
	void CheckForCollision();

	//checks for collisions between planes, if true calls the appropiate function 
	static bool plane2Plane(PhysicsObject* obj1, PhysicsObject* obj2);

	//checks for collisions between planes and spheres, if true resolves collision
	static bool plane2Sphere(PhysicsObject* obj1, PhysicsObject* obj2);

	//checks for collisions between spheres and planes, if true resolves collision
	static bool sphere2Plane(PhysicsObject* obj1, PhysicsObject* obj2);

	//checks for collisions between spheres, if true resolves collision
	static bool sphere2Sphere(PhysicsObject* obj1, PhysicsObject* obj2);

	//calls debug function of each actor
	void DebugScene();

	float GetActorsAmount() { return actors.size(); }

protected:

	vec2 gravity;
	float timeStep;
	vector<PhysicsObject*> actors;									//stores all physical objects in scene 

};