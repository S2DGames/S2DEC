#include "Entity.h"

namespace S2D{

	class EntityManager{
	private:
		vector<unique_ptr<Entity>> entities;

	public:

		void update(const sf::Time frameTime){
			for(auto& entity : entities){
				entity->update(frameTime);
			}
		}
	};

}