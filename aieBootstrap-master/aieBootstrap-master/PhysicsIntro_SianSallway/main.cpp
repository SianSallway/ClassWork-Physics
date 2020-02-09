#include "PhysicsIntro_SianSallwayApp.h"

int main() {
	
	// allocation
	auto app = new PhysicsIntro_SianSallwayApp();

	// initialise and loop
	app->run("AIE", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}