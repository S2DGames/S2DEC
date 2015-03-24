#include "Component.h"

namespace S2D{

	class ShipComponent : public Component{
	private:
		ShipPhysics* shipPhysics{nullptr};
		sf::Sprite sprite;
		sf::Texture texture;	
	public:
		ShipComponent(){
	
		}
		
		void init(){
			if(owner->hasComponent<ShipComponent>()){
				shipPhysics = &owner->getComponent<ShipPhysics>();
			}else{
				cerr << &owner->getName() << ": ShipPhysics component missing" << endl;
			}
		}
		
		bool update(sf::Time frameTime){
			if(shipPhysics != nullptr){
				sprite.setPosition(shipPhysics.getPosition());	
			}	
		}
	}
}
