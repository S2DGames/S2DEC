#pragma once

#include "Component.h"
#include "HackerPhysics.h"
#include "ComputerAttack.h"

using namespace S2D;

class HackerImage : public Component{
private:
	Game* game;
	sf::Sprite sprite;
	sf::Texture* texture;

	HackerPhysics* physics{nullptr};
	ComputerAttack* computer{nullptr};

	sf::IntRect textureRect{0, 0, 0, 0};
	float animationFrameTimeCount = 0.0f;

	int direction = 1;

public:
	HackerImage(Game* game, string filename) : game(game), texture(game->loadTexture(filename, true)){
		sprite.setTexture(*texture);
		textureRect = {0, 0, 34, 56};
		sprite.setTextureRect(textureRect);
		sprite.setOrigin(textureRect.width / 2.0f, textureRect.height / 2.0f);
		sprite.setScale({3, 3});
		//34 56
	}

	void init() override{
		if(owner->hasComponent<HackerPhysics>()){
			physics = &owner->getComponent<HackerPhysics>();
		}
	}

	void onStart() override{
		if(owner->hasComponent<ComputerAttack>()){
			computer = &owner->getComponent<ComputerAttack>();
		}
	}

	void update(sf::Time frametime) override{
		if(physics != nullptr){
			sprite.setPosition(physics->getPosition());
		}

		if(physics->getXVel() != 0.0f){
			animationFrameTimeCount += frametime.asMilliseconds();
			if(animationFrameTimeCount >= 16){
				textureRect = {textureRect.left + 34, textureRect.top, textureRect.width, textureRect.height};
				if(textureRect.left >= texture->getSize().x){
					textureRect.left = 0;
				}
				animationFrameTimeCount = 0.0f;
				sprite.setTextureRect(textureRect);
			}
			direction = computer->getDirection();
		} else{
			animationFrameTimeCount = 0.0f;
			textureRect = {0, textureRect.top, textureRect.width, textureRect.height};
			sprite.setTextureRect(textureRect);
		}

		if(direction < 0 && sprite.getScale().x > 0){
			sprite.setScale({-sprite.getScale().x, sprite.getScale().y});
		}
		if(direction > 0 && sprite.getScale().x < 0){
			sprite.setScale({-sprite.getScale().x, sprite.getScale().y});
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