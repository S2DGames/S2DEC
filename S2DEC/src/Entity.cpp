#include "Entity.h"

using namespace S2D;

Entity::Entity(string name) : id(currentId), name(name){
	currentId++;
}

const int Entity::getId(){
	return id;
}

const string Entity::getName(){
	return name;
}

void Entity::onStart(){
	for(auto& component : components){
		component->onStart();
	}
}

bool Entity::update(sf::Time frameTime){
	for(auto& component : components){
		component->update(frameTime);
	}
	return false;
}

void Entity::draw(sf::RenderTarget& target){
	for(auto& component : components){
		component->draw(target);
	}
}