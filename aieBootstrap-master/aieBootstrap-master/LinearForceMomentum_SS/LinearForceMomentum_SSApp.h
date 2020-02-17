#pragma once
#include "Application.h"
#include "Renderer2D.h"
#include "PhysicsScene.h"
#include "Sphere.h"
#include <glm\ext.hpp>

using namespace glm;

class LinearForceMomentum_SSApp : public aie::Application {
public:

	LinearForceMomentum_SSApp();
	virtual ~LinearForceMomentum_SSApp();

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
};