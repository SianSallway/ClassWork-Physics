#include "LinearForceMomentum_SSApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <Gizmos.h>
#include <iostream>
#include "Sphere.h"

using namespace std;
using namespace glm;

LinearForceMomentum_SSApp::LinearForceMomentum_SSApp() {

}

LinearForceMomentum_SSApp::~LinearForceMomentum_SSApp() {

}

bool LinearForceMomentum_SSApp::startup() {
	
	// increase the 2d line count to maximize the number of objects we can draw
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);

	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	physicsScene = new PhysicsScene();
	//for projectile set y to -10
	physicsScene->SetGravity(glm::vec2(0, 0));
	physicsScene->SetTimeStep(0.01f);

	ball1 = new Sphere(glm::vec2(-20, 0), glm::vec2(0, 0), 4.0f, 4, 12, glm::vec4(1, 0, 0, 1));
	//For different tutorial ->//ball2 = new Sphere(glm::vec2(ball1->GetPosition().x, (ball1->GetPosition().y) - 7), glm::vec2(0, 0), 0.5f, 4, 12, glm::vec4(0, 1, 0, 1));
	ball2 = new Sphere(glm::vec2(10, 0), glm::vec2(0, 0), 4.0f, 4, 12, glm::vec4(0, 1, 0, 1));
	
	physicsScene->AddActor(ball1);
	physicsScene->AddActor(ball2);

	ball1->ApplyForce(vec2(30, 0));
	ball2->ApplyForce(vec2(-15, 0));

	return true;
}

void LinearForceMomentum_SSApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void LinearForceMomentum_SSApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	aie::Gizmos::clear();

	physicsScene->Update(deltaTime);
	physicsScene->UpdateGizmos();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void LinearForceMomentum_SSApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	static float aspectRatio = 16 / 9.f;

	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100, -100 / aspectRatio, 100 / aspectRatio, -1.0f, 1.0f));
	
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}