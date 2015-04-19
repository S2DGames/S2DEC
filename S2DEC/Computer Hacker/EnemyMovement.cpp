#include "EnemyMovement.h"
#include "EnemyPhysics.h"
#include "HackerPhysics.h"

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
	if (currentBehavior == boss1)
		bossManager();
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

void EnemyMovement::moveToCenter() {
	if (enemyPhysics->getPosition().x < 630.0f)
		direction = 1;
	else if (enemyPhysics->getPosition().x > 650.0f)
		direction = -1;
	else if (enemyPhysics->getPosition().x > 630.0f && enemyPhysics->getPosition().x < 650.0f)
		direction = 0;
}

void EnemyMovement::setCircuit(vector<sf::Vector2f> points) {
	
	if (enemyPhysics->getPosition().x >= points[nodeCounter].x - 1.0f && enemyPhysics->getPosition().x <= points[nodeCounter].x + 1.0f){
		direction = 0;
		if (timer > 0)
			timer--;
		else
		{
			timer = 120;
			nodeCounter++;
			if (enemyPhysics->getPosition().y > points[nodeCounter].y)
				enemyPhysics->jump();
			if (nodeCounter >= points.size()-4)
				nodeCounter = 0;
		}
	}
	else if (enemyPhysics->getPosition().x < points[nodeCounter].x){
		direction = 1;
	}
	else if (enemyPhysics->getPosition().x > points[nodeCounter].x){
		direction = -1;
	}
}

void EnemyMovement::bossManager(){
	setCircuit(mapPoints);
}

void EnemyMovement::setMapPointVectors(vector<sf::Vector2f> mapPoints){
	this->mapPoints = mapPoints;
}