#pragma once

#include "SFML/Graphics/RenderTarget.hpp"
#include "Component.h"
#include "Game.h"
#include "Util.h"

using namespace S2D;

class ComponentTemplate : public Component{
private:
	Game* game{nullptr};
public:
	ComponentTemplate(Game* game) : game(game){

	}

	/**
	 * Called when this component is added to an Entity.
	 */
	void init() override{

	}

	/**
	 * Called when the Game starts.
	 */
	void onStart() override{

	}

	/**
	 * Called once every frame.
	 */
	void update(float frameTime) override{

	}

	/**
	 * Called once every frame.
	 */
	void draw(sf::RenderTarget& target) override{
//Uncomment this, include "SFML/Graphics/RectangleShape.hpp", and set the size of the RectangleShape
//if you want the physics body to be outlined.
/*#ifdef _DEBUG
#ifndef IGNORE_DEBUG
		sf::RectangleShape outline;
		outline.setFillColor(sf::Color::Transparent);
		outline.setOutlineColor(sf::Color::Red);
		outline.setOutlineThickness(1.0f);
		outline.setSize({10.0f, 10.0f});
		outline.setOrigin(outline.getSize().x / 2.0f, outline.getSize().y / 2.0f);
		outline.setPosition({body->GetPosition().x * SCALE, body->GetPosition().y * SCALE});
		target.draw(outline);
#endif
#endif*/
	}

	/**
	 * Called if a physics body connected with this component collides with another physics body.
	 * To connect a Box2d body to this component use b2Body::SetUserDate(this); inside the init or onStart function.
	 * Do not delete or add physics objects in the scope of this function.
	 */
	void beginCollision(Component* collidedComponent, b2Contact* contact) override{

	}

	/**
	* Called if a physics body connected with this component collides with another physics body.
	* To connect a Box2d body to this component use b2Body::SetUserDate(this); inside the init or onStart function.
	* Do not delete or add physics objects in the scope of this function.
	*/
	void endCollision(Component* collidedComponent, b2Contact* contact) override{

	}
};