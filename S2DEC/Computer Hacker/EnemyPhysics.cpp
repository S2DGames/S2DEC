#include "EnemyPhysics.h"
#include "HackerPhysics.h"
#include "ComputerAttack.h"

EnemyPhysics::EnemyPhysics(Game* game){
	this->game = game;
	bodyDef.type = b2_dynamicBody;
	shape.SetAsBox(50.0f / SCALE / 2.0f, 75.0f / SCALE / 2.0f);
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.1f;
	position = sf::Vector2f(100.0f, 100.0f);

}

EnemyPhysics::~EnemyPhysics(){
	game->DestroyBody(body);
}

void EnemyPhysics::init() {
	if (owner->hasComponent<EnemyMovement>()){
		enemyMovement = &owner->getComponent<EnemyMovement>();
		position = enemyMovement->getSpawn();
		bodyDef.position = { position.x / SCALE, position.y / SCALE };
	}
	else{
		cerr << owner->getName() << ": EnemyMovement component missing" << endl;
	}

	body = game->CreateBody(&bodyDef);
	body->SetUserData(this);
	body->SetFixedRotation(true);
	body->CreateFixture(&fixtureDef);
}

void EnemyPhysics::onStart() {
}

void EnemyPhysics::update(sf::Time frameTime) {
	body->SetLinearVelocity({ enemyMovement->getVelocity(), body->GetLinearVelocity().y });

}

sf::Vector2f EnemyPhysics::getPosition(){
	return{ body->GetPosition().x * SCALE, body->GetPosition().y * SCALE};
}

void EnemyPhysics::beginCollision(Component* collidedComponent, b2Contact* contact){
	if (auto f = dynamic_cast<Floor*>(collidedComponent)){
		onGround = true;
	}

	if (auto h = dynamic_cast<HackerPhysics*>(collidedComponent)){
		if (onGround){
			jump();
		}	
	}

	if(auto c = dynamic_cast<ComputerAttack*>(collidedComponent)){
		if(owner->hasComponent<Health>()){
			owner->getComponent<Health>().damage(1);
		}
	}
}

void EnemyPhysics::endCollision(Component* collidedComponent, b2Contact* contact){
	if (auto f = dynamic_cast<Floor*>(collidedComponent)){
		int i = 0;
		for (b2ContactEdge* ce = body->GetContactList(); ce; ce = ce->next){
			Component* currentlyCollided = (Component*)ce->other->GetUserData();
			i++;
		}

		if (i == 1){
			onGround = false;
		}
	}
}

void EnemyPhysics::jump(){
	if (onGround){
		float impulse = body->GetMass() * -13.0f;
		body->ApplyLinearImpulse({ 0, impulse }, body->GetWorldCenter(), true);
	}
}
