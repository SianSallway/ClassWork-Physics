#pragma once

#include "Application.h"
#include "Renderer2D.h"

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
};