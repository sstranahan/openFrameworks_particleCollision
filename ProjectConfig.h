#pragma once

/*
	This is class containing the configuration options for the simulation.
	You do not need to modify anything of this, but feel free if you decide to.
*/

class ProjectConfig {
public:
	/// How many particles to create in the simulation
	static int PARTICLES_COUNT;
	/// How many obstacles to create in the simulation
	static int OBSTACLES_COUNT;
	/// Radius of the particles
	static int PARTICLE_SIZE;
	/// Maximum initial velocity of the particles
	static float MAX_INITIAL_VELOCITY;
	/// Minimum distance to the mouse in order to start attracting a particle
	static float MIN_ATTRACTION_DISTANCE;
	/// Maximum distance the obstacles will have an repel effect on any given particle
	static float MAX_REPEL_DISTANCE;
	/// Factor of attraction
	static float ATTRACTION_STRENGTH;
	/// Factor of repel
	static float REPEL_STRENGTH;
};