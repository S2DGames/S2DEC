#pragma once

#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Box2D/Dynamics/b2Body.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "Component.h"
#include "Game.h"
#include "Util.h"
#include "AlienCoordinator.h"
#include "sf_b2.h"

using namespace S2D;

class Alien : public Component{
private:
	Game* game{nullptr};
	b2Body* body{nullptr};
	b2BodyDef bodyDef{};
	b2PolygonShape shape{};
	b2Fixture* fixture{nullptr};

	sf::RectangleShape image;

	sf::Vector2f nextPosition;
	AlienCoordinator* coordinator;
	int alienId = 0;
public:
	Alien(Game* game, AlienCoordinator* ac, int id, sf::Vector2f startingPosition);
	~Alien();

	/**
	* Called when this component is added to an Entity.
	*/
	void init() override;

	/**
	* Called once every frame.
	*/
	void update(float frameTime) override;

	/**
	* Called once every frame.
	*/
	void draw(sf::RenderTarget& target) override;

	const b2Vec2 getb2Position();
	void setNextPosition(sf::Vector2f nextPosition);
	const sf::Vector2f getsfPosition();
	const sf::Vector2f getsfSize();
};