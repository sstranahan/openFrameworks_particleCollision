#include "ofApp.h"
#include "ProjectConfig.h"

// Simulation configuration values
int ProjectConfig::PARTICLES_COUNT = 100;
int ProjectConfig::OBSTACLES_COUNT = 2;
int ProjectConfig::PARTICLE_SIZE = 10;
float ProjectConfig::MAX_INITIAL_VELOCITY = 3;
float ProjectConfig::MIN_ATTRACTION_DISTANCE = 200;
float ProjectConfig::MAX_REPEL_DISTANCE = 20;
float ProjectConfig::ATTRACTION_STRENGTH =  5e-1;
float ProjectConfig::REPEL_STRENGTH = 2e-2;

void ofApp::setup(){
	// TODO: You must complete this function. You are free to modify it at will. Review ofApp.h for more details
	// SAS: Finished

	for (int i = 0; i < ProjectConfig::PARTICLES_COUNT; i++) {
		RoundParticle temp;
		particles.push_back(temp);
	}

	for (int i = 0; i < ProjectConfig::OBSTACLES_COUNT; i++) {
		RoundObstacle temp;
		obstacles.push_back(temp);
	}
}

void ofApp::update(){
	// Verifies collisions
	for (int i = 0; i < particles.size(); i++) {
		// Performs attraction to mouse
		particles[i].doAttractToMouse();
		// Verifies collisions to other particles
		for (int j = i + 1; j < particles.size(); j++) {
			// Check whether they are colliding
			if (particles[i].isCollidingWithRoundEntity(particles[j])) {
				// Creates a copy to avoid problems when updating velocities
				RoundParticle temp = particles[i]; 
				// Performs collision update
				particles[i].doCollisionWithRoundEntity(particles[j]);
				particles[j].doCollisionWithRoundEntity(temp);
			}
		}
		// Verifies collisions to obstacles
		for (int j = 0; j < obstacles.size(); j++) {
			// Performs repel from obstacles
			particles[i].doRepelFromRoundObstacle(obstacles[j]);
			// Check whether they are colliding
			if (particles[i].isCollidingWithRoundEntity(obstacles[j])) {
				// Performs collision update
				particles[i].doCollisionWithRoundEntity(obstacles[j]);
			}
		}
		// Verifies collisions to walls
		particles[i].doWallsCollision();
	}
	// Updates position
	for (int i = 0; i < particles.size(); i++) {
		particles[i].doUpdatePosition();
	}
}

void ofApp::draw(){
	// TODO: You must complete this function. You are free to modify it at will. Review ofApp.h for more details
	// SAS: Finished

	for (int i = 0; i < particles.size(); i++) {
		particles[i].draw();
	}

	for (int i = 0; i < obstacles.size(); i++) {
		obstacles[i].draw();
	}

}