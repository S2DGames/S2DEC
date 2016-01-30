#pragma once

#include "SFML/Graphics/RenderTarget.hpp"
#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Component.h"
#include "Game.h"
#include "Util.h"
#include "sf_b2.h"
#include "Spell.h"
#include "WizardUtility.h"
#include "Fireball.h"
#include "WaterBlast.h"
#include "LightningBolt.h"

using namespace S2D;

class Wizard : public Component {
private:
	sf::RectangleShape image;

	b2Body* body{ nullptr };
	b2BodyDef bodyDef;
	b2PolygonShape shape;
	b2Fixture* fixture{ nullptr };

	bool canFire = false;
	SpellType spellType;
	vector<sf::Keyboard::Key> playerKeyPresses;

	vector<sf::Keyboard::Key> fireBall{ sf::Keyboard::Up, sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Left, sf::Keyboard::Right };
	vector<sf::Keyboard::Key> waterBlast{ sf::Keyboard::Left, sf::Keyboard::Up, sf::Keyboard::Right, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Up, sf::Keyboard::Right, sf::Keyboard::Down };
	vector<sf::Keyboard::Key> lightningBolt{ sf::Keyboard::Up, sf::Keyboard::Up, sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Down, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right };

public:
	Wizard(sf::Vector2f position) {
		image.setSize(sf::Vector2f(20.0f, 20.0f));
		image.setPosition(position);
		image.setOrigin((image.getSize().x) / 2.0f, (image.getSize().y) / 2.0f);
		//bodyDef.position = { sfTob2(position) };
	}

	/**
	* Called when this component is added to an Entity.
	*/
	void init() override {
		//bodyDef.type = b2_dynamicBody;

		//shape.SetAsBox(sfTob2(image.getSize().x / 2.0f), sfTob2(image.getSize().y / 2.0f));
		//body = game->CreateBody(&bodyDef);
		//body->SetUserData(this);
		//body->SetFixedRotation(true);
		//fixture = body->CreateFixture(&shape, 1.0f);
		//fixture->SetFriction(0.0f);
		//fixture->SetRestitution(1.0f);
		//movesfTob2(image, body);
	}

	void onStart() override {

	}

	void update(float frameTime) override {

		for (auto key : game->getKeysPressed()) {
			if (playerKeyPresses.size() < 8) {
				playerKeyPresses.emplace_back(key);
			}
		}

		if (playerKeyPresses.size() == 8) {
			if((spellType = checkForSpellCombo(playerKeyPresses)) > SpellType::None) {
				cout << (int)spellType << endl;
				canFire = true;
			}
			playerKeyPresses.clear();
		}

		if ((game->getKeyState(sf::Keyboard::LControl) == KEY_PRESSED)) {
			playerKeyPresses.clear();
		}

		if (game->getMouseState(sf::Mouse::Left) == KEY_PRESSED && canFire) {
			Entity& spell = game->createEntity("Spell");
			if (spellType == SpellType::Fire) {
				spell.addComponent<Fireball>(sf::Vector2f{ image.getPosition().x, image.getPosition().y }, sf::Vector2f{ (float)game->getMousePos().x, (float)game->getMousePos().y });
			}
			else if (spellType == SpellType::Water) {
				spell.addComponent<WaterBlast>(sf::Vector2f{ image.getPosition().x, image.getPosition().y }, sf::Vector2f{ (float)game->getMousePos().x, (float)game->getMousePos().y });
			}
			else if (spellType == SpellType::Lightning) {
				spell.addComponent<LightningBolt>(sf::Vector2f{ image.getPosition().x, image.getPosition().y }, sf::Vector2f{ (float)game->getMousePos().x, (float)game->getMousePos().y });
			}
			canFire = false;
		}
	}

	void draw(sf::RenderTarget& target) override {
		target.draw(image);
	}

	void beginCollision(Component* collidedComponent, b2Contact* contact) override {

	}

	void endCollision(Component* collidedComponent, b2Contact* contact) override {

	}

	SpellType checkForSpellCombo(vector<sf::Keyboard::Key> keyPresses) {
		int matchCount = 0;
		SpellType spellType;
		//TODO make the selection of spells unique
		//TODO make this area NOT a horrific mess of code, embarassing generations of programmers
		for (int index = 0; index < 8; index++) {
			if (keyPresses[index] == fireBall[index]) {
				matchCount++;
			}
		}
		if (matchCount == 8) {
			return SpellType::Fire;
		}
		else {
			matchCount = 0;
		}
		for (int index = 0; index < 8; index++) {
			if (keyPresses[index] == waterBlast[index]) {
				matchCount++;
			}
		}
		if (matchCount == 8) {
			return SpellType::Water;
		}
		else {
			matchCount = 0;
		}
		for (int index = 0; index < 8; index++) {
			if (keyPresses[index] == lightningBolt[index]) {
				matchCount++;
			}
		}
		if (matchCount = 8) {
			return SpellType::Lightning;
		}
		else {
			matchCount == 0;
		}
		return SpellType::None;
	}
};