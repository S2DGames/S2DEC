#pragma once

#include "SFML/Graphics/RenderTarget.hpp"
#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Component.h"
#include "Game.h"
#include "Util.h"
#include "sf_b2.h"

using namespace S2D;

class Screen : public Component{
private:
	sf::Vector2i screenSize;
	
public:
	void increaseSize(int plusX, int plusY){
		game->setSize({(unsigned)(game->getSize().x + plusX), (unsigned)(game->getSize().y + plusY)});
		game->setPosition({(int)(game->getPosition().x - plusX / 2), (int)(game->getPosition().y - plusY / 2)});
	}

	void init() override{
		
	}

	void update(float frameTime) override{
		if(game->getKeyState(sf::Keyboard::Key::Equal)){
			increaseSize(16, 9);
		}
		if(game->getKeyState(sf::Keyboard::Key::Dash)){
			increaseSize(-16, -9);
		}
	}
};