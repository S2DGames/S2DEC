#pragma once

#include "SFML/Graphics/RenderTarget.hpp"
#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Box2D/Dynamics/Joints/b2PrismaticJoint.h"
#include "Component.h"
#include "Game.h"
#include "Util.h"
#include "sf_b2.h"
#include "Utility.h"
#include "LTBL2/ltbl/lighting/LightShape.h"

using std::unique_ptr;
using std::move;
using std::shared_ptr;
using std::make_shared;
using namespace S2D;

enum OpenDirection{UP, DOWN, LEFT, RIGHT};

class Door : public Component{
private:
	b2Body* body;
	b2BodyDef bodyDef;
	b2PolygonShape shape;
	b2Fixture* fixture;
	b2FixtureDef fixtureDef;
	b2PrismaticJoint* joint;
	b2PrismaticJointDef prismaticJointDef;
	sf::RectangleShape image{};

	b2Body* area;
	b2BodyDef areaDef;
	b2PolygonShape areaShape;
	b2Fixture* areaFixture;
	b2FixtureDef areaFixtureDef;
	sf::RectangleShape areaImage{};

	OpenDirection direction;
	b2Vec2 closedPosition;
	b2Vec2 openPosition;
	bool opening = false;
	bool isOpen = false;
	bool closing = false;
	bool isClosed = true;

	const int cycle = 90;
	int frameCount = 90;

	shared_ptr<ltbl::LightShape> lightShape;

public:
	Door(Game* game, array<int, 4> a, OpenDirection direction){
		image.setSize({(a[2] - a[0]) == 0 ? 1.0f : a[2] - a[0], (a[3] - a[1]) == 0 ? 1.0f : a[3] - a[1]});
		image.setFillColor(sf::Color::Red);
		setCenter(image);
		image.setPosition({(a[0] + a[2]) / 2.0f, (a[1] + a[3]) / 2.0f});
		image.setOutlineThickness(2);
		bodyDef.type = b2_kinematicBody;
		bodyDef.position = sfTob2(image.getPosition());
		shape.SetAsBox(sfTob2(image.getSize().x / 2.0f), sfTob2(image.getSize().y / 2.0f));
		body = game->CreateBody(&bodyDef);
		body->SetUserData(this);
		fixtureDef.shape = &shape;
		fixtureDef.filter.categoryBits = DOOR;
		fixtureDef.filter.maskBits = PLAYER;
		fixture = body->CreateFixture(&fixtureDef);

		switch (direction) {
		case OpenDirection::UP:
			areaImage.setSize({ image.getSize().x * 10, image.getSize().y });
			break;
		case OpenDirection::DOWN:
			areaImage.setSize({ image.getSize().x * 10, image.getSize().y });
			break;
		case OpenDirection::LEFT:
			areaImage.setSize({ image.getSize().x, image.getSize().y * 10 });
			break;
		case OpenDirection::RIGHT:
			areaImage.setSize({ image.getSize().x, image.getSize().y * 10 });
			break;
		}
		areaImage.setFillColor(sf::Color(255, 0, 0, 100));
		setCenter(areaImage);
		areaImage.setPosition(image.getPosition());
		areaImage.setOutlineThickness(2);
		areaDef.type = b2_staticBody;
		areaDef.position = bodyDef.position;
		areaShape.SetAsBox(sfTob2(areaImage.getSize().x / 2.0f), sfTob2(areaImage.getSize().y / 2.0f));
		area = game->CreateBody(&areaDef);
		area->SetUserData(this);
		areaFixtureDef.density = 1.0f;
		areaFixtureDef.shape = &areaShape;
		areaFixtureDef.isSensor = true;
		areaFixtureDef.filter.categoryBits = DOOR_AREA;
		areaFixtureDef.filter.maskBits = PLAYER;
		areaFixture = area->CreateFixture(&areaFixtureDef);
		fixture->SetUserData(this);

		/*prismaticJointDef.bodyA = body;
		prismaticJointDef.bodyB = area;
		prismaticJointDef.localAnchorA.SetZero();
		prismaticJointDef.localAnchorB.SetZero();
		prismaticJointDef.collideConnected = false;
		prismaticJointDef.localAxisA.Set(0, 1);
		joint = (b2PrismaticJoint*)game->CreateJoint(&prismaticJointDef);*/

		closedPosition = bodyDef.position;
		this->direction = direction;
		switch(direction){
			case OpenDirection::UP:
				openPosition = {closedPosition.x, closedPosition.y - sfTob2(image.getSize().y)};
				break;
			case OpenDirection::DOWN:
				openPosition = {closedPosition.x, closedPosition.y + sfTob2(image.getSize().y)};
				break;
			case OpenDirection::LEFT:
				openPosition = {closedPosition.x - sfTob2(image.getSize().x), closedPosition.y};
				break;
			case OpenDirection::RIGHT:
				openPosition = {closedPosition.x + sfTob2(image.getSize().x), closedPosition.y};
				break;
		}
	}

