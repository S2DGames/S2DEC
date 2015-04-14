#pragma once

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "ShipPhysics.h"
#include "Game.h"
#include "Util.h"

using namespace S2D;

class ShipPhysics;

class ShipImage : public Component{
private:
	ShipPhysics* shipPhysics{nullptr};
	sf::Sprite sprite;
	sf::Texture texture;
public:
	ShipImage(const string filename){
		texture.loadFromFile(filename);
		sprite.setTexture(texture);
		sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
		sprite.setPosition(Game::SCREEN_SIZE.x / 2.0f, Game::SCREEN_SIZE.y / 2.0f);
	}
		
	void init() override{
		if(owner->hasComponent<ShipPhysics>()){
			shipPhysics = &owner->getComponent<ShipPhysics>();
		}else{
			cerr << owner->getName() << ": ShipPhysics component missing" << endl;
		}
	}
		
	bool update(sf::Time frameTime) override{
		if(shipPhysics != nullptr){
			sprite.setPosition(shipPhysics->getPosition().x, shipPhysics->getPosition().y);
			sprite.setRotation(shipPhysics->getAngle());
		}	
		return false;
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