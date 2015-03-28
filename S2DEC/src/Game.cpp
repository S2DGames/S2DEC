#include "Game.h"
using namespace S2D;

Game::Game(unsigned int width, unsigned int height, const string name) :
		sf::RenderWindow(),
		b2World(b2Vec2(0.0, 0.0)),
		Controls(this),
		EventManager(this),
		videoMode(width, height),
		title(name){
	
	b2World::SetContactListener(this);
	state = INITIALIZING;

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
	state = LOADING;
	//Create batched texture
	ResourceManager::createBatch();

	state = RUNNING;
	sf::Clock clock;
	clock.restart();
	while(state == RUNNING){
		//capture and store input
			if(Controls::updateControls() == CLOSE){
				state = CLOSING;
				break;
			}

		//update events
			EventManager::checkEvents();

		//update objects in the scene
			//update physics
			b2World::Step(timeStep, VELOCITY_ITERATIONS, POSITION_ITERATIONS);

			//update components
			EntityManager::update(clock.getElapsedTime());

		//reset clock and screen
			clock.restart();
			sf::RenderWindow::clear();

		//draw objects in the scene
			EntityManager::draw(*this);
			sf::RenderWindow::display();
	}

	sf::RenderWindow::close();
	
	return 0;
}