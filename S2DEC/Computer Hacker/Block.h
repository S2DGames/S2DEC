#pragma once

#include "Component.h"
#include "Game.h"
#include "Box2D/Dynamics/b2World.h"
#include "Box2D/Collision/Shapes/b2PolygonShape.h"

using namespace S2D;

class Block : public Component{
private:
	Game* game;

	b2Body* body;
	b2BodyDef bodyDef;
	b2PolygonShape shape;
	b2Fixture* fixture;
	b2Vec2 position;
	b2Vec2 size;

	sf::RectangleShape rs;
public:
	Block(Game* game, sf::Vector2f position, sf::Vector2f size) : position({position.x / SCALE, position.y / SCALE}), size({size.x / SCALE, size.y / SCALE}){
		bodyDef.type = b2_staticBody;
		rs.setSize(size);
		rs.setOrigin(rs.getSize().x / 2.0f, rs.getSize().y / 2.0f);
		rs.setPosition(position);
		this->game = game;
	}

	~Block(){
		game->DestroyBody(body);
	}

	void init() override{
		bodyDef.position = position;
		body = game->CreateBody(&bodyDef);
		body->SetUserData(this);
		shape.SetAsBox(size.x / 2.0f, size.y / 2.0f);
		fixture = body->CreateFixture(&shape, 1.0f);
		owner->setZ(20);
	}

	void draw(sf::RenderTarget& target) override{
		target.draw(rs);
#ifdef _DEBUG
#ifndef IGNORE_DEBUG
		sf::RectangleShape outline;
		outline.setFillColor(sf::Color::Transparent);
		outline.setOutlineColor(sf::Color::Red);
		outline.setOutlineThickness(1.0f);
		outline.setSize((sf::Vector2f)rs.getSize());
		outline.setOrigin(rs.getSize().x / 2.0f, rs.getSize().y / 2.0f);
		outline.setPosition({body->GetPosition().x * SCALE, body->GetPosition().y * SCALE});
		target.draw(outline);
#endif
#endif
	}

};