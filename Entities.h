#pragma once

#include "ofMain.h"

class RoundEntity {
	public:
		/// Virual function to be implemented by the child classes to draw the entity each frame. Do not modify this!
		virtual void draw() {};
		
		/// Virual function to be implemented by the child classes to update attributes of the entity each frame. Do not modify this!
		virtual void doUpdatePosition() {};

		/// Determines if the entity is colliding with any wall and performs
		/// collision by changing the velocity accordingly.
		///	This is already implemented so you do not need to change it.
		void doWallsCollision();

		/// Returns if the entity passed to the function is colliding with this entity.
		/// Notice that both entities are circles.Therefore to determine if both are
		///	colliding you can use the addition of the radiusesand the distances from
		///	their center(position) as we did before in this course to determine if two
		///	circles were overlapping!
		///
		///	This function returns true if the two entities are colliding and false otherwise.
		///	Place this function's definition in the Entities.cpp file.
		bool isCollidingWithRoundEntity(const RoundEntity&);

		/// Position of the entity as a vector of 2 dimensions
		ofVec2f position;
		/// Velocity of the entity as a vector of 2 dimensions
		ofVec2f velocity;
		/// Radius of the entity (used to draw the circle in 2d)
		float radius;
};

class RoundObstacle : public RoundEntity {
	public:
		/// Constructor. Do not modify this.
		RoundObstacle();

		/// Implementing virtual method. Do not modify this!
		void draw();
};

class RoundParticle: public RoundEntity {
public:
	/// Main constructor. Here the particle is intialized with a random location and velocity. Do not modify this!
	RoundParticle();

	/// Implementing virtual method (refer to RoundEntity for details). Do not modify this!
	void draw();

	/// Implementing virtual method (refer to RoundEntity for details). Do not modify this!
	void doUpdatePosition();

	/// The goal of this function is to perform attraction to mouse location. In other words modify
	/// the velocity of the particle to make it move towards the mouse pointer.
	/// You need to change the particle velocity to sort of move towards the mouse.
	/// You can get the mouse x and y position by calling ofGetMouseX() and ofGetMouseY()
	void doAttractToMouse();

	/// Performs collision with a particle (updating the particle's velocity)
	/// Here you need to handle the collision between two particles, that is to say,
	/// update the velocity of each particle (change direction).
	void doCollisionWithRoundEntity(RoundParticle&);

	/// Performs collision with an obstacle (updating the particle's velocity)
	/// Here you need to handle the collision between a particle and an obstacle.
	/// Notice the obstacle won't move after a collision. You can assume obstacle are always fixed.
	/// Therefore only the particle velocity (direction) has to be updated.
	void doCollisionWithRoundEntity(const RoundObstacle&);

	/// Repel particles from round obstacle. Do not modify this!
	void doRepelFromRoundObstacle(const RoundObstacle& obstacle);
};