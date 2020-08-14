#include "Entities.h"
#include "ProjectConfig.h"
#include "math.h"

// ------------------ ROUND ENTITY DEFINITIONS --------------------

void RoundEntity::doWallsCollision() {
	bool flip;
	// Verifies x component
	flip = false;
	flip = flip | (velocity.x < 0 && position.x <= radius);
	flip = flip | (velocity.x > 0 && position.x >= ofGetWidth() - radius);
	if (flip) velocity.x = -velocity.x;
	// Verifies y component
	flip = false;
	flip = flip | (velocity.y < 0 && position.y <= radius);
	flip = flip | (velocity.y > 0 && position.y >= ofGetHeight() - radius);
	if (flip) velocity.y = -velocity.y;
}

bool RoundEntity::isCollidingWithRoundEntity(const RoundEntity& entity) {
	// TODO: You must complete this function. You are free to modify it at will. Review Entities.h for more details

	// if (sqrt(((position.x - entity.position.x) * (position.x - entity.position.x)) + ((position.y - entity.position.y) * (position.y - entity.position.y))) <= (radius + entity.radius))

	// The following if statement will move one circle if there is any overlap to prevent "clumping" together
	if (position.distance(entity.position) < radius + entity.radius){
		
		float angle = atan2(position.y - entity.position.y, position.x - entity.position.x);
		float distToMove = radius + entity.radius - position.distance(entity.position);
		
		ofVec2f moveVec;
		moveVec.x = cos(angle) * distToMove;
		moveVec.y = sin(angle) * distToMove;
		
		position = moveVec + position;
	}


	// This if statement returns true if the distance between the two particles is less than or equal to their combined radii
	if (position.distance(entity.position) <= radius + entity.radius)
		return true;
	
	return false;
}

// -------------------- PARTICLE DEFINITIONS ----------------------

RoundParticle::RoundParticle(){
	// Radius init
	radius = ProjectConfig::PARTICLE_SIZE;
	// Sets random position
	position.x = ofRandomWidth();
	position.y = ofRandomHeight();
	// Sets random velocity
	velocity.x = ofRandom(-ProjectConfig::MAX_INITIAL_VELOCITY, ProjectConfig::MAX_INITIAL_VELOCITY);
	velocity.y = ofRandom(-ProjectConfig::MAX_INITIAL_VELOCITY, ProjectConfig::MAX_INITIAL_VELOCITY);
}

void RoundParticle::doUpdatePosition(){
	position += velocity;
}
//
void RoundParticle::draw(){
	ofSetColor(208, 255, 63);
	ofDrawCircle(position, radius);
}

void RoundParticle::doAttractToMouse() {
	// TODO: You must complete this function. You are free to modify it at will. Review Entities.h for more details
	

	// Attract to mouse function -> if mouse is within attract distance, creates a unit vector in direction of mouse from particle,
	// creates normalized (unitized) vector in direction of mouse factored at the ATTRACTION_STRENGTH. Then multiplies this unit 
	// vector by length of velocity vector to avoid changing speed

	ofVec2f mouseLoc;
	mouseLoc.x = (float)ofGetMouseX();
	mouseLoc.y = (float)ofGetMouseY();
	
	if (position.distance(mouseLoc) > ProjectConfig::MIN_ATTRACTION_DISTANCE)
		return;

	ofVec2f force = (position - mouseLoc).getNormalized();
	float lambda = ProjectConfig::ATTRACTION_STRENGTH;

	velocity = ((1 - lambda) * velocity - force * lambda).getNormalized() * velocity.length();
	
}

