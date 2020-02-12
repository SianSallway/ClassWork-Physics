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

PhysicEngine_SSApp::~PhysicEngine_SSApp() {

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
	physicsScene->SetGravity(glm::vec2(0, 0));
	physicsScene->SetTimeStep(0.01f);

	//SetupConinuousDemo(glm::vec2(-40, 0), 45, 30, -10); 
	//SetupNumericalIntergration(vec2(-40, 0), vec2(30, 30), vec2(0, -10), 45);
	
	ball1 = new Sphere(glm::vec2(-20, 0), glm::vec2(0, 0), 4.0f, 4, 12, glm::vec4(1, 0, 0, 1));
	//ball2 = new Sphere(glm::vec2(ball1->GetPosition().x, (ball1->GetPosition().y) - 7), glm::vec2(0, 0), 0.5f, 4, 12, glm::vec4(0, 1, 0, 1));
	//ball2 = new Sphere(glm::vec2(10, 0), glm::vec2(0, 0), 4.0f, 4, 12, glm::vec4(0, 1, 0, 1));
	plane = new Plane(vec2(20,20), -20.0f, vec4(1, 1, 1, 1));

	physicsScene->AddActor(ball1);
	//physicsScene->AddActor(ball2);
	physicsScene->AddActor(plane);

	//ball1->ApplyForce(glm::vec2(25, 5));
	//ball2->ApplyForce(glm::vec2(0, 30));
	//ball1->ApplyForceToActor(ball2, glm::vec2(2, 0));
	ball1->ApplyForce(glm::vec2(30,0));
	//ball2->ApplyForce(glm::vec2(-15, 0));
	

	return true;
}

void PhysicEngine_SSApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void PhysicEngine_SSApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	aie::Gizmos::clear();
	
	physicsScene->Update(deltaTime);
	//FIX: PLANE NOT DRAWING 
	physicsScene->UpdateGizmos();

	//float ballMass = ball1->GetMass();
	//ballMass -= 0.5f;

	/*if (ball1->GetPosition().y > 0)
	{
		aie::Gizmos::add2DCircle(glm::vec2(ball2->GetPosition().x, ball2->GetPosition().y - 2), ball2->GetRadius(), ball2->GetSegments(), ball2->GetColour());
	}*/

	/*if (input->wasKeyPressed(aie::INPUT_KEY_ENTER))
	{
		ball1->ApplyForceToActor(ball2, glm::vec2(2, 0));
	}*/

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