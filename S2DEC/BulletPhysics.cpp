#include "BulletPhysics.h"

void BulletPhysics::onStart(){
	sin = std::sin(ship->getAngle() * DEGTORAD);
	cos = std::cos(ship->getAngle() * DEGTORAD);
}