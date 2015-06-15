// Copyright (C) 2015 Doug Madden (dmadden772@gmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
#include "Game.h"
using namespace S2D;

sf::Vector2u Game::SCREEN_SIZE;

Game::Game(unsigned int width, unsigned int height, const char* name) :
		sf::RenderWindow(),
		b2World(b2Vec2(0.0, 0.0)),
		Controls(this){
		//EventManager(this){
	title = name;
	SCREEN_SIZE = {width, height};
	videoMode.width = width;
	videoMode.height = height;
	b2World::SetContactListener(this);
	state = INITIALIZING;

	timeStep = 0.0f;
}

void Game::init(){
	settings.antialiasingLevel = 2;
	sf::RenderWindow::create(videoMode, title, sf::Style::None, settings);
	sf::RenderWindow::setVerticalSyncEnabled(true);
}

void Game::setSize(const sf::Vector2u size){
	SCREEN_SIZE = size;
	sf::RenderWindow::close();
	videoMode.width = size.x;
	videoMode.height = size.y;
	init();
}

int Game::play(){
	//Load all resources
	state = LOADING;
	//Create batched texture
	//ResourceManager::createBatch();

	//call onStart for each component
	EntityManager::onStart();

	state = RUNNING;
	sf::Clock clock;
	clock.restart();
	while(state == RUNNING){
		timeStep = clock.getElapsedTime().asSeconds();
		clock.restart();

		//store input
		if(Controls::updateControls() == CLOSE){
			state = CLOSED;
			return state;
		}

		//update events
		//EventManager::checkEvents();

		//update physics
		b2World::Step(timeStep, VELOCITY_ITERATIONS, POSITION_ITERATIONS);

		//update components
		EntityManager::update(timeStep);

		//reset screen
		sf::RenderWindow::clear();

		//draw objects in the scene and display
		EntityManager::draw(*this);
		sf::RenderWindow::display();		
	}

	return 0;
}

GameState Game::getState(){
	return state;
}

void Game::endScene(){
	state = CLOSING;
	sf::Clock c;
	EntityManager::destroyAll();
}

void Game::close(){
	sf::RenderWindow::close();
	EntityManager::destroyAll();
}

sf::FloatRect Game::getCameraRect(){
	sf::Vector2f cameraPosition = {getView().getCenter().x - (getSize().x / 2.0f), getView().getCenter().y - (getSize().y / 2.0f)};
	sf::FloatRect viewRect = {cameraPosition.x, cameraPosition.y, (float)getSize().x, (float)getSize().y};
	return viewRect;
}