void RoundParticle::doCollisionWithRoundEntity(RoundParticle& particle) {
	// TODO: You must complete this function. You are free to modify it at will. Review Entities.h for more details


	//ofVec2f tangentVec;
	//tangentVec.y = -(particle.position.x - position.x);
	//tangentVec.x = particle.position.y - position.y;
	//tangentVec = tangentVec.normalize();

	//ofVec2f relVelocityVec;
	//relVelocityVec.x = (velocity.x - particle.velocity.x);
	//relVelocityVec.y = (velocity.y - particle.velocity.y);

	//float len = relVelocityVec.dot(tangentVec);

	//ofVec2f tanVelComponent;
	//tanVelComponent = tangentVec * len;

	//ofVec2f velPerpToTan = relVelocityVec - tanVelComponent;

	//velocity.x -= velPerpToTan.x;
	//velocity.y -= velPerpToTan.y;


	// *********************************************************************************** //
	// SAS: Not sure if this is working *quite* the way I would like - some more to do here
	// *********************************************************************************** //


	//ofVec2f collisionVec;
	//collisionVec.x = particle.position.x - position.x;
	//collisionVec.y = particle.position.y - position.y;

	//collisionVec = collisionVec.normalize();

	//ofVec2f relVelocity;
	//relVelocity.x = velocity.x - particle.velocity.x;
	//relVelocity.y = velocity.y - particle.velocity.y;

	//float speed = relVelocity.x * collisionVec.x + relVelocity.y * collisionVec.y;

	//velocity.x -= (speed * collisionVec.x);
	//velocity.y -= (speed * collisionVec.y);

	//particle.velocity.x += (speed * collisionVec.x);
	//particle.velocity.y += (speed * collisionVec.y);

	float speed = velocity.length();

	ofVec2f normalVec;
	normalVec.x = position.x - particle.position.x;
	normalVec.y = position.y - particle.position.y;
	//normalVec = normalVec.getNormalized();

	velocity = velocity + normalVec;
	velocity = velocity.getNormalized();

	velocity = velocity * speed;

	// This seems to work well. Create a unitized vector normal to the direction of collision. New velocity is original velocity minus
	// twice the dot product of velocity and normal vector in direction of normal vector

	//ofVec2f newVel = velocity - 2 * (velocity.dot(normalVec)) * normalVec;
	//velocity = newVel.getNormalized();
	// velocity = velocity * speed;
}

void RoundParticle::doCollisionWithRoundEntity(const RoundObstacle& obstacle) {
	// TODO: You must complete this function. You are free to modify it at will. Review Entities.h for more details
	//ofVec2f tangentVec;
	//tangentVec.y = -(obstacle.position.x - position.x);
	//tangentVec.x = obstacle.position.y - position.y;
	//tangentVec = tangentVec.normalize();

	//ofVec2f relVelocityVec;
	//relVelocityVec.x = (velocity.x);
	//relVelocityVec.y = (velocity.y);

	//float len = relVelocityVec.dot(tangentVec);

	//ofVec2f tanVelComponent;
	//tanVelComponent = tangentVec * len;

	//ofVec2f velPerpToTan = relVelocityVec - tanVelComponent;

	//velocity.x -= velPerpToTan.x;
	//velocity.y -= velPerpToTan.y;

	//ofVec2f collisionVec;
	//collisionVec.x = obstacle.position.x - position.x;
	//collisionVec.y = obstacle.position.y - position.y;

	//collisionVec = collisionVec.normalize();

	//ofVec2f tangentVec;
	//tangentVec.x = collisionVec.y;
	//tangentVec.y = collisionVec.x;

	//float speed = relVelocity.x * collisionVec.x + relVelocity.y * collisionVec.y;

	//velocity.x -= (speed * collisionVec.x);
	//velocity.y -= (speed * collisionVec.y);

	// This seems to work well. Create a unitized vector normal to the direction of collision. New velocity is original velocity minus
	// twice the dot product of velocity and normal vector in direction of normal vector

	// float speed = velocity.length();

	//ofVec2f normalVec;
	//normalVec.x = obstacle.position.x - position.x;
	//normalVec.y = obstacle.position.y - position.y;
	//normalVec = normalVec.getNormalized();

	//ofVec2f newVel = velocity - 2 * (velocity.dot(normalVec)) * normalVec;
	//velocity = newVel;

	// velocity = velocity * speed;

	float speed = velocity.length();

	ofVec2f normalVec;
	normalVec.x = position.x - obstacle.position.x;
	normalVec.y = position.y - obstacle.position.y;
	//normalVec = normalVec.getNormalized();

	velocity = velocity + normalVec;
	velocity = velocity.getNormalized();

	velocity = velocity * speed;

}

void RoundParticle::doRepelFromRoundObstacle(const RoundObstacle& obstacle) {
	ofVec2f point = obstacle.position;
	if (position.distance(point) < ProjectConfig::MAX_REPEL_DISTANCE)
		return;
	ofVec2f force = (position - point).getNormalized();
	float lambda = ProjectConfig::REPEL_STRENGTH;
	// Changes direction without increasing velocity
	velocity = ((1 - lambda) * velocity + force * lambda).getNormalized() * velocity.length();
}

// -------------------- OBSTACLE DEFINITIONS ----------------------

RoundObstacle::RoundObstacle() {
	// Random radius
	radius = ofRandom(20, 50);
	// Sets random position
	position.x = ofRandomWidth();
	position.y = ofRandomHeight();
}

void RoundObstacle::draw() {
	ofSetColor(255, 0, 0);
	ofDrawCircle(position, radius);
}