#pragma once

#include "Game.h"
#include "Snake.h"
#include "Food.h"

using namespace S2D;

void loadSnake(Game* game){
	Entity& snake = game->createEntity("snake");
	sf::Keyboard::Key controls[4] = {sf::Keyboard::I, sf::Keyboard::K, sf::Keyboard::J, sf::Keyboard::L};
	snake.addComponent<Snake>(controls);

	Entity& foodSpawner = game->createEntity("food");
	snake.addComponent<Food>();
}