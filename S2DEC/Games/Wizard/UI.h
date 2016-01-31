#pragma once

#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Font.hpp"
#include "Component.h"
#include "Game.h"
#include "Util.h"
#include "sf_b2.h"
#include "Tower.h"

using namespace S2D;

class UI : public Component {
private:
	vector<sf::Keyboard::Key> controls;
	vector<sf::CircleShape> glyphs;
	vector<sf::CircleShape> selectedGlyphs;
	vector<std::shared_ptr<ltbl::LightPointEmission>> lights;

	sf::Texture lightTexture;

	sf::RectangleShape healthBar;
	sf::RectangleShape healthBarOutline;

	float currentDegree = 0.0f;
	int spellCount = 0;

	int score = 0;
	sf::Font font;
	sf::Text text;

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
		lightTexture.loadFromFile("resources/LTBL2/pointLightTexture.png");
		lightTexture.setSmooth(true);

		font.loadFromFile("resources/Font.ttf");
		text.setFont(font);
		text.setPosition(10.0f, 20.0f);

		healthBar.setPosition(game->getSize().x / 2.0f, 15.0f);
		healthBarOutline.setPosition(game->getSize().x / 2.0f, 15.0f);
		sf::CircleShape shape1{ 10 };
		shape1.setOrigin({ shape1.getRadius(), shape1.getRadius() });
		shape1.setFillColor(sf::Color::Blue);
		shape1.setPosition({ game->getSize().x / 2.0f, (game->getSize().y / 2.0f) - 40.0f });
		/*std::shared_ptr<ltbl::LightPointEmission> light1 = std::make_shared<ltbl::LightPointEmission>();
		light1->_emissionSprite.setTexture(lightTexture);
		light1->_emissionSprite.setColor(sf::Color::White);
		light1->_emissionSprite.setPosition(shape1.getPosition().x - 30, shape1.getPosition().y - 30);
		light1->_localCastCenter = sf::Vector2f(0.0f, 0.0f);*/

		sf::CircleShape shape2{ 10 };
		shape2.setOrigin({ shape2.getRadius(), shape2.getRadius() });
		shape2.setFillColor(sf::Color::Blue);
		shape2.setPosition({ game->getSize().x / 2.0f, (game->getSize().y / 2.0f) + 40.0f });
		/*std::shared_ptr<ltbl::LightPointEmission> light2 = std::make_shared<ltbl::LightPointEmission>();
		light2->_emissionSprite.setTexture(lightTexture);
		light2->_emissionSprite.setColor(sf::Color::White);
		light2->_emissionSprite.setPosition(shape2.getPosition().x - 30, shape2.getPosition().y - 30);
		light2->_localCastCenter = sf::Vector2f(0.0f, 0.0f);*/

		float radians = -30.0f * DEGTORAD;
		float x = (40.0f * cos(radians)) + 640;
		float y = (40.0f * sin(radians)) + 360;
		sf::CircleShape shape3{ 10 };
		shape3.setOrigin({ shape3.getRadius(), shape3.getRadius() });
		shape3.setFillColor(sf::Color::Blue);
		shape3.setPosition({ x, y });
		/*std::shared_ptr<ltbl::LightPointEmission> light3 = std::make_shared<ltbl::LightPointEmission>();
		light3->_emissionSprite.setTexture(lightTexture);
		light3->_emissionSprite.setColor(sf::Color::White);
		light3->_emissionSprite.setPosition(shape3.getPosition().x - 30, shape3.getPosition().y - 30);
		light3->_localCastCenter = sf::Vector2f(0.0f, 0.0f);*/

		radians = 30.0f * DEGTORAD;
		x = (40.0f * cos(radians)) + 640;
		y = (40.0f * sin(radians)) + 360;
		sf::CircleShape shape4{ 10 };
		shape4.setOrigin({ shape4.getRadius(), shape4.getRadius() });
		shape4.setFillColor(sf::Color::Blue);
		shape4.setPosition({ x, y });
		/*std::shared_ptr<ltbl::LightPointEmission> light4 = std::make_shared<ltbl::LightPointEmission>();
		light4->_emissionSprite.setTexture(lightTexture);
		light4->_emissionSprite.setColor(sf::Color::White);
		light4->_emissionSprite.setPosition(shape4.getPosition().x - 30, shape4.getPosition().y - 30);
		light4->_localCastCenter = sf::Vector2f(0.0f, 0.0f);*/

