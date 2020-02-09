#pragma once

#include "Application.h"
#include "Renderer2D.h"

class PhysicsIntro_SianSallwayApp : public aie::Application {
public:

	PhysicsIntro_SianSallwayApp();
	virtual ~PhysicsIntro_SianSallwayApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
};