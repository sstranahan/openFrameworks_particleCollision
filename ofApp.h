#pragma once

#include "ofMain.h"
#include "Entities.h"

class ofApp : public ofBaseApp{
public:
	///	This function is called at the beginning of your app.
	/// You need to complete this function to do the following:
	/// You are required to add PARTICLES_COUNT RoundParticle to the particles vector
	/// You are required to add OBSTACLES_COUNT RoundObstacle to the obstacles vector
	/// Consider loops!
	void setup(); 

	/// This function has all the importat flow for updating the simulation. Do not modify this function
	/// unless you are sure what you are doing.
	void update();

	/// This function is used for drawing the entire simulation. Do not modify this function unless you
	/// are sure what you are doing. You must call each of the particles and obstacles draw function in order
	/// to see something on the screen. Consider loops!
	void draw();

private:
	/// Vector of all particles in the game. This is empty initially!!!
	vector<RoundParticle> particles;
	/// Vector of all obstacles in the game. This is empty initially!!!
	vector<RoundObstacle> obstacles;
};
