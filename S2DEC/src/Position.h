#pragma once

#include "SFML/System/Vector2.hpp"

namespace S2D{

	class Position{
	private:
		sf::Vector2f position;
		const int priority;

	protected:
		void setPosition(sf::Vector2f position){
			this->position = position;
		}

	public:
		Position(sf::Vector2f position, int priority = 0) : position(position), priority(priority){

		}

		const sf::Vector2f& getPosition(){
			return position;
		}

		const int getPriority(){
			return priority;
		}

	};

}