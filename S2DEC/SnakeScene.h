#pragma once

#include "Game.h"
#include "Snake.h"
#include "Food.h"

using namespace S2D;

void loadSnake(Game* game){
	game->setSize({800, 500});
	Entity& snake = game->createEntity("snake");
	sf::Keyboard::Key controls[4] = {sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D};
	snake.addComponent<Snake>(game, controls);

	Entity& foodSpawner = game->createEntity("food");
	snake.addComponent<Food>(game);
}