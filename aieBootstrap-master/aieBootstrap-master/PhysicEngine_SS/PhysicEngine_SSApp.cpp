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

void PhysicEngine_SSApp::SetupConinuousDemo(glm::vec2 startPos, float inclination, float speed, float gravity)
{
	float t = 0;
	float timeStep = 0.1f;
	float radius = 1.0f;
	int segments = 12;
	glm::vec4 colour = glm::vec4(1, 1, 0, 1);

	while (t <= 5)
	{
		//calculate the x, y position of the projectile at time t
		float x;
		float y;
		
		//kinematic formulas fro x and y axis, changing the inclination angle over time
		x = startPos.x + (t * cos(inclination) * speed);
		y = startPos.y + (t * sin(inclination) * speed) + 0.5 * gravity * pow(t, 2);

		aie::Gizmos::add2DCircle(glm::vec2(x, y), radius, segments, colour);
		//physicsScene->AddActor(new Sphere(vec2(x, y), vec2(0, speed), radius, 0, segments, vec4(1, 0, 0, 1)));
		t += timeStep;
	}
}

void PhysicEngine_SSApp::SetupNumericalIntergration(vec2 startPos, vec2 velocity, vec2 force, float inclination)
{
	float t = 0;
	float dt = physicsScene->GetTimeStep();
	float radius = 1.0f;
	int segments = 12;
	vec4 colour = glm::vec4(1, 0, 0, 1);
	float mass = 1;
	float x;
	float y;

	if (t <= dt)
	{
		x = startPos.x + (t * cos(inclination) * velocity.x) * dt;
		y = startPos.y + (t * sin(inclination) * velocity.y) + 0.5 * force.y * pow(t, 2);

		velocity = velocity + (force / mass) * dt;
		t += dt;

		track = new Sphere(vec2(x, y), velocity, radius, mass, 12, vec4(1, 0, 0, 1));
		physicsScene->AddActor(track);
	}
}

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
	
	ball1 = new Sphere(vec2(-23, 50), vec2(0, 0), 4.0f, 4, 12, vec4(1, 0, 0, 1));
	ball2 = new Sphere(vec2(0, 50), vec2(0, 0), 4.0f, 4, 12, vec4(1, 0, 0, 1));
	ball3 = new Sphere(vec2(18, 50), vec2(0, 0), 4.0f, 4, 12, vec4(1, 0, 0, 1));
	ball4 = new Sphere(vec2(47, 50), vec2(0, 0), 4.0f, 4, 12, vec4(1, 0, 0, 1));
	ball5 = new Sphere(vec2(70, 50), vec2(0, 0), 4.0f, 4, 12, vec4(1, 0, 0, 1));
	ball6 = new Sphere(vec2(-45, 50), vec2(0, 0), 4.0f, 4, 12, vec4(1, 0, 0, 1));
	plane1 = new Plane(vec2(3,5), -45, vec4(1, 1, 1, 1));
	plane2 = new Plane(vec2(3,-5), 45, vec4(1, 1, 1, 1));
	box1 = new Box(vec2(0, 0), vec2(0, 0), vec2(8, 2), vec4(1, 0, 0, 1));
	box2 = new Box(vec2(-60, 30), vec2(0, 0), vec2(8, 2), vec4(1, 0, 0, 1));
	box3 = new Box(vec2(60, 30), vec2(0, 0), vec2(8, 2), vec4(1, 0, 0, 1));
	box4 = new Box(vec2(35, 0), vec2(0, 0), vec2(8, 2), vec4(1, 0, 0, 1));
	box5= new Box(vec2(25, 30), vec2(0, 0), vec2(8, 2), vec4(1, 0, 0, 1));
	box6= new Box(vec2(-35, 0), vec2(0, 0), vec2(8, 2), vec4(1, 0, 0, 1));
	box7= new Box(vec2(-20, 30), vec2(0, 0), vec2(8, 2), vec4(1, 0, 0, 1));

	physicsScene->AddActor(ball1);
	physicsScene->AddActor(ball2);
	physicsScene->AddActor(ball3);
	physicsScene->AddActor(ball4);
	physicsScene->AddActor(ball5);
	physicsScene->AddActor(ball6);
	physicsScene->AddActor(plane1);
	physicsScene->AddActor(plane2);
	physicsScene->AddActor(box1);
	physicsScene->AddActor(box2);
	physicsScene->AddActor(box3);
	physicsScene->AddActor(box4);
	physicsScene->AddActor(box5);
	physicsScene->AddActor(box6);
	physicsScene->AddActor(box7);

	return true;
}

void PhysicEngine_SSApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
	/*delete ball1;
	delete ball2;
	delete ball3;
	delete ball4;
	delete newSphere;
	delete plane1;
	delete plane2;*/
}

void PhysicEngine_SSApp::update(float deltaTime) {

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

	//Add a new box to the scene when the right mouse button is clicked
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

		newBox = new Box(worldMousePos, vec2(0,0), vec2(8, 2), vec4(1, 0, 0, 1));
		physicsScene->AddActor(newBox);
	}

	if (input->wasKeyPressed(aie::INPUT_KEY_S))
	{
		//physicsScene->RemoveActor();
	}

	if (input->wasKeyPressed(aie::INPUT_KEY_B))
	{
		//physicsScene->RemoveActor();
	}

	//cout << "Vector size: " << physicsScene->actors.size() << endl;
	
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