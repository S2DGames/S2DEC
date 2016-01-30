#pragma once

#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "Component.h"
#include "Game.h"
#include "Util.h"
#include "sf_b2.h"

using namespace S2D;

class UI : public Component {
private:
	vector<sf::CircleShape> glyphs;

public:
	UI() {
		sf::CircleShape shape1{ 10 };
		shape1.setOrigin({ shape1.getRadius(), shape1.getRadius() });
		shape1.setFillColor(sf::Color{ 100, 200, 40, 150 });
		shape1.setPosition({ game->getSize().x / 2.0f, game->getSize().y - 40.0f });

		sf::CircleShape shape2{ 10 };
		shape2.setOrigin({ shape1.getRadius(), shape1.getRadius() });
		shape2.setFillColor(sf::Color{ 200, 100, 40, 150 });
		shape2.setPosition({ game->getSize().x / 2.0f, game->getSize().y + 40.0f });

		glyphs.emplace_back(shape1);
	}

	void init() override {
		
	}

	void onStart() override {

	}

	void update(float frameTime) override {
		
	}

	void draw(sf::RenderTarget& target) override {
		for (auto glyph : glyphs) {
			target.draw(glyph);
		}
	}

	void beginCollision(Component* collidedComponent, b2Contact* contact) override {

	}

	void endCollision(Component* collidedComponent, b2Contact* contact) override {

	}
};