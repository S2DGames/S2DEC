#pragma once

#include <random>
#include <chrono>
#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Box2D/Dynamics/b2Body.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "Component.h"
#include "Game.h"
#include "Util.h"
#include "Snake.h"

using namespace S2D;
using std::default_random_engine;
using std::uniform_int_distribution;
using std::chrono::system_clock;

class Food : public Component{
private:
	Game* game{nullptr};
	b2Body* body{nullptr};
	b2BodyDef bodyDef{};
	b2PolygonShape shape{};
	b2Fixture* fixture{nullptr};
	sf::RectangleShape image;

	default_random_engine rng;

	bool respawn{true};

public:
	Food(Game* game) : game(game), rng(system_clock::now().time_since_epoch().count()){
		bodyDef.type = b2_staticBody;
		shape.SetAsBox(10.0f / SCALE / 2.0f, 10.0f / SCALE / 2.0f);
		image.setSize({10.0f, 10.0f});
		image.setOrigin(image.getSize().x / 2.0f, image.getSize().y / 2.0f);
	}

	void spawn(){
		uniform_int_distribution<int> xDist(1, Game::SCREEN_SIZE.x / 12);
		uniform_int_distribution<int> yDist(1, Game::SCREEN_SIZE.y / 12);
		bodyDef.position = {((float)xDist(rng) * 12) / SCALE, ((float)yDist(rng) * 12) / SCALE};
		init();
		image.setPosition(bodyDef.position.x * SCALE, bodyDef.position.y * SCALE);
	}

	/**
	* Called when this component is added to an Entity.
	*/
	void init() override{
		body = game->CreateBody(&bodyDef);
		body->SetFixedRotation(true);
		fixture = body->CreateFixture(&shape, 1.0f);
		fixture->SetSensor(true);
		body->SetUserData(this);
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
		if(respawn){
			game->DestroyBody(body);
			spawn();
			respawn = false;
		}
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
		outline.setSize({10.0f, 10.0f});
		outline.setOrigin(outline.getSize().x / 2.0f, outline.getSize().y / 2.0f);
		outline.setPosition({body->GetPosition().x * SCALE, body->GetPosition().y * SCALE});
		target.draw(outline);
#endif
#endif
	}

	/**
	* Called if a physics body connected with this component collides with another physics body.
	* To connect a Box2d body to this component use b2Body::SetUserDate(this); inside the init or onStart function.
	*/
	void beginCollision(Component* collidedComponent, b2Contact* contact) override{
		if(auto snake = dynamic_cast<Snake*>(collidedComponent)){
			respawn = true;
		}
		printf("collision\n");
	}
};