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
#include "SFML/Audio/Sound.hpp"
#include "SFML/Audio/SoundBuffer.hpp"
//#include "SFML/Audio//Music.hpp"
#include "UI.h"

using namespace S2D;

class Wizard : public Component {
private:
	sf::SoundBuffer buffer;
	sf::SoundBuffer spellBuffer;
	sf::Sound sound;
	sf::Sound spellSound;
	//sf::Music music;
	vector<string> runeSounds;
	int runeIndex = 0;

	sf::RectangleShape image;

	b2Body* body{ nullptr };
	b2BodyDef bodyDef;
	b2PolygonShape shape;
	b2Fixture* fixture{ nullptr };

	bool canFire = false;
	SpellType spellType;
	vector<sf::Keyboard::Key> playerKeyPresses;

	int difficultyLength;
	vector<sf::Keyboard::Key> fireBall{ sf::Keyboard::W, sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::A, sf::Keyboard::D };
	vector<sf::Keyboard::Key> waterBlast{ sf::Keyboard::A, sf::Keyboard::Q, sf::Keyboard::E, sf::Keyboard::D, sf::Keyboard::A, sf::Keyboard::Q, sf::Keyboard::E, sf::Keyboard::D};
	vector<sf::Keyboard::Key> lightningBolt{ sf::Keyboard::Q, sf::Keyboard::E, sf::Keyboard::W, sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D};

public:
	Wizard(sf::Vector2f position, int difficulty) {
		image.setSize(sf::Vector2f(20.0f, 20.0f));
		image.setPosition(position);
		image.setOrigin((image.getSize().x) / 2.0f, (image.getSize().y) / 2.0f);
		difficultyLength = difficulty;
		//bodyDef.position = { sfTob2(position) };
	}

	/**
	* Called when this component is added to an Entity.
	*/
	void init() override {
		/*if (!music.openFromFile("resources\\GL010_A_Hero_Rises_Full.wav")) {
			cout << "Unable to load music" << endl;
		}*/
		runeSounds.emplace_back("resources\\Tone 1.wav");
		runeSounds.emplace_back("resources\\Tone 1.wav");
		runeSounds.emplace_back("resources\\Tone 2.wav");
		runeSounds.emplace_back("resources\\Tone 3.wav");
		runeSounds.emplace_back("resources\\Tone 4.wav");
		runeSounds.emplace_back("resources\\Tone 5.wav");
		runeSounds.emplace_back("resources\\Tone 5.wav");
		runeSounds.emplace_back("resources\\Tone 6.wav");
		runeSounds.emplace_back("resources\\Fireball.wav");
		runeSounds.emplace_back("resources\\Water Wave.wav");
		runeSounds.emplace_back("resources\\Lightening.wav");

		/*music.setVolume(25.0f);
		music.play();
		music.setLoop(true);*/
		sound.setBuffer(buffer);
		spellSound.setBuffer(spellBuffer);
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
		if (runeIndex > 7) {
			runeIndex = 0;
		}

		for (auto key : game->getKeysPressed()) {
			if (key != sf::Keyboard::Tab) {
				if (playerKeyPresses.size() < difficultyLength) {
					playerKeyPresses.emplace_back(key);
					buffer.loadFromFile(runeSounds[runeIndex]);
					sound.play();
					runeIndex++;
				}
			}
		}

		if (playerKeyPresses.size() == difficultyLength) {
			if((spellType = checkForSpellCombo(playerKeyPresses)) > SpellType::None) {
				cout << (int)spellType << endl;
				canFire = true;
			}
			playerKeyPresses.clear();
		}
		
		if ((game->getKeyState(sf::Keyboard::LControl) == KEY_PRESSED)) {
			playerKeyPresses.clear();
		}

		if (game->getMouseState(sf::Mouse::Left) == KEY_PRESSED) {
			if(canFire){
				Entity& spell = game->createEntity("Spell");
				if (spellType == SpellType::Fire) {
					spellBuffer.loadFromFile(runeSounds[8]);
					spellSound.setVolume(75.0f);
					spellSound.play();
					spell.addComponent<Fireball>(sf::Vector2f{ image.getPosition().x, image.getPosition().y }, sf::Vector2f{ (float)game->getMousePos().x, (float)game->getMousePos().y }, (void*)(&owner->getComponent<UI>()));
				}
				else if (spellType == SpellType::Water) {
					spellBuffer.loadFromFile(runeSounds[9]);
					spellSound.setVolume(25.0f);
					spellSound.play();
					spell.addComponent<WaterBlast>(sf::Vector2f{ image.getPosition().x, image.getPosition().y }, sf::Vector2f{ (float)game->getMousePos().x, (float)game->getMousePos().y }, (void*)(&owner->getComponent<UI>()));
				}
				else if (spellType == SpellType::Lightning) {
					spellBuffer.loadFromFile(runeSounds[10]);
					spellSound.setVolume(75.0f);
					spellSound.play();
					spell.addComponent<LightningBolt>(sf::Vector2f{ image.getPosition().x, image.getPosition().y }, sf::Vector2f{ (float)game->getMousePos().x, (float)game->getMousePos().y }, (void*)(&owner->getComponent<UI>()));
				}
				canFire = false;
			}
			playerKeyPresses.clear();
			runeIndex = 0;
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
		for (int index = 0; index < difficultyLength; index++) {
			if (keyPresses[index] == fireBall[index]) {
				matchCount++;
			}
		}
		if (matchCount == difficultyLength) {
			return SpellType::Fire;
		}
		else {
			matchCount = 0;
		}
		for (int index = 0; index < difficultyLength; index++) {
			if (keyPresses[index] == waterBlast[index]) {
				matchCount++;
			}
		}
		if (matchCount == difficultyLength) {
			return SpellType::Water;
		}
		else {
			matchCount = 0;
		}
		for (int index = 0; index < difficultyLength; index++) {
			if (keyPresses[index] == lightningBolt[index]) {
				matchCount++;
			}
		}
		if (matchCount == difficultyLength) {
			return SpellType::Lightning;
		}
		else {
			matchCount = 0;
		}
		return SpellType::None;
	}

	vector<sf::Keyboard::Key> getKeyPresses() {
		return playerKeyPresses;
	}
};