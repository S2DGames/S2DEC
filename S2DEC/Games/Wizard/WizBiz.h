#pragma once

#include "Game.h"
#include "Wizard.h"
#include "EnemySpawner.h"
#include "Tower.h"
#include "UI.h"

using namespace S2D;

void load(Game* game) {
	Entity& wizard = game->createEntity("Player");
	wizard.addComponent<Wizard>(sf::Vector2f{ game->SCREEN_SIZE.x/2.0f, game->SCREEN_SIZE.y/2.0f });
	wizard.addComponent<Tower>(sf::Vector2f{ game->SCREEN_SIZE.x / 2.0f, game->SCREEN_SIZE.y / 2.0f });
	wizard.addComponent<EnemySpawner>();
	wizard.addComponent<UI>(vector<sf::Keyboard::Key>{sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::E, sf::Keyboard::D, sf::Keyboard::A, sf::Keyboard::Q});

	wizard.setZ(10);
}

//change