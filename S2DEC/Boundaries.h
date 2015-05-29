#pragma once

#include "Component.h"
#include "Game.h"
#include "Box2D/Dynamics/b2World.h"
#include "Box2D/Collision/Shapes/b2ChainShape.h"

using namespace S2D;

class Boundaries : public Component{
private:
	Game* game{nullptr};
	b2Body* body{nullptr};
	b2BodyDef bodyDef;
	b2FixtureDef fixtureDef;
	b2Fixture* fixture{nullptr};
	b2ChainShape chainShape;

	vector<b2Vec2> vertices;

	vector<sf::RectangleShape> rectangleShapes;

public:
	Boundaries(Game* game) : game(game){
		bodyDef.type = b2_staticBody;
	}

	~Boundaries(){
		game->DestroyBody(body);
	}

	void init() override{
		owner->setZ(10);
	}

	void onStart() override{
		chainShape.CreateChain(&vertices[0], vertices.size());
		body = game->CreateBody(&bodyDef);
		body->SetUserData(this);
		fixtureDef.shape = &chainShape;
		fixture = body->CreateFixture(&fixtureDef);
		fixture->SetFriction(0.0f);
		fixture->SetRestitution(1.0f);
	}

	void addVertex(b2Vec2 v){
		v = {v.x / SCALE, v.y / SCALE};
		if(vertices.size() > 0){
			b2Vec2 prevVertex = vertices.at(vertices.size() - 1);
			sf::Vector2f rSize{0.0f, 0.0f};
			sf::Vector2f rPosition{0.0f, 0.0f};

			if(prevVertex.x <= v.x){
				rSize.x = v.x - prevVertex.x;
				rPosition.x = prevVertex.x;
			}else{
				rSize.x = prevVertex.x - v.x;
				rPosition.x = v.x;
			}

			if(prevVertex.y <= v.y){
				rSize.y = v.y - prevVertex.y;
				rPosition.y = prevVertex.y;
			}else{
				rSize.y = prevVertex.y - v.y;
				rPosition.y = v.y;
			}

			if(rSize.x < 0){
				rSize.x *= -1.0f;
			}

			if(rSize.y < 0){
				rSize.y *= -1.0f;
			}

			if(rSize.x == 0){
				rSize.x = 1.0f / SCALE;
			}

			if(rSize.y == 0){
				rSize.y = 1.0f / SCALE;
			}

			sf::RectangleShape rs{{rSize.x * SCALE, rSize.y * SCALE}};
			rs.setPosition({rPosition.x * SCALE, rPosition.y * SCALE});
			rs.setFillColor(sf::Color::Red);
			rectangleShapes.push_back(rs);
		}
		if(game->getState() == RUNNING){
			game->DestroyBody(body);
			vertices.emplace_back(v);
			onStart();
		}else{
			vertices.emplace_back(v);
		}
	}

	void draw(sf::RenderTarget& target) override{
		for(auto rs : rectangleShapes){
			target.draw(rs);
		}
	}

};