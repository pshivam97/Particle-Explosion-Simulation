//
//  Swarm.hpp
//  Particle Explosion Simulation
//
//  Created by Shivam Pandey
//  Copyright © 2018 Shivam Pandey. All rights reserved.
//

#ifndef Swarm_hpp
#define Swarm_hpp

#include <stdio.h>
#include <iostream>
#include <SDL.h>
#include "Particle.hpp"

using namespace std;

class Swarm {

public:
	const static int NPARTICLES = 5000;
	
private:
	Particle * m_pParticles;
	int lastTime;
	
public:
	Swarm();
	const Particle * const getParticles()  { return m_pParticles; }
	void update(int);
	virtual ~Swarm();
};

#endif /* Swarm_hpp */