		radians = 150.0f * DEGTORAD;
		x = (40.0f * cos(radians)) + 640;
		y = (40.0f * sin(radians)) + 360;
		sf::CircleShape shape5{ 10 };
		shape5.setOrigin({ shape5.getRadius(), shape5.getRadius() });
		shape5.setFillColor(sf::Color::Blue);
		shape5.setPosition({ x, y });
		/*std::shared_ptr<ltbl::LightPointEmission> light5 = std::make_shared<ltbl::LightPointEmission>();
		light5->_emissionSprite.setTexture(lightTexture);
		light5->_emissionSprite.setColor(sf::Color::White);
		light5->_emissionSprite.setPosition(shape5.getPosition().x - 30, shape5.getPosition().y - 30);
		light5->_localCastCenter = sf::Vector2f(0.0f, 0.0f);*/

		radians = 210.0f * DEGTORAD;
		x = (40.0f * cos(radians)) + 640;
		y = (40.0f * sin(radians)) + 360;
		sf::CircleShape shape6{ 10 };
		shape6.setOrigin({ shape6.getRadius(), shape6.getRadius() });
		shape6.setFillColor(sf::Color::Blue);
		shape6.setPosition({ x, y });
		/*std::shared_ptr<ltbl::LightPointEmission> light6 = std::make_shared<ltbl::LightPointEmission>();
		light6->_emissionSprite.setTexture(lightTexture);
		light6->_emissionSprite.setColor(sf::Color::White);
		light6->_emissionSprite.setPosition(shape6.getPosition().x - 30, shape6.getPosition().y - 30);
		light6->_localCastCenter = sf::Vector2f(0.0f, 0.0f);*/

		glyphs.emplace_back(shape1);
		glyphs.emplace_back(shape2);
		glyphs.emplace_back(shape3);
		glyphs.emplace_back(shape4);
		glyphs.emplace_back(shape5);
		glyphs.emplace_back(shape6);

		/*lights.emplace_back(light1);
		lights.emplace_back(light2);
		lights.emplace_back(light3);
		lights.emplace_back(light4);
		lights.emplace_back(light5);
		lights.emplace_back(light6);*/
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
				//game->addLight(lights[0]);
			}else if (key == controls[1]) {
				glyphs[1].setFillColor(sf::Color::Yellow);
				//game->addLight(lights[1]);
			}else if (key == controls[2]) {
				glyphs[2].setFillColor(sf::Color::Yellow);
				//game->addLight(lights[2]);
			}else if (key == controls[3]) {
				glyphs[3].setFillColor(sf::Color::Yellow);
				//game->addLight(lights[3]);
			}else if (key == controls[4]) {
				glyphs[4].setFillColor(sf::Color::Yellow);
				//game->addLight(lights[4]);
			}else if (key == controls[5]) {
				glyphs[5].setFillColor(sf::Color::Yellow);
				//game->addLight(lights[5]);
			}
		}

		for (sf::Keyboard::Key key : game->getKeysReleased()) {
			if (key == controls[0]) {
				glyphs[0].setFillColor(sf::Color::Blue);
				//game->removeLight(lights[0]);
			}else if (key == controls[1]) {
				glyphs[1].setFillColor(sf::Color::Blue);
				//game->removeLight(lights[1]);
			}else if (key == controls[2]) {
				glyphs[2].setFillColor(sf::Color::Blue);
				//game->removeLight(lights[2]);
			}else if (key == controls[3]) {
				glyphs[3].setFillColor(sf::Color::Blue);
				//game->removeLight(lights[3]);
			}else if (key == controls[4]) {
				glyphs[4].setFillColor(sf::Color::Blue);
				//game->removeLight(lights[4]);
			}else if (key == controls[5]) {
				glyphs[5].setFillColor(sf::Color::Blue);
				//game->removeLight(lights[5]);
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

		text.setString(std::to_string(score));
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
		target.draw(text);
	}

	void beginCollision(Component* collidedComponent, b2Contact* contact) override {

	}

	void endCollision(Component* collidedComponent, b2Contact* contact) override {

	}

	void addPoints(int points) {
		score += points;
	}
};