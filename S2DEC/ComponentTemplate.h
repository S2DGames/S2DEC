#pragma once

#include "SFML/Graphics/RenderTarget.hpp"
#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Component.h"
#include "Game.h"
#include "Util.h"
#include "sf_b2.h"

using namespace S2D;

class ComponentTemplate : public Component{
private:
	sf::Sprite image;
	sf::Texture texture;

	b2Body* body{nullptr};
	b2BodyDef bodyDef;
	b2PolygonShape shape;
	b2Fixture* fixture{nullptr};
public:
	ComponentTemplate(string filename, b2Vec2 position){
		texture.loadFromFile(filename);
		image.setTexture(texture);
		image.setOrigin((texture.getSize().x) / 2.0f, (texture.getSize().y) / 2.0f);
		bodyDef.position = {position.x, position.y + sfTob2(game->getSize().y / 2.0f) - sfTob2(texture.getSize().y / 2.0f)};
	}

	/**
	 * Called when this component is added to an Entity.
	 */
	void init() override{
		bodyDef.type = b2_dynamicBody;
		
		shape.SetAsBox(sfTob2(texture.getSize().x / 2.0f), sfTob2(texture.getSize().y / 2.0f));
		body = game->CreateBody(&bodyDef);
		body->SetUserData(this);
		body->SetFixedRotation(true);
		fixture = body->CreateFixture(&shape, 1.0f);
		fixture->SetFriction(0.0f);
		fixture->SetRestitution(1.0f);
		movesfTob2(image, body);
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
		movesfTob2(image, body);
	}

	/**
	 * Called once every frame.
	 */
	void draw(sf::RenderTarget& target) override{
		target.draw(image);
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