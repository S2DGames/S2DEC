#pragma once

#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "Component.h"
#include "Game.h"
#include "Util.h"
#include "sf_b2.h"
#include "Wizard.h"

using namespace S2D;

class UI : public Component {
private:
	vector<sf::Keyboard::Key> controls;
	vector<sf::CircleShape> glyphs;
	vector<sf::CircleShape> selectedGlyphs;

	sf::RectangleShape healthBar;
	sf::RectangleShape healthBarOutline;

	float currentDegree = 0.0f;
	int spellCount = 0;

public:
	UI(vector<sf::Keyboard::Key> controls) : controls(controls) {
		healthBar.setSize({ 200.0f, 10.0f });
		healthBar.setOrigin(healthBar.getSize().x / 2.0f, healthBar.getSize().y / 2.0f);
		healthBar.setFillColor(sf::Color::Red);
		healthBarOutline.setSize({ 204.0f, 14.0f });
		healthBarOutline.setOrigin(healthBarOutline.getSize().x / 2.0f, healthBarOutline.getSize().y / 2.0f);
		healthBarOutline.setFillColor(sf::Color::Black);
	}

	void init() override {
		healthBar.setPosition(game->getSize().x / 2.0f, 15.0f);
		healthBarOutline.setPosition(game->getSize().x / 2.0f, 15.0f);
		sf::CircleShape shape1{ 10 };
		shape1.setOrigin({ shape1.getRadius(), shape1.getRadius() });
		shape1.setFillColor(sf::Color::Blue);
		shape1.setPosition({ game->getSize().x / 2.0f, (game->getSize().y / 2.0f) - 40.0f });

		sf::CircleShape shape2{ 10 };
		shape2.setOrigin({ shape2.getRadius(), shape2.getRadius() });
		shape2.setFillColor(sf::Color::Blue);
		shape2.setPosition({ game->getSize().x / 2.0f, (game->getSize().y / 2.0f) + 40.0f });

		float radians = -30.0f * DEGTORAD;
		float x = (40.0f * cos(radians)) + 640;
		float y = (40.0f * sin(radians)) + 360;
		sf::CircleShape shape3{ 10 };
		shape3.setOrigin({ shape3.getRadius(), shape3.getRadius() });
		shape3.setFillColor(sf::Color::Blue);
		shape3.setPosition({ x, y });

		radians = 30.0f * DEGTORAD;
		x = (40.0f * cos(radians)) + 640;
		y = (40.0f * sin(radians)) + 360;
		sf::CircleShape shape4{ 10 };
		shape4.setOrigin({ shape4.getRadius(), shape4.getRadius() });
		shape4.setFillColor(sf::Color::Blue);
		shape4.setPosition({ x, y });

		radians = 150.0f * DEGTORAD;
		x = (40.0f * cos(radians)) + 640;
		y = (40.0f * sin(radians)) + 360;
		sf::CircleShape shape5{ 10 };
		shape5.setOrigin({ shape5.getRadius(), shape5.getRadius() });
		shape5.setFillColor(sf::Color::Blue);
		shape5.setPosition({ x, y });

		radians = 210.0f * DEGTORAD;
		x = (40.0f * cos(radians)) + 640;
		y = (40.0f * sin(radians)) + 360;
		sf::CircleShape shape6{ 10 };
		shape6.setOrigin({ shape6.getRadius(), shape6.getRadius() });
		shape6.setFillColor(sf::Color::Blue);
		shape6.setPosition({ x, y });

		glyphs.emplace_back(shape1);
		glyphs.emplace_back(shape2);
		glyphs.emplace_back(shape3);
		glyphs.emplace_back(shape4);
		glyphs.emplace_back(shape5);
		glyphs.emplace_back(shape6);
	}

	void onStart() override {

	}

	void update(float frameTime) override {

		healthBar.setSize({ 20.0f * owner->getComponent<Tower>().getHealth(), healthBar.getSize().y });
		healthBar.setOrigin(healthBar.getSize().x / 2.0f, healthBar.getSize().y / 2.0f);
		healthBar.setPosition(game->getSize().x / 2.0f, 15.0f);

		for (sf::Keyboard::Key key : game->getKeysHeld()) {
			if (key == controls[0]) {
				glyphs[0].setFillColor(sf::Color::Yellow);
			}else if (key == controls[1]) {
				glyphs[1].setFillColor(sf::Color::Yellow);
			}else if (key == controls[2]) {
				glyphs[2].setFillColor(sf::Color::Yellow);
			}else if (key == controls[3]) {
				glyphs[3].setFillColor(sf::Color::Yellow);
			}else if (key == controls[4]) {
				glyphs[4].setFillColor(sf::Color::Yellow);
			}else if (key == controls[5]) {
				glyphs[5].setFillColor(sf::Color::Yellow);
			}
		}

		for (sf::Keyboard::Key key : game->getKeysReleased()) {
			if (key == controls[0]) {
				glyphs[0].setFillColor(sf::Color::Blue);
			}else if (key == controls[1]) {
				glyphs[1].setFillColor(sf::Color::Blue);
			}else if (key == controls[2]) {
				glyphs[2].setFillColor(sf::Color::Blue);
			}else if (key == controls[3]) {
				glyphs[3].setFillColor(sf::Color::Blue);
			}else if (key == controls[4]) {
				glyphs[4].setFillColor(sf::Color::Blue);
			}else if (key == controls[5]) {
				glyphs[5].setFillColor(sf::Color::Blue);
			}
		}

		if (spellCount < 8) {
			for (auto key : game->getKeysPressed()) {
				for (auto control : controls) {
					if (key == control) {
						float radians = currentDegree * DEGTORAD;
						float x = (80.0f * cos(radians)) + 640;
						float y = (80.0f * sin(radians)) + 360;
						sf::CircleShape shape{ 10 };
						shape.setOrigin({ shape.getRadius(), shape.getRadius() });
						shape.setFillColor(sf::Color{ 90, 10, 125, 100 });
						shape.setPosition({ x, y });
						currentDegree += 45.0f;
						selectedGlyphs.emplace_back(shape);
						spellCount++;
						if (spellCount > 8) {
							spellCount = 0;
							selectedGlyphs.clear();
						}
					}
				}
			}
		}

		if (game->getMouseState(sf::Mouse::Left) == KEY_PRESSED) {
			spellCount = 0;
			selectedGlyphs.clear();
		}
	}

	void draw(sf::RenderTarget& target) override {
		for (auto glyph : glyphs) {
			target.draw(glyph);
		}
		for (auto glyph : selectedGlyphs) {
			target.draw(glyph);
		}

		target.draw(healthBarOutline);
		target.draw(healthBar);
	}

	void beginCollision(Component* collidedComponent, b2Contact* contact) override {

	}

	void endCollision(Component* collidedComponent, b2Contact* contact) override {

	}
};