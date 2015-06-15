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
#pragma once

#include <iostream>
#include "Entity.h"
#include "CompareEntityZ.h"
#include "SFML/System/Clock.hpp"

using std::cout;
using std::endl;
using std::sort;

namespace S2D{

	class EntityManager{
	private:
		vector<unique_ptr<Entity>> entities{};
		
		bool iterating;
		vector<Entity*> queuedEntites{};

		void addQueuedComponents(){
			for(auto entity : queuedEntites){
				unique_ptr<Entity> uniqueEntityPtr{entity};
				entities.emplace_back(move(uniqueEntityPtr));
			}
			queuedEntites.clear();
		}

		bool zOrderChanged;

	public:
		EntityManager() : zOrderChanged(false), iterating(false){

		}

		Entity& createEntity(string name){
			Entity* entity = new Entity(name, this);
			//only add the entity to the game if we are not currently looping over entities
			if(!iterating){
				unique_ptr<Entity> uniqueEntityPtr{entity};
				entities.emplace_back(move(uniqueEntityPtr));
			}else{
				queuedEntites.emplace_back(entity);
			}
			zOrderChanged = true;
			return *entity;
		}

		void onStart(){
			iterating = true;
			for(auto& entity : entities){
				entity->onStart();
			}
			iterating = false;
		}

		void update(float frameTime){
			removeDeadEntities();
			iterating = true;
			for(auto& entity : entities){
				entity->update(frameTime);
			}
			iterating = false;
			addQueuedComponents();
		}

		void draw(sf::RenderTarget& target){
			if(zOrderChanged){
				sort(entities.begin(), entities.end(), CompareZ);
				zOrderChanged = false;
			}
			iterating = true;
			for(auto& entity : entities){
				entity->draw(target);
			}
			iterating = false;
		}

		void destroyAll(){
			iterating = true;
			for(auto& entity : entities){
				entity->destroy();
			}
			iterating = false;
		}

		void removeDeadEntities(){
			entities.erase(
				std::remove_if(std::begin(entities),
				std::end(entities),
				[](const std::unique_ptr<Entity>& entity){
					if(!entity->isAlive()){
						cout << entity->getName() << " destroyed" << endl;
						return true;
					}
					return false;
				}),
				std::end(entities)
			);
		}

		void zOrderModified(){
			zOrderChanged = true;
		}
	};

}