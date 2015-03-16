#pragma once

#include "SFML/System/Vector2.hpp"

namespace S2D{

	class Size{
	private:
		sf::Vector2f size;
		const int priority;

	public:
		Size(sf::Vector2f size, int priority = 0) : size(size), priority(priority){

		}

		const sf::Vector2f& getSize(){
			return size;
		}

		const int getPriority(){
			return priority;
		}

		void setSize(sf::Vector2f& size){
			this->size = size;
		}
	};

}