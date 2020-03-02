#include "CollisionResolution_SSApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <glm\ext.hpp>
#include <Gizmos.h>
#include <iostream>

using namespace std;

CollisionResolution_SSApp::CollisionResolution_SSApp() {

}

CollisionResolution_SSApp::~CollisionResolution_SSApp() {

}

bool CollisionResolution_SSApp::startup()
{
	// increase the 2d line count to maximize the number of objects we can draw
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);

	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	physicsScene = new PhysicsScene();
	//for projectile set y to -10
	physicsScene->SetGravity(glm::vec2(0, -20));
	physicsScene->SetTimeStep(0.01f);

	//SetupConinuousDemo(glm::vec2(-40, 0), 45, 30, -10); 
	//SetupNumericalIntergration(vec2(-40, 0), vec2(30, 30), vec2(0, -10), 45);

	ball1 = new Sphere(vec2(-20, -35), vec2(0, 0), 4.0f, 4, 12, vec4(1, 0, 0, 1));
	//For different tutorial ->//ball2 = new Sphere(glm::vec2(ball1->GetPosition().x, (ball1->GetPosition().y) - 7), glm::vec2(0, 0), 0.5f, 4, 12, glm::vec4(0, 1, 0, 1));
	ball2 = new Sphere(vec2(30, 0), vec2(0, 0), 4.0f, 4, 12, vec4(1, 0, 0, 1));
	ball3 = new Sphere(vec2(40, 20), vec2(0, 0), 4.0f, 4, 12, vec4(1, 0, 0, 1));
	ball4 = new Sphere(vec2(20, 0), vec2(0, 0), 4.0f, 4, 12, vec4(1, 0, 0, 1));
	plane1 = new Plane(vec2(3, 5), -45, vec4(1, 1, 1, 1));
	plane2 = new Plane(vec2(3, -3), 45, vec4(1, 1, 1, 1));


	physicsScene->AddActor(ball1);
	physicsScene->AddActor(ball2);
	physicsScene->AddActor(ball3);
	physicsScene->AddActor(ball4);
	physicsScene->AddActor(plane1);
	physicsScene->AddActor(plane2);


	return true;
}

void CollisionResolution_SSApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void CollisionResolution_SSApp::update(float deltaTime)
{
	// input example
	aie::Input* input = aie::Input::getInstance();

	aie::Gizmos::clear();

	physicsScene->Update(deltaTime);
	physicsScene->UpdateGizmos();

	//Add a new sphere to the scene when the left mouse button is clicked
	if (input->wasMouseButtonPressed(0))
	{
		//window dimensions
		vec2 winDim = vec2(aie::Application::getWindowWidth() * 0.5, aie::Application::getWindowHeight() * 0.5);

		static float aspectRatio = winDim.x / winDim.y;

		//mouse position
		int mouseX;
		int mouseY;
		input->getMouseXY(&mouseX, &mouseY);

		//convert mouse x & y to range -1 to 1
		vec2 nMousePos = (vec2((float)mouseX, (float)mouseY) / winDim) - vec2(1.0, 1.0);

		//convert to world space
		vec2 worldMousePos = (vec2(nMousePos.x * 100, nMousePos.y * 100 / aspectRatio));

		newSphere = new Sphere(worldMousePos, vec2(0, 0), 4.0f, 4, 12, vec4(0, 1, 0, 1));
		physicsScene->AddActor(newSphere);

		//cout << "Last item shape type: " << physicsScene->actors.back()->GetShapeType() << endl;
		//newSphere->ApplyForce(vec2(0, -10));
	}


	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void CollisionResolution_SSApp::draw()
{
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