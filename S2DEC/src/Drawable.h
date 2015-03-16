#pragma once

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Transformable.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "Component.h"
#include "Position.h"
#include "Size.h"

namespace S2D{

	class Drawable : public Component, public Position, public Size{
	private:
		int layer;
		bool onScreen;

	protected:
		sf::Drawable& drawable;
		sf::Transformable& transformable;

	public:
		Drawable(sf::Drawable& drawable, sf::Transformable& transformable);

		const bool hasPosition();
		const bool hasSize();
		const bool hasImage();

		void draw(sf::RenderTarget& target);
		void draw(sf::RenderTarget& target, sf::RenderStates& states);
		void updateOnScreen(sf::View& currentView);
		void setPosition(sf::Vector2f position);
		void setSize(sf::Vector2f size);
		void update(sf::Drawable& image, sf::Transformable* transformable, sf::Vector2f size);
		void setDrawable(sf::Drawable& drawable);
		void setTransformable(sf::Transformable& transformable);
	};

}