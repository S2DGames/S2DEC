#pragma once

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "BulletPhysics.h"

using namespace S2D;

class BulletImage : public Component{
private:
	sf::Sprite sprite;
	sf::Texture texture;

	BulletPhysics* physics{nullptr};

public:
	BulletImage(const string filename){
		texture.loadFromFile(filename);
		sprite.setTexture(texture);
		sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
	}

	void init() override{
		if(owner->hasComponent<BulletPhysics>()){
			physics = &owner->getComponent<BulletPhysics>();
		}else{
			cerr << owner->getName() << ": BulletPhysics component missing" << endl;
		}
	}

	bool update(sf::Time frameTime) override{
		if(physics != nullptr){
			sprite.setPosition(physics->getPosition().x, physics->getPosition().y);
			sprite.setRotation(physics->getAngle());
		}
		return true;
	}

	void draw(sf::RenderTarget& target) override{
		target.draw(sprite);
	}
};