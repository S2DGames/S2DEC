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
	vector<sf::Keyboard::Key> LightningBolt{ sf::Keyboard::Up, sf::Keyboard::Up, sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Down, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right };

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

	//change

	/**
	* Called when the Game starts.
	*/
	void onStart() override {

	}

	/**
	* Called once every frame.
	*/
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
			spell.addComponent<Fireball>(sf::Vector2f{ image.getPosition().x, image.getPosition().y }, sf::Vector2f{ (float)game->getMousePos().x, (float)game->getMousePos().y });
			canFire = false;
		}
	}

	/**
	* Called once every frame.
	*/
	void draw(sf::RenderTarget& target) override {
		target.draw(image);
	}

	/**
	* Called if a physics body connected with this component collides with another physics body.
	* To connect a Box2d body to this component use b2Body::SetUserDate(this); inside the init or onStart function.
	* Do not delete or add physics objects in the scope of this function.
	*/
	void beginCollision(Component* collidedComponent, b2Contact* contact) override {

	}

	/**
	* Called if a physics body connected with this component collides with another physics body.
	* To connect a Box2d body to this component use b2Body::SetUserDate(this); inside the init or onStart function.
	* Do not delete or add physics objects in the scope of this function.
	*/
	void endCollision(Component* collidedComponent, b2Contact* contact) override {

	}

	SpellType checkForSpellCombo(vector<sf::Keyboard::Key> keyPresses) {
		int matchCount = 0;
		SpellType spellType;
		//TODO make the selection of spells unique
		for (int index = 0; index < 8; index++) {
			if (keyPresses[index] == fireBall[index]) {
				matchCount++;
				spellType = SpellType::Fire;
			}
			else if (keyPresses[index] == waterBlast[index]) {
				matchCount++;
				spellType = SpellType::Water;
			}
			else if (keyPresses[index] == LightningBolt[index]) {
				matchCount++;
				spellType = SpellType::Lightning;
			}

		}
		if (matchCount == 8) {
			return spellType;
		}
		else {
			spellType = SpellType::None;
			return spellType;
		}
	}

	vector<sf::Keyboard::Key> getKeyPresses() {
		return playerKeyPresses;
	}
};