#include "Physics.h"

using namespace S2D;

Physics::Physics(Entity* entity, b2BodyDef bodyDef) : Component("Physics"), Position({0.0, 0.0}, 10), owner(entity){
	body = nullptr;
	world = nullptr;
}

Physics::~Physics(){

}

void Physics::init(b2World* world){
	this->world = world;
	body = world->CreateBody(&bodyDef);
	body->SetUserData(this);
	for(auto it : fixtureDefs){
		(body->CreateFixture(&it.second))->SetUserData(this);
	}
}

const bool Physics::hasPosition(){
	return true;
}

bool Physics::addFixture(string name, b2FixtureDef fixtureDef){
	if(fixtureDefs.count(name) == 0){
		fixtureDefs[name] = fixtureDef;
		return true;
	}
	return false;
}

void Physics::beginCollision(Physics* physicsComponent, b2Contact* contact){
	owner->beginCollision(physicsComponent, contact);
}

void Physics::endCollision(Physics* physicsComponent, b2Contact* contact){
	owner->endCollision(physicsComponent, contact);
}