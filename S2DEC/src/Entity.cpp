#include "Entity.h"
#include "EntityManager.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

using namespace S2D;

const string Entity::getName(){
	return name;
}

void Entity::onStart(){
	for(auto& component : components){
		component->onStart();
	}
}

bool Entity::update(float frameTime){
	iterating = true;
	for(auto& component : components){
		component->update(frameTime);
	}
	iterating = false;
	addQueuedComponents();
	return false;
}

void Entity::draw(sf::RenderTarget& target){
	for(auto& component : components){
		component->draw(target);
	}
}

int Entity::getZ(){
	return z;
}

void Entity::setZ(int newZ){
	z = newZ;
	owner->zOrderModified();
}

const bool Entity::isAlive(){
	return alive;
}

void Entity::destroy(){
	alive = false;
}

//TODO: NOT TESTED
void Entity::addQueuedComponents(){
	for(auto component : queuedComponents){
		unique_ptr<Component> uniqueComponentPtr{component};
		components.emplace_back(move(uniqueComponentPtr));
		componentArray[component->id] = component;
		componentBitset[component->id] = true;
		component->init();
	}
	queuedComponents.clear();
}