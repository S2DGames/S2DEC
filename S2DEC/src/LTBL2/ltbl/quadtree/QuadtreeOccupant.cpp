#include "QuadtreeOccupant.h"

#include "QuadtreeNode.h"

#include <assert.h>

using namespace ltbl;

void QuadtreeOccupant::quadtreeUpdate() {
	if (_pQuadtreeNode != nullptr)
		_pQuadtreeNode->update(this);
}

void QuadtreeOccupant::quadtreeRemove() {
	if (_pQuadtreeNode != nullptr)
		_pQuadtreeNode->remove(this);
}

void QuadtreeOccupant::setAwake(bool isAwake) {
	this->_isAwake = isAwake;
}

bool QuadtreeOccupant::isAwake() {
	return this->_isAwake;
}

void QuadtreeOccupant::toggleAwake() {
	if (this->isAwake()) {
		this->setAwake(false);
	}
	else {
		this->setAwake(true);
	}

}

void QuadtreeOccupant::setTurnedOn(bool turnedOn) {
	this->_isTurnedOn = turnedOn;
}

bool QuadtreeOccupant::isTurnedOn() {
	return this->_isTurnedOn;
}


void QuadtreeOccupant::toggleTurnedOn() {
	if (this->isTurnedOn()) {
		this->_isTurnedOn = false;
	}
	else {
		this->_isTurnedOn = true;
	}
}