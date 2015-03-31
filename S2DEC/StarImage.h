#pragma once

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "Component.h"

using namespace S2D;

class StarImage : public Component{
private:
	sf::Sprite sprite;
	sf::Texture texture;

	sf::Time animationTime;

	unsigned int frame = 0;

	unsigned int absoluteFrame = 0;

	void setAnimationFrame(sf::IntRect frame){
		sprite.setTextureRect(frame);
	}

public:
	StarImage(string filename, sf::Vector2f position, float offset){
		texture.loadFromFile(filename);
		sprite.setTexture(texture);
		sprite.setPosition(position);
		animationTime += sf::seconds(offset);
	}

	bool update(sf::Time frameTime) override{
		animationTime += frameTime;

		if(animationTime.asSeconds() >= 30.0f && absoluteFrame < 1){
			frame = 1;
			sprite.move({-.5f, -.5f});
			absoluteFrame++;
		}
		
		if(animationTime.asSeconds() >= 30.25f && absoluteFrame < 2){
			frame = 2;
			absoluteFrame++;
		}

		if(animationTime.asSeconds() >= 30.35f && absoluteFrame < 3){
			frame = 3;
			sprite.move({-.5f, -.5f});
			absoluteFrame++;
		}

		if(animationTime.asSeconds() >= 30.45f && absoluteFrame < 4){
			frame = 2;
			sprite.move({.5f, .5f});
			absoluteFrame++;
		}

		if(animationTime.asSeconds() >= 30.55f && absoluteFrame < 5){
			frame = 1;
			absoluteFrame++;
		}

		if(animationTime.asSeconds() >= 30.65f){
			frame = 0;
			animationTime = sf::Time::Zero;
			sprite.move({.5f, .5f});
			absoluteFrame++;
		}

		switch(frame){
		case 0:
			setAnimationFrame({0, 0, 2, 2});
			break;
		case 1:
			setAnimationFrame({2, 0, 3, 3});
			break;
		case 2:
			setAnimationFrame({5, 0, 3, 3});
			break;
		case 3:
			setAnimationFrame({8, 0, 4, 4});
			break;
		}

		if(absoluteFrame >= 6){
			absoluteFrame = 0;
		}

		return true;
	}

	void draw(sf::RenderTarget& target) override{
		target.draw(sprite);
	}
};