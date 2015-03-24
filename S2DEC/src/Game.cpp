#include "Game.h"
#include "../TestObject.h"
using namespace S2D;

Game::Game(unsigned int width, unsigned int height, const string name) :
		sf::RenderWindow(),
		b2World(b2Vec2(0.0, 0.0)),
		Controls(this),
		EventManager(this),
		videoMode(width, height),
		title(name){

	b2World::SetContactListener(this);
	running = false;

	timeStep = 1.0f / (float)FRAMERATE;
}

void Game::setGravity(sf::Vector2f gravity){
	b2World::SetGravity(b2Vec2(gravity.x, gravity.y));
}

void Game::init(){
	sf::RenderWindow::create(videoMode, title);
	sf::RenderWindow::setFramerateLimit(FRAMERATE);
}

int Game::play(){
	//Load all resources
	//TestObject test(this);
	Entity testEntity("test");

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
			b2World::Step(timeStep, VELOCITY_ITERATIONS, POSITION_ITERATIONS);

			//update other stuff
			//TODO
			EntityManager::update(clock.getElapsedTime());

		clock.restart();

		//draw objects in the scene
			//EntityManager::draw();
			sf::RenderWindow::clear();
			
			sf::RenderWindow::display();
	}
	return 0;
}