//
//  Particle.cpp
//  Particle Explosion Simulation
//
//  Created by Shivam Pandey
//  Copyright © 2018 Shivam Pandey. All rights reserved.
//

#include "Particle.hpp"

Particle::Particle() : m_x(0),m_y(0)  {
	init();
}

void Particle::init()   {
	
	m_x = 0;
	m_y = 0;
	m_direction = (2.0 * M_PI * rand())/RAND_MAX;
	m_speed = (0.04 * rand())/RAND_MAX;
	m_speed *= m_speed;
}

void Particle::updatePos(int interval)  {
	
//	m_direction += interval * 0.0004;   UNCOMMENT THIS TO GET A SPIRAL MOTION
	
	double xspeed = m_speed * cos(m_direction);
	double yspeed = m_speed * sin(m_direction);
	
	m_x += xspeed * interval;
	m_y += yspeed * interval ;
	
	if(m_x < -1 or m_x > 1 or m_y < -1 or m_y > 1) init();
}

Particle::~Particle()  {}
