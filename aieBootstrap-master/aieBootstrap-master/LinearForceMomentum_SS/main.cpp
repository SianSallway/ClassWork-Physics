#include "LinearForceMomentum_SSApp.h"

int main() {
	
	// allocation
	auto app = new LinearForceMomentum_SSApp();

	// initialise and loop
	app->run("AIE", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}