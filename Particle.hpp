//
//  Particle.hpp
//  Particle Explosion Simulation
//
//  Created by Shivam Pandey
//  Copyright © 2018 Shivam Pandey. All rights reserved.
//

#ifndef Particle_hpp
#define Particle_hpp

#include <stdio.h>
#include <iostream>
#include <SDL.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

class Particle {

public:
	double m_x;
	double m_y;

private:
	double m_speed;
	double m_direction;

private:
	void init();
	
public:
	Particle();
	void updatePos(int);
	virtual ~Particle();
	
};

#endif /* Particle_hpp */
