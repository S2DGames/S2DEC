#include "EnemySpawner.h"
#include "Enemy.h"

#include <iostream>

using std::cout;
using std::endl;

void Enemy::kill() {
	((EnemySpawner*)spawner)->enemyDied();
	this->owner->destroy();
}