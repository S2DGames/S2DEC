#pragma once

#include "SFML/Graphics/RenderTarget.hpp"
#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Component.h"
#include "Game.h"
#include "Util.h"
#include "sf_b2.h"
#include "LTBL2/ltbl/lighting/LightPointEmission.h"

using namespace S2D;
using std::shared_ptr;
using std::make_shared;
using namespace ltbl;

class FireElemental : public Component{
private:
	sf::Texture texture;
	sf::Sprite image;

	b2Body* body{nullptr};
	b2BodyDef bodyDef;
	b2PolygonShape shape;
	b2Fixture* fixture{nullptr};

	float acceleration = 0.05f;
	float decceleration = 0.98f;
	float speed = 2.5f;

	//lighting stuff
	shared_ptr<LightPointEmission> light;

	sf::Texture lightTexture;
	sf::Sprite lightSprite;

	b2Body* cameraBody{nullptr};
	b2BodyDef cameraBodyDef;
	b2PolygonShape cameraShape;
	b2Fixture* cameraFixture{nullptr};

public:
	FireElemental(){
		texture.loadFromFile("resources/fire\ elemental/fireelemental.png");
		lightTexture.loadFromFile("resources/fire\ elemental/pointLightTextureBIG.png");
		image.setTexture(texture);
	}

	b2Vec2 getVelocity(){
		return body->GetLinearVelocity();
	}

	float getXPosition(){
		return b2Tosf(body->GetPosition().x);
	}

	/**
	* Called when this component is added to an Entity.
	*/
	void init() override{
		bodyDef.type = b2_dynamicBody;
		b2Vec2 position = sfTob2(game->getView().getCenter());
		bodyDef.position = {position.x, position.y + sfTob2(game->getSize().y / 2.0f) - sfTob2(texture.getSize().y / 2.0f)};
		shape.SetAsBox(sfTob2(texture.getSize().x / 2.0f), sfTob2(texture.getSize().y / 2.0f));
		body = game->CreateBody(&bodyDef);
		body->SetUserData(this);
		body->SetFixedRotation(true);
		fixture = body->CreateFixture(&shape, 1.0f);
		fixture->SetFriction(0.0f);
		fixture->SetRestitution(1.0f);
		image.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
		movesfTob2(image, body);

		cameraBodyDef.type = b2_dynamicBody;
		cameraBodyDef.position = bodyDef.position;
		cameraShape.SetAsBox(sfTob2(1.0f), sfTob2(1.0f));
		cameraBody = game->CreateBody(&cameraBodyDef);
		body->SetFixedRotation(true);
		cameraFixture = body->CreateFixture(&shape, 1.0f);
		cameraFixture->SetSensor(true);
	}

	/**
	* Called when the Game starts.
	*/
	void onStart() override{
		//since game isnt started, the light system hast been created yet
		//TODO: fix that ^
		light = make_shared<LightPointEmission>();
		lightTexture.setSmooth(true);
		light->_emissionSprite.setTexture(lightTexture);
		light->_emissionSprite.setOrigin(lightTexture.getSize().x / 2.0f, lightTexture.getSize().y / 2.0f);
		light->_emissionSprite.setColor(sf::Color::Red);
		light->_emissionSprite.setPosition(image.getPosition());
		light->_localCastCenter = sf::Vector2f(0.0f, 0.0f);
		game->addLight(light);
	}

	/**
	* Called once every frame.
	*/
	void update(float frameTime) override{
		b2Vec2 vel = body->GetLinearVelocity();
		bool xKey{false};
		bool yKey{false};
		if(game->getKeyState(sf::Keyboard::Up) != NOT_PRESSED){
			//velocity.y -= 1.0f;
			//vel.y = b2Max(vel.y - acceleration, -speed);
			//yKey = true;
		}
		if(game->getKeyState(sf::Keyboard::Down) != NOT_PRESSED){
			//velocity.y += 1.0f;
			//vel.y = b2Min(vel.y + acceleration, speed);
			//yKey = true;
		}
		if(game->getKeyState(sf::Keyboard::Left) != NOT_PRESSED){
			//velocity.x -= 1.0f;
			vel.x = b2Max(vel.x - acceleration, -speed);
			xKey = true;
		}
		if(game->getKeyState(sf::Keyboard::Right) != NOT_PRESSED){
			//velocity.x += 1.0f;
			vel.x = b2Min(vel.x + acceleration, speed);
			xKey = true;
		}

		if(!xKey){
			vel.x *= decceleration;
		}
		//if(!yKey){
		//	vel.y *= decceleration;
		//}
		body->SetLinearVelocity(vel);

		movesfTob2(image, body);
		light->_emissionSprite.setPosition(image.getPosition());

		//if the player goes past some bounds, move the view
		//lets use 1/3th screen width on both sides
		//this should keep the player around the center and move
		//the camera when the player moves past 2/3rds to the right or 1/3rd to the left
		//		   1/3		 2/3
		//_______________________________
		//|         |         |         |
		//|         |         |         |
		//|         |         |         |
		//|         |         |         |
		//|         |         |         |
		//|_________|____p____|_________|

		float oneThirdScreenSize = game->getSize().x / 3;
		float leftBound = game->getView().getCenter().x - (oneThirdScreenSize / 2.0f);
		float rightBound = game->getView().getCenter().x + (oneThirdScreenSize / 2.0f);
		if(image.getPosition().x < leftBound){
			//move camera left. try to put player in the center
			
		}

		if(image.getPosition().x > rightBound){
			//move camera right
		}

		//for now just match the camera position to the player position
		cameraBody->SetLinearVelocity({vel.x, 0});

		//update the view to match the cameraBody
		sf::View view = game->getView();
		sf::Vector2f position = b2Tosf(cameraBody->GetPosition());
		view.setCenter(position.x, position.y - (game->getSize().y / 2.0f) + (texture.getSize().y / 2.0f));
		game->setView(view);

		//move the light sprite
		game->globalLightSprite.setPosition(view.getCenter());
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