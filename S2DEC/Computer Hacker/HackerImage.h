#pragma once

#include "Component.h"
#include "HackerPhysics.h"

using namespace S2D;

class HackerImage : public Component{
private:
	Game* game;
	sf::Sprite sprite;
	const sf::Texture& texture;

	HackerPhysics* physics{nullptr};

public:
	HackerImage(Game* game, string filename) : game(game), texture(game->loadTexture(filename)){
		sprite.setTexture(texture);
		sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
	}

	void init() override{
		if(owner->hasComponent<HackerPhysics>()){
			physics = &owner->getComponent<HackerPhysics>();
		}
	}

	void update(sf::Time frameTime) override{
		if(physics != nullptr){
			sprite.setPosition(physics->getPosition());
		}
	}

	void draw(sf::RenderTarget& target) override{
		target.draw(sprite);
#ifdef _DEBUG
#ifndef IGNORE_DEBUG
		sf::RectangleShape outline;
		outline.setFillColor(sf::Color::Transparent);
		outline.setOutlineColor(sf::Color::Red);
		outline.setOutlineThickness(1.0f);
		outline.setSize((sf::Vector2f)texture.getSize());
		outline.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
		outline.setPosition(sprite.getPosition());
		outline.setRotation(sprite.getRotation());
		target.draw(outline);
#endif
#endif
	}
};