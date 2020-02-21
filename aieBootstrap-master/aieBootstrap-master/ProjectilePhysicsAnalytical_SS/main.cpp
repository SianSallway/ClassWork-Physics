#include "ProjectilePhysics_SSApp.h"

int main() {
	
	// allocation
	auto app = new ProjectilePhysics_SSApp();

	// initialise and loop
	app->run("AIE", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}