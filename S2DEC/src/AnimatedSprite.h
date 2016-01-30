#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

using std::string;
using std::vector;
using std::cout;
using std::endl;

namespace S2D{
	class AnimatedSprite : public sf::Sprite{
	private:
		sf::Texture texture;
		sf::IntRect frameBounds;

		vector<sf::IntRect> frames;
		float secondsPerFrame = 0.0f;

		int currentFrame = 0;
		float totalFrameTime = 0.0f;

	public:
		void load(string spriteSheet, sf::IntRect frameBounds, int xSpacing, int ySpacing, unsigned int xOffset, unsigned int yOffset, int frameCount){
			this->frameBounds = frameBounds;
			if(frameCount <= 0){
				cout << "Frame count must be greater than 0" << endl;
				return;
			}
			texture.loadFromFile(spriteSheet);
			frames.emplace_back(sf::IntRect{static_cast<int>(frameBounds.left + xOffset), static_cast<int>(frameBounds.top + yOffset), frameBounds.width, frameBounds.height});
			for(int i = 1; i < frameCount; i++){
				frames.emplace_back(sf::IntRect{static_cast<int>(((frameBounds.width + xSpacing) * i) + xOffset), static_cast<int>(frameBounds.top + yOffset), frameBounds.width, frameBounds.height});
			}

			setTexture(texture);
			setTextureRect(frames[0]);
		}

		void setAnimationSpeed(float secondsPerFrame){
			this->secondsPerFrame = secondsPerFrame;
		}

		void setOrigin(){
			sf::Sprite::setOrigin(frameBounds.width / 2.0f, frameBounds.height / 2.0f);
		}

		void update(float frameTime){
			totalFrameTime += frameTime;
			if(totalFrameTime > secondsPerFrame){
				currentFrame += (int)(totalFrameTime / secondsPerFrame);
				while(currentFrame >= frames.size()){
					currentFrame = currentFrame - frames.size();
				}
				totalFrameTime = 0.0f;
			}else if(totalFrameTime == secondsPerFrame){
				totalFrameTime = 0.0f;
				currentFrame++;
				if(currentFrame >= frames.size()){
					currentFrame = 0;
				}
			}
			setTextureRect(frames[currentFrame]);
		}

		sf::IntRect getFrameBounds(){
			return frameBounds;
		}
	};
}