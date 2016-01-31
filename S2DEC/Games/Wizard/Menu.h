#pragma once

#include "SFML/Graphics/RenderTarget.hpp"
#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Component.h"
#include "Game.h"
#include "Util.h"
#include "sf_b2.h"
#include "WizardUtility.h"

using namespace S2D;

class Menu : public Component {
private:
	vector<sf::Keyboard::Key> controls;
	vector<sf::CircleShape> glyphs;
	
	SpellType spellType;
	bool canFire = false;
	vector<sf::Keyboard::Key> playerKeyPresses;
	vector<sf::Keyboard::Key> start{ sf::Keyboard::Q, sf::Keyboard::W, sf::Keyboard::E, sf::Keyboard::A, sf::Keyboard::S, sf::Keyboard::D};
	vector<sf::Keyboard::Key> end{ sf::Keyboard::E, sf::Keyboard::W, sf::Keyboard::Q, sf::Keyboard::D, sf::Keyboard::S, sf::Keyboard::A };

public:
	Menu(vector<sf::Keyboard::Key> controls) : controls(controls){
		
	}

	/**
	* Called when this component is added to an Entity.
	*/
	void init() override {
		float glyphRadius = 75;
		float circleRadius = 175;

		float radians = -90.0f * DEGTORAD;
		float x = (circleRadius * cos(radians)) + 640.0f;
		float y = (circleRadius * sin(radians)) + 360.0f;
		sf::CircleShape shape1{ glyphRadius };
		shape1.setOrigin({ shape1.getRadius(), shape1.getRadius() });
		shape1.setFillColor(sf::Color::Blue);
		shape1.setPosition({ x, y });

		radians = 90.0f * DEGTORAD;
		x = (circleRadius * cos(radians)) + 640.0f;
		y = (circleRadius * sin(radians)) + 360.0f;
		sf::CircleShape shape2{ glyphRadius };
		shape2.setOrigin({ shape2.getRadius(), shape2.getRadius() });
		shape2.setFillColor(sf::Color::Blue);
		shape2.setPosition({ x, y });

		radians = -30.0f * DEGTORAD;
		x = (circleRadius * cos(radians)) + 640.0f;
		y = (circleRadius * sin(radians)) + 360.0f;
		sf::CircleShape shape3{ glyphRadius };
		shape3.setOrigin({ shape3.getRadius(), shape3.getRadius() });
		shape3.setFillColor(sf::Color::Blue);
		shape3.setPosition({ x, y });

		radians = 30.0f * DEGTORAD;
		x = (circleRadius * cos(radians)) + 640.0f;
		y = (circleRadius * sin(radians)) + 360.0f;
		sf::CircleShape shape4{ glyphRadius };
		shape4.setOrigin({ shape4.getRadius(), shape4.getRadius() });
		shape4.setFillColor(sf::Color::Blue);
		shape4.setPosition({ x, y });

		radians = 150.0f * DEGTORAD;
		x = (circleRadius * cos(radians)) + 640.0f;
		y = (circleRadius * sin(radians)) + 360.0f;
		sf::CircleShape shape5{ glyphRadius };
		shape5.setOrigin({ shape5.getRadius(), shape5.getRadius() });
		shape5.setFillColor(sf::Color::Blue);
		shape5.setPosition({ x, y });

		radians = 210.0f * DEGTORAD;
		x = (circleRadius * cos(radians)) + 640.0f;
		y = (circleRadius * sin(radians)) + 360.0f;
		sf::CircleShape shape6{ glyphRadius };
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

	/**
	* Called when the Game starts.
	*/
	void onStart() override {

	}

	/**
	* Called once every frame.
	*/
	void update(float frameTime) override {

		if (game->getMouseState(sf::Mouse::Left) == KEY_PRESSED) {
			playerKeyPresses.clear();
		}

		for (auto key : game->getKeysPressed()) {
			if (playerKeyPresses.size() < 6) {
				playerKeyPresses.emplace_back(key);
			}
		}

		if (playerKeyPresses.size() == 6) {
			if ((spellType = checkForSpellCombo(playerKeyPresses)) > SpellType::None) {
				cout << (int)spellType << endl;
				canFire = true;
			}
			playerKeyPresses.clear();
		}

		if ((game->getKeyState(sf::Keyboard::LControl) == KEY_PRESSED)) {
			playerKeyPresses.clear();
		}

		for (sf::Keyboard::Key key : game->getKeysHeld()) {
			if (key == controls[0]) {
				glyphs[0].setFillColor(sf::Color::Yellow);
				//game->addLight(lights[0]);
			}
			else if (key == controls[1]) {
				glyphs[1].setFillColor(sf::Color::Yellow);
				//game->addLight(lights[1]);
			}
			else if (key == controls[2]) {
				glyphs[2].setFillColor(sf::Color::Yellow);
				//game->addLight(lights[2]);
			}
			else if (key == controls[3]) {
				glyphs[3].setFillColor(sf::Color::Yellow);
				//game->addLight(lights[3]);
			}
			else if (key == controls[4]) {
				glyphs[4].setFillColor(sf::Color::Yellow);
				//game->addLight(lights[4]);
			}
			else if (key == controls[5]) {
				glyphs[5].setFillColor(sf::Color::Yellow);
				//game->addLight(lights[5]);
			}
		}

		for (sf::Keyboard::Key key : game->getKeysReleased()) {
			if (key == controls[0]) {
				glyphs[0].setFillColor(sf::Color::Blue);
				//game->removeLight(lights[0]);
			}
			else if (key == controls[1]) {
				glyphs[1].setFillColor(sf::Color::Blue);
				//game->removeLight(lights[1]);
			}
			else if (key == controls[2]) {
				glyphs[2].setFillColor(sf::Color::Blue);
				//game->removeLight(lights[2]);
			}
			else if (key == controls[3]) {
				glyphs[3].setFillColor(sf::Color::Blue);
				//game->removeLight(lights[3]);
			}
			else if (key == controls[4]) {
				glyphs[4].setFillColor(sf::Color::Blue);
				//game->removeLight(lights[4]);
			}
			else if (key == controls[5]) {
				glyphs[5].setFillColor(sf::Color::Blue);
				//game->removeLight(lights[5]);
			}
		}

		if (spellType == SpellType::Start) {
			game->endScene();
		}
		else if(spellType == SpellType::End) {
			game->endGame();
		}
	}

	/**
	* Called once every frame.
	*/
	void draw(sf::RenderTarget& target) override {
		for (auto glyph : glyphs) {
			target.draw(glyph);
		}
	}

	SpellType checkForSpellCombo(vector<sf::Keyboard::Key> keyPresses) {
		int matchCount = 0;
		SpellType spellType;
		//TODO make the selection of spells unique
		//TODO make this area NOT a horrific mess of code, embarassing generations of programmers
		for (int index = 0; index < 6; index++) {
			if (keyPresses[index] == start[index]) {
				matchCount++;
			}
		}
		if (matchCount == 6) {
			return SpellType::Start;
		}
		else {
			matchCount = 0;
		}
		for (int index = 0; index < 6; index++) {
			if (keyPresses[index] == end[index]) {
				matchCount++;
			}
		}
		if (matchCount == 6) {
			return SpellType::End;
		}
		return SpellType::None;
	}
};