#include "EnemySpawner.h"
#include "Enemy.h"

#include <iostream>

using std::cout;
using std::endl;

void Enemy::kill() {
	((EnemySpawner*)spawner)->enemyDied();
	try {
		this->owner->destroy();
	}
	catch (std::exception e) {
		//cout << ""
	}
}