#pragma once
#include <glm\ext.hpp>
#include "PhysicsObject.h"
#include <iostream>
#include <vector>

using namespace std;
using namespace glm;

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

	//calls debug function of each actor
	void DebugScene();


protected:

	glm::vec2 gravity;
	float timeStep;
	vector<PhysicsObject*> actors;									//stores all physical objects in scene 

};