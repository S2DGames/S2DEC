#pragma once

#include "Component.h"
#include "Health.h"
#include "Game.h"
#include "SFML/Graphics/RectangleShape.hpp"

using namespace S2D;

class HealthBar : public Component{
private:
	sf::RectangleShape hpBarBackground;
	sf::RectangleShape hpBar;

	Game* game;
	Health* health;
	sf::Vector2f center;
	sf::Vector2f size;

public:
	HealthBar(Game* game){
		this->game = game;
	}

	void init() override{
		health = &owner->getComponent<Health>();
		hpBarBackground.setPosition(10.0f, 10.0f);
		hpBar.setPosition(10.0f, 10.0f);

		hpBarBackground.setSize(sf::Vector2f{ 100.0f, 10 });
		hpBar.setSize(sf::Vector2f{ 100.0f, 10.0f });
		hpBarBackground.setFillColor(sf::Color::White);
		hpBar.setFillColor(sf::Color::Red);
	}

	void update(sf::Time frameTime) override {
		center = game->getView().getCenter();
		size = game->getView().getSize();

		hpBarBackground.setPosition(center.x - (size.x / 2) + 10, center.y - (size.y / 2) + 10);
		hpBar.setPosition(center.x - (size.x / 2) + 10, center.y - (size.y / 2) + 10);
		if (health >= 0)
			hpBar.setSize(sf::Vector2f{ 10.0f * health->getHealth(), 10.0f });
		else{
			owner->destroy();
			hpBar.setSize(sf::Vector2f{ 0.0f, 10.0f });
		}
	}

	void draw(sf::RenderTarget& target) override{
		target.draw(hpBarBackground);
		target.draw(hpBar);
	}
};
