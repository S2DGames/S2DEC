#include "EnemyMovement.h"
#include "EnemyPhysics.h"

EnemyMovement::EnemyMovement(Game* game, HackerPhysics* player, Behavior behavier, sf::Vector2f spawn){
	this->game = game;
	this->player = player;
	currentBehavior = behavier;
	spawnPoint = spawn;
}

EnemyMovement::EnemyMovement(Game* game, HackerPhysics* player, Behavior behavier, sf::Vector2f patrolStart, sf::Vector2f patrolEnd){
	this->game = game;
	this->player = player;
	currentBehavior = behavier;
	spawnPoint = patrolStart;
	if (patrolStart.x < patrolEnd.x){
		this->patrolStart = patrolStart;
		this->patrolEnd = patrolEnd;
	}
	else{
		this->patrolStart = patrolEnd;
		this->patrolEnd = patrolStart;
	}

}

void EnemyMovement::init(){
	if (currentBehavior == patrol){
		if (patrolStart.x < patrolEnd.x)
			direction = 1;
		else
			direction = -1;
	}
}

void EnemyMovement::onStart(){
	enemyPhysics = &owner->getComponent<EnemyPhysics>();
}

void EnemyMovement::update(sf::Time frameTime){
	if (currentBehavior == patrol){
		if (enemyPhysics->getPosition().x <= patrolStart.x){
			direction = 1;
		} else if(enemyPhysics->getPosition().x >= patrolEnd.x){
			direction = -1;
		}
	}
	else if (currentBehavior == moveToPlayer){
		if (enemyPhysics->getPosition().x <= player->getPosition().x)
			direction = 1;
		else
			direction = -1;
	}
	else if (currentBehavior == stand){
		direction = 0;
	}
}

float EnemyMovement::getVelocity() const{
	return(speed * direction);
}

sf::Vector2f EnemyMovement::getSpawn() const{
	return(spawnPoint);
}

void EnemyMovement::setSpeed(float newSpeed){
	speed = newSpeed;
}

void EnemyMovement::setPatrolStart(sf::Vector2f startPoint){
	patrolStart = startPoint;
}

void EnemyMovement::setPatrolEnd(sf::Vector2f endPoint){
	patrolEnd = endPoint;
}