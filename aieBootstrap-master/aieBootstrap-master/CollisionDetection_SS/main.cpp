#include "CollisionDetection_SSApp.h"

int main() {
	
	// allocation
	auto app = new CollisionDetection_SSApp();

	// initialise and loop
	app->run("AIE", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}