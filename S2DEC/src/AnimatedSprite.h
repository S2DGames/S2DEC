#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

using std::string;
using std::vector;

namespace S2D{
	class AnimatedSprite : public sf::Sprite{
	private:
		sf::Texture* texture;
		sf::IntRect frameBounds;
		int xSpacing;
		int ySpacing;

		vector<sf::IntRect> frames;
	public:
		void load(string spriteSheet, sf::IntRect frameBounds, int xSpacing, int ySpacing, int frameCount){
			texture->loadFromFile(spriteSheet);
			texture->getSize();
		}

		void load(string spriteSheet, sf::IntRect frameBounds, int xSpacing, int ySpacing, int frameCount, sf::IntRect spriteSheetBounds){
			texture->loadFromFile(spriteSheet);
		}

		void update(float frameTime){

		}
	};
}