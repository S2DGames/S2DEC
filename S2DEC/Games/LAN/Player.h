#pragma once

#include <unordered_set>
#include "SFML/Graphics/RenderTarget.hpp"
#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Component.h"
#include "Game.h"
#include "Util.h"
#include "sf_b2.h"
#include "Utility.h"
#include "Doors.h"

using namespace S2D;
using std::bind;
using std::unordered_set;
using std::shared_ptr;

class Player : public Component{
private:
	sf::RectangleShape image;
	sf::View view;

	b2Body* body{nullptr};
	b2BodyDef bodyDef;
	b2PolygonShape shape;
	b2Fixture* fixture{nullptr};
	b2FixtureDef fixtureDef;

	vector<sf::Keyboard::Key> controls;

	 unordered_set<Door*> openableDoors;

	 //shared_ptr<ltbl::LightShape> lightShape;
	 shared_ptr<ltbl::LightPointEmission> light;
	 sf::Texture lightTexture;

public:
	Player(sf::Vector2f position, sf::Vector2f size, vector<sf::Keyboard::Key> controls){
		image.setSize(size);
		setCenter(image);
		image.setFillColor(sf::Color::Red);
		bodyDef.position = sfTob2(position);
		shape.SetAsBox(sfTob2(size.x / 2.0f), sfTob2(size.y / 2.0f));
		this->controls = controls;
	}

	void init() override{
		bodyDef.type = b2_dynamicBody;
		body = game->CreateBody(&bodyDef);
		body->SetUserData(this);
		fixtureDef.shape = &shape;
		fixtureDef.density = 1.0f;
		fixtureDef.filter.categoryBits = PLAYER;
		fixtureDef.filter.maskBits = PLAYER | WALL | DOOR | DOOR_AREA;
		fixture = body->CreateFixture(&fixtureDef);
		fixture->SetUserData(this);
		fixture->SetFriction(0.0f);
		fixture->SetRestitution(1.0f);
		movesfTob2(image, body);

		registerLocalEvent(Player::checkOpen, Player::open);
		registerLocalEvent(Player::checkUp, Player::up);
		registerLocalEvent(Player::checkLeft, Player::left);
		registerLocalEvent(Player::checkDown, Player::down);
		registerLocalEvent(Player::checkRight, Player::right);
		registerLocalEvent(Player::checkKey, Player::printMousePosition);

		//view = game->getView();
		//view.setSize(350, 196);

		//lightShape = std::make_shared<ltbl::LightShape>();
		//lightShape->_shape.setPointCount(image.getPointCount());
		//for(int i = 0; i < lightShape->_shape.getPointCount(); i++){
		//	lightShape->_shape.setPoint(i, image.getPoint(i));
		//}
		//lightShape->_shape.setPosition(image.getPosition());
		//lightShape->_renderLightOverShape = true;
		light = std::make_shared<ltbl::LightPointEmission>();
		light->_emissionSprite.setOrigin(image.getOrigin());
		lightTexture.loadFromFile("resources/LTBL2/pointLightTexture.png");
		lightTexture.setSmooth(true);
		light->_emissionSprite.setTexture(lightTexture);
		light->_emissionSprite.setColor(sf::Color::White);
		light->_emissionSprite.setPosition(image.getPosition());
		light->_localCastCenter = sf::Vector2f(0.0f, 0.0f);
	}

	void onStart() override{
		game->addLight(light);
	}

	bool checkOpen() {
		return game->getKeyState(sf::Keyboard::E) == KEY_PRESSED;
	}
	bool checkUp(){
		return game->getKeyState(controls[0]);
	}
	bool checkDown(){
		return game->getKeyState(controls[2]);
	}
	bool checkLeft(){
		return game->getKeyState(controls[1]);
	}
	bool checkRight(){
		return game->getKeyState(controls[3]);
	}
	bool checkKey(){
		//return checkUp() || checkDown() || checkLeft() || checkRight();
		if(game->getMouseState(sf::Mouse::Left) == KEY_PRESSED){
			return true;
		}
		return false;
	}

	b2Vec2 velocity{0.0f, 0.0f};
	float speed{2.0f};
	void open() {
		for (auto door : openableDoors) {
			if (door != nullptr) {
				door->open();
				cout << "Open" << endl;
			}
		}
	}
	void up(){
		velocity.y -= speed;
	}
	void down(){
		velocity.y += speed;
	}	
	void left(){
		velocity.x -= speed;
	}
	void right(){
		velocity.x += speed;
	}
	void printMousePosition(){
		cout << game->getMousePos().x << ":" << game->getMousePos().y << endl;
	}

	void update(float frameTime) override{
		body->SetLinearVelocity(velocity);
		movesfTob2(image, body);
		velocity = {0.0f, 0.0f};
		
		//view.setCenter(image.getPosition());
		//game->setView(view);

		//lightShape->_shape.setPosition(image.getPosition());
		light->_emissionSprite.setPosition(image.getPosition());
	}

	void draw(sf::RenderTarget& target) override{
		target.draw(image);
		#ifdef _DEBUG
		#ifndef IGNORE_DEBUG
		sf::RectangleShape outline;
		outline.setFillColor(sf::Color::Transparent);
		outline.setOutlineColor(sf::Color::Red);
		outline.setOutlineThickness(1.0f);
		outline.setSize(image.getSize());
		outline.setOrigin(outline.getSize().x / 2.0f, outline.getSize().y / 2.0f);
		outline.setPosition({body->GetPosition().x * SCALE, body->GetPosition().y * SCALE});
		target.draw(outline);
		#endif
		#endif
	}

	void beginCollision(Component* collidedComponent, b2Contact* contact) override{
		if (auto door = dynamic_cast<Door*>(collidedComponent)) {
			if(this == (Component*)contact->GetFixtureA()->GetUserData()){
				if(contact->GetFixtureB()->IsSensor()){
					if(openableDoors.count(door) <= 0){
						openableDoors.emplace(door);
					}
				}
			} else{
				if(contact->GetFixtureA()->IsSensor()){
					if(openableDoors.count(door) <= 0){
						openableDoors.emplace(door);
					}
				}
			}
		}
	}

	void endCollision(Component* collidedComponent, b2Contact* contact) override{
		if (auto door = dynamic_cast<Door*>(collidedComponent)) {
			if(this == (Component*)contact->GetFixtureA()->GetUserData()){
				if(contact->GetFixtureB()->IsSensor()){
					if(openableDoors.count(door) > 0){
						openableDoors.erase(openableDoors.find(door));
					}
				}
			} else{
				if(contact->GetFixtureA()->IsSensor()){
					if(openableDoors.count(door) > 0){
						openableDoors.erase(openableDoors.find(door));
					}
				}
			}
		}
	}
};