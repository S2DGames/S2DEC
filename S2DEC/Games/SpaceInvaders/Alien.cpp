#pragma once

#include "Alien.h"

Alien::Alien(Game* game, AlienCoordinator* ac, int id, sf::Vector2f startingPosition) : game(game), coordinator(ac), alienId(id), nextPosition(startingPosition){
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = {sfTob2(startingPosition)};
	shape.SetAsBox(10.0f / SCALE, 10.0f / SCALE);
	image.setSize({20.0f, 20.0f});
	image.setOrigin(image.getSize().x / 2.0f, image.getSize().y / 2.0f);
	image.setPosition(startingPosition);
}

Alien::~Alien(){
	game->DestroyBody(body);
	coordinator->removeAlien(alienId);
}

void Alien::init(){
	body = game->CreateBody(&bodyDef);
	body->SetUserData(this);
	body->SetFixedRotation(true);
	fixture = body->CreateFixture(&shape, 1.0f);
	fixture->SetFriction(0.0f);
	fixture->SetRestitution(1.0f);
}

void Alien::update(float frameTime){
	sf::Vector2f currentPosition = b2Tosf(getb2Position());
	b2Vec2 velocity{sfTob2(sf::Vector2f{currentPosition.x - nextPosition.x, currentPosition.y - nextPosition.y})};
	body->SetLinearVelocity(velocity);
	movesfTob2(image, body);
}

void Alien::draw(sf::RenderTarget& target){
	target.draw(image);
}

const b2Vec2 Alien::getb2Position(){
	return body->GetPosition();
}

void Alien::setNextPosition(sf::Vector2f nextPosition){
	this->nextPosition = nextPosition;
}

const sf::Vector2f Alien::getsfPosition(){
	return image.getPosition();
}

const sf::Vector2f Alien::getsfSize(){
	return image.getSize();
}