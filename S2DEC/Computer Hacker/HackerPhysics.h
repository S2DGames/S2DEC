#pragma once

#include "Component.h"
#include "Box2D/Dynamics/b2World.h"
#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Floor.h"
#include "Health.h"
#include "EnemyPhysics.h"

using namespace S2D;

class HackerPhysics : public Component{
private:
	Game* game{nullptr};

	b2Body* body;
	b2BodyDef bodyDef;
	b2FixtureDef fixtureDef;
	b2PolygonShape rectangleShape;

	sf::View view;

	float maxSpeed = 5.0f;

	bool onGround{false};
	vector<sf::Vector2f> floorPoints;

public:
	HackerPhysics(Game* game, sf::Vector2f position) : game(game){
		bodyDef.type = b2_dynamicBody;
		bodyDef.position = {position.x / SCALE, position.y / SCALE};
		rectangleShape.SetAsBox(50.0f / SCALE / 2.0f, 106.0f / SCALE / 2.0f);
		fixtureDef.shape = &rectangleShape;
		fixtureDef.density = 10.0f;
		fixtureDef.friction = 0.0f;
	}

	~HackerPhysics(){
		game->DestroyBody(body);
	}

	void init() override{
		body = game->CreateBody(&bodyDef);
		body->SetUserData(this);
		body->SetFixedRotation(true);
		body->CreateFixture(&fixtureDef);
	}

	void onStart() override{
		view = game->getView();
		//view.setSize({(float)game->getSize().x + 200.0f, (float)game->getSize().y + 112.5f});
		view.setSize({1280, 720});
		view.setCenter(view.getCenter().x, view.getCenter().y + 100);
		game->setView(view);
	}

	void update(sf::Time frameTime) override{
		view.setCenter(body->GetPosition().x * SCALE, view.getCenter().y);
		//view.setCenter(body->GetPosition().x * SCALE, body->GetPosition().y * SCALE);
		game->setView(view);

		b2Vec2 speed{0, body->GetLinearVelocity().y};

		if(game->getKeyState(sf::Keyboard::Left)){
			speed.x -= maxSpeed;
		}

		if(game->getKeyState(sf::Keyboard::Right)){
			speed.x += maxSpeed;
		}

		body->SetLinearVelocity(speed);

		if(game->getKeyState(sf::Keyboard::Space) == KEY_PRESSED){
			if(onGround){
				float impulse = body->GetMass() * -13.0f;
				body->ApplyLinearImpulse({0, impulse}, body->GetWorldCenter(), true);
			}
		}

	}

	void beginCollision(Component* collidedComponent, b2Contact* contact){
		if (auto f = dynamic_cast<Floor*>(collidedComponent)){
			
			onGround = true;
		}

		if (auto f = dynamic_cast<EnemyPhysics*>(collidedComponent)){
			owner->getComponent<Health>().damage(1);
		}
	}

	void endCollision(Component* collidedComponent, b2Contact* contact){
		if(auto f = dynamic_cast<Floor*>(collidedComponent)){
			int i = 0;
			for(b2ContactEdge* ce = body->GetContactList(); ce; ce = ce->next){
				Component* currentlyCollided = (Component*)ce->other->GetUserData();
				i++;
			}

			if(i == 1){
				onGround = false;
			}
		}
	}

	const sf::Vector2f getPosition(){
		return {body->GetPosition().x * SCALE, body->GetPosition().y * SCALE};
	}

	bool getOnGround(){
		return onGround;
	}

	b2Body* getBody(){
		return body;
	}

	float getXVel(){
		return body->GetLinearVelocity().x;
	}

	void storeVertices(vector<sf::Vector2f> points){

	}
};