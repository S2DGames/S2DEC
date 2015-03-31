#pragma once

#include "Entity.h"

namespace S2D{

	class EntityManager{
	private:
		vector<unique_ptr<Entity>> entities;

	public:
		Entity& createEntity(string name){
			Entity* entity = new Entity(name);
			unique_ptr<Entity> uniqueEntityPtr{entity};
			entities.emplace_back(move(uniqueEntityPtr));
			return *entity;
		}

		void onStart(){
			for(auto& entity : entities){
				entity->onStart();
			}
		}

		void update(sf::Clock& frameClock){
			for(auto& entity : entities){
				entity->update(frameClock.getElapsedTime());
			}
		}

		void draw(sf::RenderTarget& target){
			for(auto& entity : entities){
				entity->draw(target);
			}
		}
	};

}