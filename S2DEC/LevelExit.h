#pragma once

#include "Component.h"
#include "Box2D/Dynamics/b2World.h"
#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Computer Hacker/HackerPhysics.h"
#include "Game.h"

using namespace S2D;

class LevelExit : public Component{
private:
	Game* game{ nullptr };

	b2Body* body;
	b2BodyDef bodyDef;
	b2FixtureDef fixtureDef;
	b2PolygonShape rectangleShape;
	sf::Sprite sprite;
	sf::Texture texture;
	bool ableToLeave{ false };

public:
	LevelExit(Game* game, sf::Vector2f position, string filename) : game(game){
		bodyDef.type = b2_staticBody;
		bodyDef.position = { position.x / SCALE, position.y / SCALE };
		rectangleShape.SetAsBox(50.0f / SCALE / 2.0f, 75.0f / SCALE / 2.0f);
		fixtureDef.shape = &rectangleShape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.0f;

		texture.loadFromFile(filename);
		sprite.setTexture(texture);
		sprite.setPosition(position);
		sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
	}

	~LevelExit(){
		game->DestroyBody(body);
	}

	void init() override{
		body = game->CreateBody(&bodyDef);
		body->SetUserData(this);
		body->SetFixedRotation(true);
		body->CreateFixture(&fixtureDef);
	}

	void onStart() override{
	}

	void update(sf::Time frameTime) override{
		if (game->getKeyState(sf::Keyboard::E) == KEY_PRESSED){
			if (ableToLeave){
				game->endScene();
			}
		}

	}

	virtual void beginCollision(Component* collidedComponent, b2Contact* contact){
		if (auto f = dynamic_cast<HackerPhysics*>(collidedComponent)){
			ableToLeave = true;
		}
	}

	virtual void endCollision(Component* collidedComponent, b2Contact* contact){
		if (auto f = dynamic_cast<HackerPhysics*>(collidedComponent)){
			ableToLeave = false;
		}
	}

	const sf::Vector2f getPosition(){
		return{ body->GetPosition().x * SCALE, body->GetPosition().y * SCALE };
	}

	void draw(sf::RenderTarget& target) override{
		target.draw(sprite);
#ifdef _DEBUG
#ifndef IGNORE_DEBUG
		sf::RectangleShape outline;
		outline.setFillColor(sf::Color::Transparent);
		outline.setOutlineColor(sf::Color::Red);
		outline.setOutlineThickness(1.0f);
		outline.setSize((sf::Vector2f)texture.getSize());
		outline.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
		outline.setPosition(sprite.getPosition());
		outline.setRotation(sprite.getRotation());
		target.draw(outline);
#endif
#endif
	}

	sf::Sprite& getSprite(){
		return sprite;
	}
};