	void init() override{
		owner->setZ(-1);
		registerLocalEvent(Door::checkKey, Door::open);

		lightShape = std::make_shared<ltbl::LightShape>();
		lightShape->_shape.setPointCount(image.getPointCount());
		for(int i = 0; i < lightShape->_shape.getPointCount(); i++){
			lightShape->_shape.setPoint(i, image.getPoint(i));
		}
		lightShape->_shape.setOrigin(image.getOrigin());
		lightShape->_shape.setPosition(image.getPosition());
		lightShape->_renderLightOverShape = true;
	}

	void onStart() override{
		game->addShape(lightShape);
	}

	bool checkKey(){
		return game->getKeyState(sf::Keyboard::Return) == KEY_PRESSED;
	}

	void open(){
		/*if(closing){
			b2Vec2 velocity{0.0f, 0.0f};
			b2Vec2 current = sfTob2(image.getPosition());
			b2Vec2 diff = current - openPosition;
			velocity.x = diff.x / 1.5f;
			velocity.y = -diff.y / 1.5f;
			body->SetLinearVelocity(velocity);
			closing = false;
			opening = true;
			isClosed = false;
		} else if(opening){
			b2Vec2 velocity{0.0f, 0.0f};
			b2Vec2 current = sfTob2(image.getPosition());
			b2Vec2 diff = current - openPosition;
			velocity.x = diff.x / 1.5f;
			velocity.y = diff.y / 1.5f;
			body->SetLinearVelocity(velocity);
			closing = true;
			opening = false;
			isOpen = false;
		}else */
		if(isClosed && !closing){
			b2Vec2 velocity{0.0f, 0.0f};
			b2Vec2 current = sfTob2(image.getPosition());
			b2Vec2 diff = current - openPosition;
			switch(direction){
				case OpenDirection::UP:
					velocity.x = 0.0f;
					velocity.y = -diff.y / 1.5f;
					break;
				case OpenDirection::DOWN:
					velocity.x = 0.0f;
					velocity.y = -diff.y / 1.5f;
					break;
				case OpenDirection::LEFT:
					velocity.x = -diff.x / 1.5f;
					velocity.y = 0.0f;
					break;
				case OpenDirection::RIGHT:
					velocity.x = -diff.x / 1.5f;
					velocity.y = 0.0f;
					break;
			}
			
			body->SetLinearVelocity(velocity);
			opening = true;
			closing = false;
			isClosed = false;
		} else if(isOpen && !opening){
			b2Vec2 velocity{0.0f, 0.0f};
			b2Vec2 current = sfTob2(image.getPosition());
			b2Vec2 diff = closedPosition - current;
			switch(direction){
				case OpenDirection::UP:
					velocity.x = 0.0f;
					velocity.y = diff.y / 1.5f;
					break;
				case OpenDirection::DOWN:
					velocity.x = 0.0f;
					velocity.y = diff.y / 1.5f;
					break;
				case OpenDirection::LEFT:
					velocity.x = diff.x / 1.5f;
					velocity.y = 0.0f;
					break;
				case OpenDirection::RIGHT:
					velocity.x = diff.x / 1.5f;
					velocity.y = 0.0f;
					break;
			}
			body->SetLinearVelocity(velocity);
			closing = true;
			opening = false;
			isOpen = false;
		}
	}
	
