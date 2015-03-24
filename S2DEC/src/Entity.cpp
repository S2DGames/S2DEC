#include "Entity.h"

using namespace S2D;

Entity::Entity(string name) : id(currentId), name(name){
	currentId++;
}

Entity::~Entity(){

}

const int Entity::getId(){
	return id;
}

const string Entity::getName(){
	return name;
}

bool Entity::update(sf::Time frameTime){
	for(auto& component : components){
		component->update(frameTime);
	}
	return false;
}

bool Entity::draw(sf::RenderTarget& target){
	for(auto& component : components){
		component->draw(target);
	}
	return false;
}