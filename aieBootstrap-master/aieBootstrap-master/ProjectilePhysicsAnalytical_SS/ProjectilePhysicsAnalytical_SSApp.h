#pragma once

#include "Application.h"
#include "Renderer2D.h"

class ProjectilePhysicsAnalytical_SSApp : public aie::Application {
public:

	ProjectilePhysicsAnalytical_SSApp();
	virtual ~ProjectilePhysicsAnalytical_SSApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
};