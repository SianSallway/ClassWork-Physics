#pragma once
#include "Application.h"
#include "Renderer2D.h"
#include "PhysicsScene.h"
#include "Sphere.h"
#include "Plane.h"
#include <glm\ext.hpp>

using namespace glm;

class PhysicEngine_SSApp : public aie::Application {
public:

	PhysicEngine_SSApp();
	virtual ~PhysicEngine_SSApp();

	void SetupConinuousDemo(glm::vec2 startPos, float inclination, float speed, float gravity);
	void SetupNumericalIntergration(vec2 startPos, vec2 velocity, vec2 force, float inclination);
	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
	PhysicsScene*		physicsScene;
	Sphere*				ball1;
	Sphere*				ball2;
	Sphere*				ball3;
	Sphere*				ball4;
	Sphere*				track;
	Plane*				plane1;
	Plane*				plane2;
};