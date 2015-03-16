#include "Game.h"
#include "../TestObject.h"
using namespace S2D;

Game::Game(unsigned int width, unsigned int height, string name) : 
		sf::RenderWindow(sf::VideoMode(width, height), name),
		b2World(b2Vec2(0.0, 0.0)),
		Controls(this),
		EventManager(this){

	b2World::SetContactListener(this);
	running = false;

	timeStep = 1.0f / 60.0f;
	velocityIterations = 9;
	positionIterations = 8;
}

void Game::setGravity(sf::Vector2f gravity){
	b2World::SetGravity(b2Vec2(gravity.x, gravity.y));
}

int Game::play(){
	//Load all resources
	TestObject test(this);

	//Create batched texture
	ResourceManager::createBatch();

	running = true;
	sf::Clock clock;
	clock.restart();
	while(running){
		//capture and store input
			if(Controls::updateControls() == CLOSE){
				return CLOSE;
			}

		//update events
			EventManager::checkEvents();

		//update objects in the scene
			//update physics
			b2World::Step(timeStep, velocityIterations, positionIterations);

			//update other stuff
			//TODO
			//EntityManager::update(clock.getElapsedTime());

		//draw objects in the scene
			//EntityManager::draw();
			sf::RenderWindow::clear();
			
			sf::RenderWindow::display();

		clock.restart();
	}
	return 0;
}