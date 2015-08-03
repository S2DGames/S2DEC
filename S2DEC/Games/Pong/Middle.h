#pragma once
#include "Component.h"
#include "Game.h"

using namespace S2D;

class Middle : public Component{
private:
	sf::RectangleShape image;

public:
	Middle(sf::Vector2f position, sf::Vector2f size){
		//set the size of the rectangle
		image.setSize(size);
		
		//To do this we use the setOrigin function and pass in half the width and half the height of the image.
		image.setOrigin({image.getSize().x / 2.0f, image.getSize().y / 2.0f});
		image.setPosition(position);
	}

	void onStart() override{
		//draw it behind everything with a z greater than -1
		owner->setZ(-1);
	}

	void draw(sf::RenderTarget& target) override{
		target.draw(image);
	}

};