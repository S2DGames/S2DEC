#pragma once

#include "Entity.h"
#include "CompareEntityZ.h"
#include "SFML/System/Clock.hpp"

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
					return !entity->isAlive();
				}),
				std::end(entities)
			);
		}

		void zOrderModified(){
			zOrderChanged = true;
		}
	};

}