#pragma once
#include "Component.h"
#include "Game.h"

using namespace S2D;

class Middle : public Component{
private:
	Game* game;
	sf::RectangleShape image;

public:
	Middle(Game* game, sf::Vector2f position) : game(game){
		//set the size of the rectangle
		image.setSize({10, 720});
		//set the center of the rectangle as the translation point
		//SFML by default uses top right coordinates
		/*	v____
			|	 |
			|____|
		*/
		//but we want to use the center to make it easier with Box2d
		/*	 _____
			|	  |
			|  -  |
			|_____|
		*/
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