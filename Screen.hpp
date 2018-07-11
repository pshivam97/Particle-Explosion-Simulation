//
//  Screen.hpp
//  Particle Explosion Simulation
//
//  Created by Shivam Pandey
//  Copyright © 2018 Shivam Pandey. All rights reserved.
//

#ifndef Screen_hpp
#define Screen_hpp

//#pragma once

#include <stdio.h>
#include <iostream>
#include <SDL.h>

using namespace std;

class Screen {

private:
	SDL_Window * m_window;
	SDL_Renderer * m_renderer;
	SDL_Texture * m_texture;
	Uint32 * m_buffer1;
	Uint32 * m_buffer2;
	
public:
	const static int SCREEN_WIDTH = 1000;
	const static int SCREEN_HEIGHT = 700;
	
public:
	Screen();
	bool init();
	void setPixel(int x , int y , Uint8 red, Uint8 green, Uint8 blue);
	void update();
	bool processEvents();
	void close();
	void blur();
};

#endif /* Screen_hpp */

