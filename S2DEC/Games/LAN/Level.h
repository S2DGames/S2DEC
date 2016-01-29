#pragma once

#include "SFML/Graphics/RenderTarget.hpp"
#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Component.h"
#include "Game.h"
#include "Util.h"
#include "sf_b2.h"
#include "Utility.h"

using std::unique_ptr;
using std::move;
using namespace S2D;

struct wall{
	b2Body* body;
	b2BodyDef bodyDef;
	b2PolygonShape shape;
	b2Fixture* fixture;
	b2FixtureDef fixtureDef;
	sf::RectangleShape image{};
};

class Level : public Component{
private:
	sf::Sprite image;
	sf::Texture texture;

	vector<shared_ptr<ltbl::LightShape>> lightShapes;
	vector<unique_ptr<wall>> walls;
	vector<array<int, 4>> map = {
		{0, 0, 1280, 6},
		{0, 0, 6, 1280},
		{1274, 0, 1280, 720},
		{0, 714, 1280, 720},
		{223, 0, 229, 70},
		{223, 110, 229, 250},
		{223, 290, 229, 430},
		{223, 470, 229, 610},
		{223, 650, 229, 760},
		{0, 180, 223, 188},
		{0, 360, 223, 368},
		{0, 540, 223, 548},
		{0, 720, 223, 728},
		{1280 - 229, 0, 1280 - 223, 70},
		{1280 - 229, 110, 1280 - 223, 250},
		{1280 - 229, 290, 1280 - 223, 430},
		{1280 - 229, 470, 1280 - 223, 610},
		{1280 - 229, 650, 1280 - 223, 760},
		{1280 - 223, 180, 1280 - 0, 188},
		{1280 - 223, 360, 1280 - 0, 368},
		{1280 - 223, 540, 1280 - 0, 548},
		{1280 - 223, 720, 1280 - 0, 728},
		{346, 0, 352, 188},
		{346, 188, 620, 194},
		{660, 188, 934, 194},
		{928, 0, 934, 188},
		{346, 720 - 188, 352, 720},
		{346, 720 - 194, 620, 720 - 188},
		{660, 720 - 194, 934, 720 - 188},
		{928, 720 - 188, 934, 720},
		{346, 300, 352, 420},
		{1280 - 352, 300, 1280 - 346, 420},
		{346 + 145, 300, 352 + 145, 420},
		{346 + 145 + 145, 300, 352 + 145 + 145, 420},
		{346 + 145 + 145 + 145, 300, 352 + 145 + 145 + 145, 420},
		{346, 300, 346 + 145/2 - 20, 306},
		{346 + 145 / 2 + 20, 300, 346 + 145 + 145/2 - 20, 306},
		{346 + 145 + 145 / 2 + 20, 300, 346 + 145 + 145 + 145 / 2 - 20, 306},
		{346 + 145 + 145 + 145 / 2 + 20, 300, 346 + 145 + 145 + 145 + 145 / 2 - 20, 306},
		{346 + 145 + 145 + 145 + 145 / 2 + 20, 300, 346 + 145 + 145 + 145 + 145 + 3, 306},
		{346, 414, 1280 - 346, 420},

	};

public:
	Level(string filename){
		texture.loadFromFile(filename);
		image.setTexture(texture);
		setTextureRectAndCenter(image, {(float)texture.getSize().x, (float)texture.getSize().y});
	}

	void init() override{
		for(auto a : map){
			unique_ptr<wall> w(new wall);
			w->image.setSize({(a[2] - a[0]) == 0 ? 1.0f : a[2] - a[0], (a[3] - a[1]) == 0 ? 1.0f : a[3] - a[1]});
			w->image.setFillColor(sf::Color::Green);
			setCenter(w->image);
			w->image.setPosition({(a[0] + a[2]) / 2.0f, (a[1] + a[3]) / 2.0f});
			w->image.setOutlineThickness(2);
			w->image.setOutlineColor(sf::Color::Yellow);
			w->bodyDef.type = b2_staticBody;
			w->bodyDef.position = sfTob2(w->image.getPosition());
			w->shape.SetAsBox(sfTob2(w->image.getSize().x / 2.0f), sfTob2(w->image.getSize().y / 2.0f));
			w->body = game->CreateBody(&w->bodyDef);
			w->body->SetUserData(this);
			w->fixtureDef.shape = &w->shape;
			w->fixtureDef.density = 1.0f;
			w->fixtureDef.filter.categoryBits = WALL;
			w->fixtureDef.filter.maskBits = PLAYER;
			w->fixture = w->body->CreateFixture(&w->fixtureDef);
			movesfTob2(w->image, w->body);

			shared_ptr<ltbl::LightShape> lightShape = std::make_shared<ltbl::LightShape>();
			lightShape->_shape.setPointCount(w->image.getPointCount());
			for(int i = 0; i < lightShape->_shape.getPointCount(); i++){
				lightShape->_shape.setPoint(i, w->image.getPoint(i));
			}
			lightShape->_shape.setOrigin(w->image.getOrigin());
			lightShape->_shape.setPosition(w->image.getPosition());
			lightShape->_renderLightOverShape = false;

			lightShapes.emplace_back(lightShape);
			walls.emplace_back(move(w));
		}
	}

	void onStart() override{
		image.setPosition(game->getView().getCenter());
		for(auto& lightShape : lightShapes){
			game->addShape(lightShape);
		}
	}

	void draw(sf::RenderTarget& target) override{
		
		//target.draw(image);
		for(auto& w : walls){
			target.draw(w->image);
		}
	}
};