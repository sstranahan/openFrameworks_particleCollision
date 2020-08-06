#include "Entities.h"
#include "ProjectConfig.h"

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

bool RoundEntity::isCollidingWithRoundEntity(const RoundEntity& entity) const {
	// TODO: You must complete this function. You are free to modify it at will. Review Entities.h for more details

	if (sqrt(((position.x - entity.position.x) * (position.x - entity.position.x)) + ((position.y - entity.position.y) * (position.y - entity.position.y))) <= (radius + entity.radius))
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

void RoundParticle::draw(){
	ofSetColor(208, 255, 63);
	ofDrawCircle(position, radius);
}

void RoundParticle::doAttractToMouse() {
	// TODO: You must complete this function. You are free to modify it at will. Review Entities.h for more details

	ofVec2f point = position;
	if (position.distance(point) > ProjectConfig::MIN_ATTRACTION_DISTANCE)
		return;
	ofVec2f force = (position - point).getNormalized();
	float lambda = ProjectConfig::ATTRACTION_STRENGTH;
	// Changes direction without increasing velocity
	velocity = ((1 - lambda) * velocity + force * lambda).getNormalized() * velocity.length();
}

void RoundParticle::doCollisionWithRoundEntity(const RoundParticle& particle) {
	// TODO: You must complete this function. You are free to modify it at will. Review Entities.h for more details
	velocity.x = -1 * velocity.x;
	velocity.y = -1 * velocity.y;
}

void RoundParticle::doCollisionWithRoundEntity(const RoundObstacle& obstacle) {
	// TODO: You must complete this function. You are free to modify it at will. Review Entities.h for more details
	velocity.x = -1 * velocity.x;
	velocity.y = -1 * velocity.y;
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