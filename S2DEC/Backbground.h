#pragma once

#include "Component.h"
#include "Game.h"

using namespace S2D;

class Background : public Component{
private:
	Game* game;
	sf::Sprite background;
	const sf::Texture &backgroundTexture;
public:
	Background(Game* game, string fileName): game(game), backgroundTexture(game->loadTexture(fileName)) {
		background.setTexture(backgroundTexture);
	}

	void draw(sf::RenderTarget &target) override{
		target.draw(background);
	}
};