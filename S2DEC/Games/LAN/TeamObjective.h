#pragma once

#include "Game.h"
#include "Player.h"
#include "Level.h"
#include "Doors.h"

using namespace S2D;

void load(Game* game){
	
	Entity& player = game->createEntity("Player");
	player.setZ(1);
	player.addComponent<Player>(sf::Vector2f{30, 30},
								sf::Vector2f{10, 10},
								vector<sf::Keyboard::Key>
								{
									sf::Keyboard::W,
									sf::Keyboard::A,
									sf::Keyboard::S, 
									sf::Keyboard::D
								});
	Entity& level = game->createEntity("Level");
	level.addComponent<Doors>();
	level.addComponent<Level>("Games/LAN/facilitysketch.png");
	
	/*game->createEntity("Player2").addComponent<Player>(sf::Vector2f{100, 100},
													   sf::Vector2f{10, 10},
													   vector<sf::Keyboard::Key>
	{
		sf::Keyboard::Up,
			sf::Keyboard::Left,
			sf::Keyboard::Down,
			sf::Keyboard::Right
	}).getOwner()->setZ(1);*/
}