	void update(float frameTime) override{
		movesfTob2(image, body);
		if(opening){
			auto currentPosition = sfTob2(image.getPosition());
			switch(direction){
				case OpenDirection::UP:
					if(currentPosition.y <= openPosition.y){
						isOpen = true;
						isClosed = false;
						opening = false;
						closing = false;
						b2Vec2 velocity{0.0f, 0.0f};
						body->SetLinearVelocity(velocity);
					}
					break;
				case OpenDirection::DOWN:
					if(currentPosition.y >= openPosition.y){
						isOpen = true;
						isClosed = false;
						opening = false;
						closing = false;
						b2Vec2 velocity{0.0f, 0.0f};
						body->SetLinearVelocity(velocity);
					}
					break;
				case OpenDirection::LEFT:
					if(currentPosition.x <= openPosition.x){
						isOpen = true;
						isClosed = false;
						opening = false;
						closing = false;
						b2Vec2 velocity{0.0f, 0.0f};
						body->SetLinearVelocity(velocity);
					}
					break;
				case OpenDirection::RIGHT:
					if(currentPosition.x >= openPosition.x){
						isOpen = true;
						isClosed = false;
						opening = false;
						closing = false;
						b2Vec2 velocity{0.0f, 0.0f};
						body->SetLinearVelocity(velocity);
					}
					break;
			}
		} else if(closing){
			auto currentPosition = sfTob2(image.getPosition());
			switch(direction){
				case OpenDirection::UP:
					if(currentPosition.y >= closedPosition.y){
						isOpen = false;
						isClosed = true;
						opening = false;
						closing = false;
						b2Vec2 velocity{0.0f, 0.0f};
						body->SetLinearVelocity(velocity);
					}
					break;
				case OpenDirection::DOWN:
					if(currentPosition.y <= closedPosition.y){
						isOpen = false;
						isClosed = true;
						opening = false;
						closing = false;
						b2Vec2 velocity{0.0f, 0.0f};
						body->SetLinearVelocity(velocity);
					}
					break;
				case OpenDirection::LEFT:
					if(currentPosition.x >= closedPosition.x){
						isOpen = false;
						isClosed = true;
						opening = false;
						closing = false;
						b2Vec2 velocity{0.0f, 0.0f};
						body->SetLinearVelocity(velocity);
					}
					break;
				case OpenDirection::RIGHT:
					if(currentPosition.x <= closedPosition.x){
						isOpen = false;
						isClosed = true;
						opening = false;
						closing = false;
						b2Vec2 velocity{0.0f, 0.0f};
						body->SetLinearVelocity(velocity);
					}
					break;
			}
		}
		movesfTob2(lightShape->_shape, body);
	}

	void draw(sf::RenderTarget& target) override{
		target.draw(image);
		//target.draw(areaImage);
		//if(direction == OpenDirection::RIGHT){
			
		//}
#ifdef _DEBUG
#ifndef IGNORE_DEBUG
		
#endif
#endif
	}

	void beginCollision(Component* collidedComponent, b2Contact* contact) override{
		//cout << '.' << endl;
	}

	void endCollision(Component* collidedComponent, b2Contact* contact) override{

	}
};

class Doors : public Component{
private:
	vector<Entity*> doors;
	vector<array<int, 4>> upDoors = {
		{223, 70, 229, 110},
		{223, 250, 229, 290},
		{223, 430, 229, 470},
		{223, 610, 229, 650},
		{1280 - 229, 70, 1280 - 223, 110},
		{1280 - 229, 250, 1280 - 223, 290},
		{1280 - 229, 430, 1280 - 223, 470},
		{1280 - 229, 610, 1280 - 223, 650},
	};

	vector<array<int, 4>> leftDoors = {
		{620, 188, 640, 194},
		{620, 720 - 194, 640, 720 - 188}
	};

	vector<array<int, 4>> rightDoors = {
		{640, 188, 660, 194},
		{640, 720 - 194, 660, 720 - 188}
	};

public:
	Doors(){

	}

	void init() override{
		int i = 0;
		for(auto a : upDoors){
			Entity& doorEntity = game->createEntity("Door");
			doorEntity.addComponent<Door>(game, a, OpenDirection::UP);
			doors.emplace_back(&doorEntity);
		}
		for(auto a : leftDoors){
			Entity& doorEntity = game->createEntity("Door");
			doorEntity.addComponent<Door>(game, a, OpenDirection::LEFT);
			doors.emplace_back(&doorEntity);
		}
		for(auto a : rightDoors){
			Entity& doorEntity = game->createEntity("Door");
			doorEntity.addComponent<Door>(game, a, OpenDirection::RIGHT);
			doors.emplace_back(&doorEntity);
		}
	}

	void onStart() override{
		for(auto& d : doors){
			d->onStart();
		}
	}

	void update(float frameTime) override{
		for(auto& d : doors){
			d->update(frameTime);
		}
	}

	void draw(sf::RenderTarget& target) override{
		for(auto& d : doors){
			d->draw(target);
		}
	}
};