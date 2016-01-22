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
#include "sf_b2.h"

void S2D::movesfTob2(sf::Transformable& t, b2Body* b){
	if(b != nullptr){
		b2Vec2 b2Position = b->GetPosition();
		t.setPosition(b2Position.x * SCALE, b2Position.y * SCALE);
	}else{
		cerr << "null body found when moving image to body position" << endl;
	}
}

sf::Vector2f S2D::b2Tosf(b2Vec2 vec){
	return{vec.x * SCALE, vec.y * SCALE};
}

float S2D::b2Tosf(float num){
	return num * SCALE;
}

void S2D::setCenter(sf::RectangleShape& rs){
	rs.setOrigin(rs.getSize().x / 2.0f, rs.getSize().y / 2.0f);
}

void S2D::setCenter(sf::CircleShape& cs){
	cs.setOrigin(cs.getRadius(), cs.getRadius());
}

void S2D::setSizeAndCenter(sf::RectangleShape& rs, sf::Vector2f size){
	rs.setSize(size);
	setCenter(rs);
}

void S2D::setSizeAndCenter(sf::CircleShape& cs, float radius){
	cs.setRadius(radius);
	setCenter(cs);
}

void S2D::setTextureRectAndCenter(sf::Sprite& s, sf::Vector2f size, sf::IntRect rect){
	if(rect.width == rect.left && rect.height == rect.top){
		s.setTextureRect({rect.left, rect.top, (int)size.x, (int)size.y});
	}else{

	}
	//TODO scale the texture to fit within the size unless there is a texture rect
	s.setOrigin(size.x / 2.0f, size.y / 2.0f);
}