// Copyright (C) 2015 Doug Madden (dmadden772@gmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
#pragma once

//helpful functions that make it easier to convert between sfml and box2d things.
//box2d performs better with smaller numbers so a scale is used and box2d coordinates must be multiplied by the scale to get the sfml coordinates
//box2d also uses the center of an object as its default origin whereas sfml uses the top left. It is easier to move the origin of sfml images so a few functions are provided that do just that.

#include <iostream>
#include "SFML/Graphics/Transformable.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "Box2D/Dynamics/b2Body.h"
#include "Util.h"

using std::cerr;
using std::endl;

namespace S2D{

	//only use this with numbers
	template<typename T>
	T sfTob2(T num){
		return{num / SCALE};
	}

	template<typename T>
	b2Vec2 sfTob2(sf::Vector2<T> vec){
		return{vec.x / SCALE, vec.y / SCALE};
	}

	void movesfTob2(sf::Transformable& t, b2Body* b);

	sf::Vector2f b2Tosf(b2Vec2 vec);

	void setCenter(sf::RectangleShape& rs);
	void setCenter(sf::CircleShape& rs);
	void setSizeAndCenter(sf::RectangleShape& rs, sf::Vector2f size);
	void setSizeAndCenter(sf::CircleShape& cs, float radius);

	void setTextureRectAndCenter(sf::Sprite& s, sf::Vector2f size, sf::IntRect rect);
}