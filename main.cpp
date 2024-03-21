// Project includes
#include "Game.h"

/*
// Console Debugging and filing includes
#include <iostream>
#include <fstream>
#include <sstream>
#include <istream>
*/

int main() {
	//Initialze a seed for randomness
	std::srand(static_cast<unsigned>(time(NULL)));

	// Initialize Game Engine
	Game game;
	
	// Game Loop
	while (game.running() && !game.getEndGame()) {

		// Event polling
		game.update();

		// Rendering
		game.render();
		
	}

	return 0;
}