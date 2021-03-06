#pragma once
#include "Application.h"
#include "Renderer2D.h"
#include "PhysicsScene.h"
#include "Sphere.h"
#include "Plane.h"
#include "Box.h"
#include <glm\ext.hpp>

using namespace glm;

class PhysicEngine_SSApp : public aie::Application {
public:

	PhysicEngine_SSApp();
	virtual ~PhysicEngine_SSApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D* m_2dRenderer;
	aie::Font* m_font;
	PhysicsScene* physicsScene;
	Sphere* ball1;
	Sphere* ball2;
	Sphere* ball3;
	Sphere* ball4;
	Sphere* ball5;
	Sphere* ball6;
	Sphere* newSphere;
	Plane* plane1;
	Plane* plane2;
	Box* box1;
	Box* box2;
	Box* box3;
	Box* box4;
	Box* box5;
	Box* box6;
	Box* newBox;
};