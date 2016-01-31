#pragma once

#include "Spell.h"
#include "SFML/Audio/Sound.hpp"
#include "SFML/Audio/SoundBuffer.hpp"

using namespace S2D;

class Fireball : public Spell {
private:
	sf::Sound sound;
	sf::SoundBuffer buffer;

	sf::CircleShape explosion;

public:
	Fireball(sf::Vector2f position, sf::Vector2f endPosition, void* ui): Spell(position, endPosition, SpellType::Fire ) {
		explosion.setFillColor(sf::Color::Red);
		this->ui = ui;
	}

	~Fireball() {
		
	}

	void init() override {
		Spell::init();
		sound.setBuffer(buffer);
		buffer.loadFromFile("resources\\Explosion.wav");
	}

	void update(float frameTime) override {
		Spell::update(frameTime);
		if (explosion.getRadius() >= 0) {
			explosion.setRadius(explosion.getRadius() - .1f);
			explosion.setOrigin(explosion.getRadius(), explosion.getRadius());
		}
		if(explosion.getRadius()<1) {
			this->owner->destroy();
		}

	}

	void draw(sf::RenderTarget& target) override {
		target.draw(explosion);
		Spell::draw(target);
	}

	void createExplosion() {
		sound.play();
		explosion.setRadius(50.0f);
		explosion.setPosition(Spell::image.getPosition());
		explosion.setOrigin(explosion.getRadius(), explosion.getRadius());
	}

	void beginCollision(Component* collidedComponent, b2Contact* contact) override {

	}

	void endCollision(Component* collidedComponent, b2Contact* contact) override {

	}
};