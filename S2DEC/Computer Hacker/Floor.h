#pragma once

#include "Component.h"
#include "Game.h"
#include "Box2D/Dynamics/b2World.h"
#include "Box2D/Collision/Shapes/b2ChainShape.h"

using namespace S2D;

class Floor : public Component{
private:
	Game* game{nullptr};
	b2Body* body;
	b2BodyDef bodyDef;
	b2Fixture* fixture;
	b2ChainShape chainShape;

	vector<b2Vec2> vertices;

	sf::RectangleShape rs;


	//b2Body* testBody;
	//b2BodyDef testBodyDef;
	//b2Fixture* testFixture;
	//b2PolygonShape testShape;

public:
	Floor(Game* game) : game(game){
		bodyDef.type = b2_staticBody;
		//testBodyDef.type = b2_staticBody;
	}

	void init() override{
		owner->setZ(10);
	}

	void onStart() override{
		chainShape.CreateChain(&vertices[0], vertices.size());
		body = game->CreateBody(&bodyDef);
		body->SetUserData(this);
		fixture = body->CreateFixture(&chainShape, 1.0f);
		fixture->SetFriction(0.0f);
		//rs.setPosition({body->GetPosition().x * SCALE, body->GetPosition().y * SCALE});

		//testShape.SetAsBox(10.0f / SCALE, 100.0f / SCALE);
		//testBody = game->CreateBody(&testBodyDef);
		//testBody->SetUserData(this);

		rs.setSize({1280, 1});
		//rs.setOrigin({rs.getSize().x / 2, rs.getSize().y / 2});
		rs.setPosition({0.0f, 720.0f});
	}

	void addVertex(b2Vec2 v){
		if(vertices.size() == 0){
			//bodyDef.position = v;
		}
		if(game->getState() == RUNNING){
			game->DestroyBody(body);
			body->DestroyFixture(fixture);
			vertices.push_back(v);
			onStart();
		}else{
			vertices.push_back(v);
		}
	}

	void draw(sf::RenderTarget& target) override{
		target.draw(rs);
	}

};