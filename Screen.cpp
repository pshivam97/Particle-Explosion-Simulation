//
//  Screen.cpp
//  Particle Explosion Simulation
//
//  Created by Shivam Pandey
//  Copyright © 2018 Shivam Pandey. All rights reserved.
//
 
#include "Screen.hpp"

Screen::Screen() : m_window(NULL), m_renderer(NULL), m_texture(NULL), m_buffer1(NULL), m_buffer2(NULL){}

bool Screen::init()  {
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0)   {   // Checks whether SDL is successfully initialised or not.
		return false;
	}
	
	/* Creating a SDL Window */
	
	m_window = SDL_CreateWindow("Particle Explosion Simulation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN); // The function "SDL_CreateWindow()" creates a window with title given as first parameter. "SDL_Window" is the type used to identify a window and is declared in "SDL_video.h"
	
	if(m_window == NULL){   // checks whether "SDL_CreateWindow()" creates a window successfully
		SDL_Quit();
		return false;
	}
	
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
	m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);
	
	if(m_renderer == NULL){
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return false;
	}
	
	if(m_texture == NULL){
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return false;
	}
	
	m_buffer1 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
	m_buffer2 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
	memset(m_buffer1, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));  // initializing the buffer
	memset(m_buffer2, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));  // initializing the buffer
	
	return true;
}

void Screen::setPixel(int x , int y , Uint8 red, Uint8 green, Uint8 blue)  {
	
	if(x < 0 or x >= SCREEN_WIDTH or y < 0 or y >= SCREEN_HEIGHT) return;
	
	Uint32 colour = 0;
	
	colour += red;
	colour <<= 8;
	colour += green;
	colour <<= 8;
	colour += blue;
	colour <<= 8;
	colour += 0xFF;
	
	m_buffer1[(y * SCREEN_WIDTH) + x] = colour;
}

void Screen::update()    {
	SDL_UpdateTexture(m_texture, NULL, m_buffer1, SCREEN_WIDTH * sizeof(Uint32));
	SDL_RenderClear(m_renderer);
	SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
	SDL_RenderPresent(m_renderer);
}

bool Screen::processEvents()  {
	
	SDL_Event event;
	
	while(SDL_PollEvent(&event))  {   // "SDL_PollEvent()" returns 1 if there is a pending event or 0 if there are none available.
		if(event.type == SDL_QUIT) {
			return false;
		}
	}
	return true;
}

void Screen::close()   {
	
	delete [] m_buffer1;
	delete [] m_buffer2;
	SDL_DestroyTexture(m_texture);
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Screen::blur()   {
	// Swap the pointers
	Uint32 * tempBuffer;
	tempBuffer = m_buffer1;
	m_buffer1 = m_buffer2;
	m_buffer2 = tempBuffer;
	
	for(int y = 0 ; y < SCREEN_HEIGHT ; y++) {
		for(int x = 0 ; x < SCREEN_WIDTH ; x++)  {
			
			int redTotal = 0;
			int greenTotal = 0;
			int blueTotal = 0;
			
			for (int row = -1; row <= 1; row++)   {
				for (int col = -1 ; col <= 1 ; col++) {
					int currentX = x + col;
					int currentY = y + col;
					
					if(currentX >= 0 and currentX < SCREEN_WIDTH and currentY >= 0 and currentY < SCREEN_HEIGHT)  {
						Uint32 colour = m_buffer2[(currentY * SCREEN_WIDTH) + currentX];
						
						Uint8 red = colour >> 24;
						Uint8 green = colour >> 16;
						Uint8 blue = colour >> 8;
						
						redTotal += red;
						greenTotal += green;
						blueTotal += blue;
					}
				}
			}
			Uint8 red = redTotal/9;
			Uint8 green = greenTotal/9;
			Uint8 blue = blueTotal/9;
			
			setPixel(x, y, red, green, blue);
		}
	}
}
