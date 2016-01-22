#pragma once

#include "SFML/Graphics/RenderTarget.hpp"
#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Component.h"
#include "Game.h"
#include "Util.h"
#include "sf_b2.h"
#include "FireElemental.h"

using namespace S2D;

class Tree : public Component{
private:
	sf::Texture texture;
	sf::Sprite image;

	b2Body* body{nullptr};
	b2BodyDef bodyDef;
	b2PolygonShape shape;
	b2Fixture* fixture{nullptr};

	FireElemental& player;

public:
	Tree(sf::Vector2f position, FireElemental& player) : player(player){
		texture.loadFromFile("resources/fire\ elemental/tree.png");
		image.setTexture(texture);
		bodyDef.position = sfTob2(position);
	}

	float getXPosition(){
		return b2Tosf(body->GetPosition().x);
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
		fixture->SetSensor(true);
		//144 pixels between origin and bottom of tree
		image.setOrigin(texture.getSize().x / 2.0f,(texture.getSize().y / 2.0f) + 60);
		movesfTob2(image, body);

		getOwner()->setZ(-1);
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
		//move tree with some velocity (half as fast?) related to players velocity
		body->SetLinearVelocity({-player.getVelocity().x / 2.0f, 0});
		movesfTob2(image, body);
	}

	/**
	* Called once every frame.
	*/
	void draw(sf::RenderTarget& target) override{
		target.draw(image);
		#ifdef _DEBUG
		#ifndef IGNORE_DEBUG
		sf::RectangleShape outline;
		outline.setFillColor(sf::Color::Transparent);
		outline.setOutlineColor(sf::Color::Red);
		outline.setOutlineThickness(1.0f);
		b2AABB aabb;
		aabb.lowerBound = b2Vec2(FLT_MAX, FLT_MAX);
		aabb.upperBound = b2Vec2(-FLT_MAX, -FLT_MAX);
		b2Fixture* fixture = body->GetFixtureList();
		for(b2Fixture* fixture = body->GetFixtureList(); fixture; fixture = fixture->GetNext())
		{
			aabb.Combine(aabb, fixture->GetAABB(0));
		}
		outline.setSize(b2Tosf({aabb.upperBound.x - aabb.lowerBound.x, aabb.upperBound.y - aabb.lowerBound.y}));
		outline.setOrigin(outline.getSize().x / 2.0f, outline.getSize().y / 2.0f);
		outline.setPosition({body->GetPosition().x * SCALE, body->GetPosition().y * SCALE});
		target.draw(outline);
		#endif
		#endif
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