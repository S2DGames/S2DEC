#pragma once

#include <iostream>
#include "SFML/Graphics/Transformable.hpp"
#include "Box2D/Dynamics/b2Body.h"
#include "Util.h"

using std::cerr;
using std::endl;

namespace S2D{
	//moves an sfml tranformable to a box2d body's position
	void movesfTob2(sf::Transformable* t, b2Body* b){
		if(t != nullptr && b != nullptr){
			b2Vec2 b2Position = b->GetPosition();
			t->setPosition(b2Position.x * SCALE, b2Position.y * SCALE);
		}else{
			cerr << "null pointer found when moving image to body position" << endl;
		}
	}

	template<typename T>
	b2Vec2 sfTob2(sf::Vector2<T> vec){
		return{vec.x / SCALE, vec.y / SCALE};
	}

	sf::Vector2f b2Tosf(b2Vec2 vec){
		return{vec.x * SCALE, vec.y * SCALE};
	}
}