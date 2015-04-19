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
	sf::IntRect textureRect = { 0, 0, 49, 65 };
	float animationFrameTimeCount = 0.0f;

public:
	EnemyImage(const string filename){
		texture.loadFromFile(filename);
		sprite.setTexture(texture);
		sprite.setTextureRect(textureRect);
		sprite.setOrigin(49 / 2.0f, 65 / 2.0f);
		sprite.setScale({ 1.25f, 1.25f });
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
			animationFrameTimeCount += frameTime.asMilliseconds();
			if (enemyPhysics->getVelocity() != 0){
				if (animationFrameTimeCount >= 16){
					textureRect = { textureRect.left + 49, textureRect.top, textureRect.width, textureRect.height };
					if (textureRect.left >= texture.getSize().x){
						textureRect.left = 0;
					}
					animationFrameTimeCount = 0.0f;
					sprite.setTextureRect(textureRect);
				}
			}
			else{
				animationFrameTimeCount = 0.0f;
				textureRect = { 0, textureRect.top, textureRect.width, textureRect.height };
				sprite.setTextureRect(textureRect);
			}

			if (enemyPhysics->getVelocity() < 0 && sprite.getScale().x < 0){
				sprite.setScale({ -sprite.getScale().x, sprite.getScale().y });
			}
			if (enemyPhysics->getVelocity() > 0 && sprite.getScale().x > 0){
				sprite.setScale({ -sprite.getScale().x, sprite.getScale().y });
			}



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