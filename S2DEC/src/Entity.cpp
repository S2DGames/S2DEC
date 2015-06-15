// Copyright (C) 2015 Doug Madden (dmadden772@gmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
#include "Entity.h"
#include "EntityManager.h"

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