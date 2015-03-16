#include "Entity.h"

using namespace S2D;

Entity::Entity(string name) : id(currentId), name(name){
	currentId++;
}

Entity::~Entity(){

}

const int Entity::getId() {
	return id;
}

const string Entity::getName(){
	return name;
}

bool Entity::addComponent(Component* component){
	return ComponentMaintainer::addComponent(component);
}

bool Entity::update(){
	return false;
}

void Entity::beginCollision(Physics* physicsComponent, b2Contact* contact){

}

void Entity::endCollision(Physics* physicsComponent, b2Contact* contact){

}