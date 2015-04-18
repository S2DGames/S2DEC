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

	vector<sf::RectangleShape> rectangleShapes;

public:
	Floor(Game* game) : game(game){
		bodyDef.type = b2_staticBody;
	}

	~Floor(){
		game->DestroyBody(body);
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

	}

	void addVertex(b2Vec2 v){
		if(vertices.size() > 0){
			sf::RectangleShape rs;
			b2Vec2 prevVertex = vertices[vertices.size() - 1];
			sf::Vector2f rSize;
			sf::Vector2f rPosition;
			if(prevVertex.x <= v.x){
				rSize.x = v.x - prevVertex.x;
				rPosition.x = prevVertex.x;
			} else{
				rSize.x = prevVertex.x - v.x;
				rPosition.x = v.x;
			}

			if(prevVertex.y <= v.y){
				rSize.y = v.y - prevVertex.y;
				rPosition.y = prevVertex.y;
			} else{
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

			rs.setSize({rSize.x * SCALE, rSize.y * SCALE});
			rs.setPosition({rPosition.x * SCALE, rPosition.y * SCALE});
			rectangleShapes.push_back(rs);
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
		for(auto rs : rectangleShapes){
			target.draw(rs);
		}
	}

};