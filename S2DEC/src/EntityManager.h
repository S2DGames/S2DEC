#pragma once

#include "Entity.h"
#include "CompareEntityZ.h"

using std::sort;

namespace S2D{

	class EntityManager{
	private:
		vector<unique_ptr<Entity>> entities;
		
		bool iterating{false};
		vector<Entity*> queuedEntites;

		void addQueuedComponents(){
			for(auto entity : queuedEntites){
				unique_ptr<Entity> uniqueEntityPtr{entity};
				entities.emplace_back(move(uniqueEntityPtr));
			}
			queuedEntites.clear();
		}

	public:
		Entity& createEntity(string name){
			Entity* entity = new Entity(name);
			if(!iterating){
				unique_ptr<Entity> uniqueEntityPtr{entity};
				entities.emplace_back(move(uniqueEntityPtr));
			}else{
				queuedEntites.emplace_back(entity);
			}
			return *entity;
		}

		void onStart(){
			for(auto& entity : entities){
				entity->onStart();
			}
		}

		void update(sf::Clock& frameClock){
			entities.erase(std::remove_if(std::begin(entities), std::end(entities), [](const std::unique_ptr<Entity>& mEntity){return !mEntity->isAlive();}), std::end(entities));

			iterating = true;
			for(auto& entity : entities){
				entity->update(frameClock.getElapsedTime());
			}
			iterating = false;
			addQueuedComponents();
		}

		void draw(sf::RenderTarget& target){
			sort(entities.begin(), entities.end(), CompareZ);
			for(auto& entity : entities){
				entity->draw(target);
			}
		}
	};

}