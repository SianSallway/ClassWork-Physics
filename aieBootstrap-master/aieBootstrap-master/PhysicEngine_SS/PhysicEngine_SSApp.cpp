#include "PhysicEngine_SSApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <Gizmos.h>
#include <iostream>
#include "Sphere.h"

using namespace std;
using namespace glm;

PhysicEngine_SSApp::PhysicEngine_SSApp() {

}

PhysicEngine_SSApp::~PhysicEngine_SSApp()
{

}

//GitHub
bool PhysicEngine_SSApp::startup() 
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
	
	ball1 = new Sphere(vec2(-23, 50), vec2(0, 0), 2.0f, 4, 12, vec4(1, 0, 0, 1), true);
	ball2 = new Sphere(vec2(0, 50), vec2(0, 0), 2.0f, 4, 12, vec4(1, 0, 0, 1), true);
	ball3 = new Sphere(vec2(18, 50), vec2(0, 0), 2.0f, 4, 12, vec4(1, 0, 0, 1), true);
	ball4 = new Sphere(vec2(47, 50), vec2(0, 0), 2.0f, 4, 12, vec4(1, 0, 0, 1), true);
	ball5 = new Sphere(vec2(70, 50), vec2(0, 0), 2.0f, 4, 12, vec4(1, 0, 0, 1), true);
	ball6 = new Sphere(vec2(-45, 50), vec2(0, 0), 2.0f, 4, 12, vec4(1, 0, 0, 1), true);
	plane1 = new Plane(vec2(3, 5), -45, vec4(1, 1, 1, 1));
	plane2 = new Plane(vec2(3, -5), 45, vec4(1, 1, 1, 1));
	box1 = new Box(vec2(-20, 30), vec2(0, 0), vec2(8, 2), vec4(1, 0, 0, 1), false);
	box2 = new Box(vec2(-60, 30), vec2(0, 0), vec2(8, 2), vec4(1, 0, 0, 1), false);
	box3 = new Box(vec2(60, 30), vec2(0, 0), vec2(8, 2), vec4(1, 0, 0, 1), false);
	box4 = new Box(vec2(35, 0), vec2(0, 0), vec2(8, 2), vec4(1, 0, 0, 1), false);
	box5 = new Box(vec2(25, 30), vec2(0, 0), vec2(8, 2), vec4(1, 0, 0, 1), false);
	box6 = new Box(vec2(-35, 0), vec2(0, 0), vec2(8, 2), vec4(1, 0, 0, 1), false);

	physicsScene->AddActor(ball1);
	physicsScene->AddActor(ball2);
	physicsScene->AddActor(ball3);
	physicsScene->AddActor(ball4);
	physicsScene->AddActor(ball5);
	physicsScene->AddActor(ball6);
	physicsScene->AddActor(box1);
	physicsScene->AddActor(box2);
	physicsScene->AddActor(box3);
	physicsScene->AddActor(box4);
	physicsScene->AddActor(box5);
	physicsScene->AddActor(box6);
	physicsScene->AddActor(plane1);
	physicsScene->AddActor(plane2);


	return true;
}

void PhysicEngine_SSApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
	delete ball1;
	delete ball2;
	delete ball3;
	delete ball4;
	delete ball5;
	delete ball6;
	delete newSphere;
	delete box1;
	delete box2;
	delete box3;
	delete box4;
	delete box5;
	delete box6;
	delete plane1;
	delete plane2;
}

void PhysicEngine_SSApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	aie::Gizmos::clear();

	physicsScene->Update(deltaTime);
	physicsScene->UpdateGizmos();

	//Add a new sphere to the scene when the 'S' key is pressed
	if (input->wasKeyPressed(aie::INPUT_KEY_S))
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

		newSphere = new Sphere(worldMousePos, vec2(0, 0), 2.0f, 4, 12, vec4(128, 0, 128, 1), true);
		physicsScene->AddActor(newSphere);
	}

	//Add a new box to the scene when the 'B' key is pressed
	if (input->wasKeyPressed(aie::INPUT_KEY_B))
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

		newBox = new Box(worldMousePos, vec2(0, 0), vec2(8, 2), vec4(128, 0, 128, 1), false);
		physicsScene->AddActor(newBox);
	}

	//delete the object at the position of the right mouse click
	if (input->wasMouseButtonPressed(1))
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

		for (int i = 0; i < physicsScene->GetActorsAmount(); i++)
		{
			RigidBody* actor = dynamic_cast<RigidBody*>(physicsScene->actors[i]);

			//cout << "shape type: " << actor->GetShapeType() << endl;
			//cout << "shape pos: " << actor->GetPosition().x << ", " << actor->GetPosition().y << endl;

			if (physicsScene->actors[i]->GetShapeType() == SPHERE)
			{
				Sphere* sphere = dynamic_cast<Sphere*>(physicsScene->actors[i]);

				//check if mouse click was anywhere on the sphere
				vec2 sphereZone = sphere->GetPosition() + sphere->GetRadius();

				if (worldMousePos == sphereZone)
				{
					physicsScene->RemoveActor(physicsScene->actors[i]);
				}
			}

			if (actor != nullptr && actor->GetPosition() == worldMousePos)
			{
				physicsScene->RemoveActor(physicsScene->actors[i]);
				//cout << "shape type: " << physicsScene->actors[i]->GetShapeType() << endl;
			}
		}
	}

	//remove the last object added to the scene 
	if (input->wasKeyPressed(aie::INPUT_KEY_DELETE))
	{
		physicsScene->RemoveActor();
	}

	//reverse the force of gravity when the G key is held down
	if (input->isKeyDown(aie::INPUT_KEY_G))
	{
		physicsScene->SetGravity(vec2(0, 20));
	}

	//restore gravity when the G key is released
	if (input->isKeyUp(aie::INPUT_KEY_G))
	{
		physicsScene->SetGravity(vec2(0, -20));
	}

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void PhysicEngine_SSApp::draw() {

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