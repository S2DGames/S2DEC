#pragma once

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "EnemyPhysics.h"
#include "Game.h"
#include "Util.h"

using namespace S2D;


class EnemyImage : public Component{
private:
	EnemyPhysics* enemyPhysics{ nullptr };
	sf::Sprite sprite;
	sf::Texture texture;
public:
	EnemyImage(const string filename){
		texture.loadFromFile(filename);
		sprite.setTexture(texture);
		sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
	}

	void init() override{
		if (owner->hasComponent<EnemyPhysics>()){
			enemyPhysics = &owner->getComponent<EnemyPhysics>();
		}
		else{
			cerr << owner->getName() << ": EnemyPhysics component missing" << endl;
		}
	}

	void update(sf::Time frameTime) override{
		if (enemyPhysics != nullptr){
			sprite.setPosition(enemyPhysics->getPosition().x, enemyPhysics->getPosition().y);
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

	sf::Sprite& getSprite(){
		return sprite;
	}
};