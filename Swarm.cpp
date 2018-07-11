//
//  Swarm.cpp
//  Particle Explosion Simulation
//
//  Created by Shivam Pandey
//  Copyright © 2018 Shivam Pandey. All rights reserved.
//

#include "Swarm.hpp"

Swarm::Swarm() : lastTime(0)   {
	m_pParticles = new Particle[NPARTICLES];
	
}
void Swarm::update(int time_elapsed_milliseconds)  {
	
	int interval = time_elapsed_milliseconds - lastTime;
	
	for(int i = 0 ; i < Swarm::NPARTICLES ; i++)
		m_pParticles[i].updatePos(interval);
	
	lastTime = time_elapsed_milliseconds;
}

Swarm::~Swarm() {
	delete [] m_pParticles;
}
