#include "EnemyPhysics.h"

EnemyPhysics::EnemyPhysics(Game* game){
	this->game = game;
	bodyDef.type = b2_dynamicBody;
	shape.SetAsBox(50.0f / SCALE / 2.0f, 75.0f / SCALE / 2.0f);
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.1f;
	position = sf::Vector2f(100.0f, 100.0f);

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

