#include "Entity.h"

namespace S2D{

	class EntityManager{
	private:
		vector<unique_ptr<Entity>> entities;

	public:
		void addEntity(Entity* entity){
			unique_ptr<Entity> uniqueEntityPtr{entity};
			entities.emplace_back(move(uniqueEntityPtr));
		}

		void update(const sf::Time frameTime){
			for(auto& entity : entities){
				entity->update(frameTime);
			}
		}

		void draw(sf::RenderTarget& target){
			for(auto& entity : entities){
				entity->draw(target);
			}
		}
	};

}