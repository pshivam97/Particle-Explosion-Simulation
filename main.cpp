/*  main.cpp
//
//  Particle Explosion Simulation
//
//  Created by Shivam Pandey.
//  Copyright © 2018 Shivam Pandey. All rights reserved.
*/

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "Screen.hpp"
#include "Swarm.hpp"

using namespace std;

int main(int argc, const char * argv[]) {

	Screen screen; // Screen instance created
	Swarm swarm;  // Swarm instance created

	if(!screen.init()) {   /* SDL Initialization */
		cerr << "Error Initializing SDL !!" << endl;
		return EXIT_FAILURE;
	}

	while(true)  {   /* GAME LOOP */

		int time_elapsed_milliseconds = SDL_GetTicks();
		
		swarm.update(time_elapsed_milliseconds);
		
		unsigned char green = 128 * (1 + sin(time_elapsed_milliseconds * 0.0001));
		unsigned char red = 128 * (1 + sin(time_elapsed_milliseconds * 0.0002));
		unsigned char blue = 128 * (1 + sin(time_elapsed_milliseconds * 0.0003));

		const Particle * const pParticles = swarm.getParticles();
		
		for(int i = 0 ; i < Swarm::NPARTICLES ; i++)  {

			Particle particle = pParticles[i];

			int x = (particle.m_x + 1) * (Screen::SCREEN_WIDTH/2);
			int y = particle.m_y * (Screen::SCREEN_WIDTH/2) + Screen::SCREEN_HEIGHT/2;

			screen.setPixel(x, y, red, green, blue);
		}
		
		screen.blur();
		screen.update(); // masking the texture over the renderer and then rendering over the screen/display

		if(!screen.processEvents()) break;
	}

	screen.close();

	return EXIT_SUCCESS;
}
