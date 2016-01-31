#pragma once

#include "Game.h"
#include "Wizard.h"
#include "EnemySpawner.h"
#include "Tower.h"
#include "UI.h"
#include "Menu.h"

using namespace S2D;

void loadMenu(Game* game, int& difficulty) {
	Entity& menu = game->createEntity("Menu");
	menu.addComponent<Menu>(vector<sf::Keyboard::Key>{sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::E, sf::Keyboard::D, sf::Keyboard::A, sf::Keyboard::Q}, difficulty);

	Entity& wizard = game->createEntity("Player");
	wizard.addComponent<Wizard>(sf::Vector2f{ game->SCREEN_SIZE.x / 2.0f, game->SCREEN_SIZE.y / 2.0f }, 4);
}

void loadLevel1(Game* game, int& difficulty) {
	Entity& wizard = game->createEntity("Player");
	wizard.addComponent<Wizard>(sf::Vector2f{ game->SCREEN_SIZE.x/2.0f, game->SCREEN_SIZE.y/2.0f }, difficulty);
	wizard.addComponent<Tower>(sf::Vector2f{ game->SCREEN_SIZE.x / 2.0f, game->SCREEN_SIZE.y / 2.0f });
	wizard.addComponent<EnemySpawner>(difficulty);
	wizard.addComponent<UI>(vector<sf::Keyboard::Key>{sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::E, sf::Keyboard::D, sf::Keyboard::A, sf::Keyboard::Q}, difficulty);
	

	wizard.setZ(10);
}

void loadLevel2(Game* game, int& difficulty) {
	
}

//change