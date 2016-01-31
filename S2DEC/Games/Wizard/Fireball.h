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
	std::shared_ptr<ltbl::LightPointEmission> light;
	//sf::Texture lightTexture;

public:
	Fireball(sf::Vector2f position, sf::Vector2f endPosition, void* ui): Spell(position, endPosition, SpellType::Fire ) {
		explosion.setFillColor(sf::Color::Red);
		this->ui = ui;

		//lightTexture.loadFromFile("resources/LTBL2/pointLightTexture.png");
		//lightTexture.setSmooth(true);
	}

	~Fireball() {
		
	}

	void init() override {
		Spell::init();
		//light = std::make_shared<ltbl::LightPointEmission>();
		//light->_emissionSprite.setTexture(lightTexture);
		//light->_emissionSprite.setColor(sf::Color::Red);
		//light->_emissionSprite.setPosition(image.getPosition().x - 30, image.getPosition().y - 30);
		//light->_localCastCenter = sf::Vector2f(0.0f, 0.0f);

		//game->addLight(light);
		sound.setBuffer(buffer);
		buffer.loadFromFile("resources\\Explosion.wav");
		light = std::make_shared<ltbl::LightPointEmission>();
		light->_emissionSprite.setTexture(lightTexture);
		light->_emissionSprite.setColor(sf::Color::White);
		//light->_emissionSprite.setPosition(shape1.getPosition().x - 30, shape1.getPosition().y - 30);
		light->_localCastCenter = sf::Vector2f(0.0f, 0.0f);
	}

	void update(float frameTime) override {
		//light->_emissionSprite.setPosition(image.getPosition().x - 30, image.getPosition().y - 30);
		Spell::update(frameTime);
		if (explosion.getRadius() >= 0) {
			explosion.setRadius(explosion.getRadius() - .1f);
			explosion.setOrigin(explosion.getRadius(), explosion.getRadius());
		}
		if(explosion.getRadius()<1 && explosion.getRadius() > 0) {
			//light->setTurnedOn(false);
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