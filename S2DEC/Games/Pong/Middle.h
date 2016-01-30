#pragma once
#include "Component.h"
#include "sf_b2.h"

using namespace S2D;

class Middle : public Component{
private:
	sf::RectangleShape image;

public:
	Middle(sf::Vector2f position, sf::Vector2f size){
		//set the size of the rectangle
		image.setSize(size);
		
		//Set the position of the rectangle
		//SFML uses the top left as the origin point by default just so you know.
		//I like to use the center so there is a simple function in sf_b2.h to set the center of
		//many SFML drawables.
		setCenter(image);
		image.setPosition(position);
	}

	void onStart() override{
		//draw it behind everything that has a z greater than -1
		owner->setZ(-1);
	}

	void draw(sf::RenderTarget& target) override{
		target.draw(image);
	}

};