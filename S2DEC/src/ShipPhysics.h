#include "Box2D/Dynamics/b2World.h"
#include "Component.h"
#include "ShipControls.h"

namespace S2D{
	class ShipPhysics : public Component{
	private:
		ShipControls* shipControls{nullptr};
		b2World* world{nullptr};
		b2Body* body{nullptr};
		b2BodyDef bodyDef;
		b2FixtureDef fixtureDef;

	public:
		ShipPhysics(b2World* world) : world(world){
			body = world->CreateBody(&bodyDef);
			body->SetUserData(this);
		}

		sf::Vector2f getPosition() const{
			return{bodyDef.position.x, bodyDef.position.x};
		}

		void init() override{
			if(owner->hasComponent<ShipControls>()){
				shipControls = &owner->getComponent<ShipControls>();
			}else{
				cerr << owner->getName() << ": ShipPhysics component missing" << endl;
			}
		}

		bool update(sf::Time frameTime) override{
			//check shipControls
			return false;
		}

		void beginCollision(Component* collidedComponent, b2Contact* contact) override{

		}

		void endCollision(Component* collidedComponent, b2Contact* contact) override{

		}
	};
}