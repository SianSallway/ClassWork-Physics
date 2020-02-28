#pragma once
#include <glm\ext.hpp>
#include "PhysicsObject.h"
#include <iostream>
#include <vector>

using namespace std;

class PhysicsScene
{
public:

	PhysicsScene();
	~PhysicsScene();

	//adds PhysicsObject pointer to the end of the actors vector
	void AddActor(PhysicsObject* actor);
	
	//removes PhysicsObject pointer from the end of the actors vector
	void RemoveActor(PhysicsObject* actor);
	
	//updates physical simulation, calls update function of each actor, handles collison detection and response 
	void Update(float deltaTime);
	
	//handles the drawing of physical objects 
	void UpdateGizmos();

	void SetGravity(const glm::vec2 g) { gravity = g; };
	glm::vec2 GetGravity() const { return gravity; };

	void SetTimeStep(const float ts) { timeStep = ts; };
	float GetTimeStep() const { return timeStep; };

	//checks for collisions between each shape type
	void CheckForCollision();

	static bool plane2Plane(PhysicsObject* obj1, PhysicsObject* obj2);
	static bool plane2Sphere(PhysicsObject* obj1, PhysicsObject* obj2);
	static bool sphere2Plane(PhysicsObject* obj1, PhysicsObject* obj2);
	static bool sphere2Sphere(PhysicsObject* obj1, PhysicsObject* obj2);
	static bool box2Plane(PhysicsObject* obj1, PhysicsObject* obj2);
	static bool box2Sphere(PhysicsObject* obj1, PhysicsObject* obj2);
	static bool box2Box(PhysicsObject* obj1, PhysicsObject* obj2);

	//calls debug function of each actor
	void DebugScene();


protected:

	glm::vec2 gravity;
	float timeStep;
	vector<PhysicsObject*> actors;									//stores all physical objects in scene 

};