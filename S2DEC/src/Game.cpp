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

Game::Game(unsigned int width, unsigned int height, const char* name, bool lighting) :
		sf::RenderWindow(),
		b2World(b2Vec2(0.0, 0.0)),
		Controls(this),
		EntityManager(this),
		lightSystemEnabled(lighting){
	state = INITIALIZING;
	style = sf::Style::None;
	title = name;
	SCREEN_SIZE = {width, height};
	videoMode.width = width;
	videoMode.height = height;
	videoMode.bitsPerPixel = 32;
	b2World::SetContactListener(this);

	timeStep = 0.0f;
}

void Game::init(){
	sf::RenderWindow::create(videoMode, title, style, settings);
	if(lightSystemEnabled){
		unshadowShader.loadFromFile("resources/LTBL2/unshadowShader.vert", "resources/LTBL2/unshadowShader.frag");
		lightOverShapeShader.loadFromFile("resources/LTBL2/lightOverShapeShader.vert", "resources/LTBL2/lightOverShapeShader.frag");
		penumbraTexture.loadFromFile("resources/LTBL2/penumbraTexture.png");
		penumbraTexture.setSmooth(true);
		ltbl::LightSystem::create(sf::FloatRect(-1000.0f, -1000.0f, 1000.0f, 1000.0f), sf::RenderWindow::getSize(), penumbraTexture, unshadowShader, lightOverShapeShader);
		pointLightTexture.loadFromFile("resources/LTBL2/pointLightTexture.png");
		pointLightTexture.setSmooth(true);
		directionLightTexture.loadFromFile("resources/LTBL2/directionLightTexture.png");
		directionLightTexture.setSmooth(true);
		/*light->_emissionSprite.setTexture(pointLightTexture);
		light->_emissionSprite.setOrigin(pointLightTexture.getSize().x / 2.0f, pointLightTexture.getSize().y / 2.0f);
		light->_emissionSprite.setColor(sf::Color::White);
		light->_emissionSprite.setPosition(100, 100);
		light->_emissionSprite.scale(5, 5);
		light->_localCastCenter = sf::Vector2f(0.0f, 0.0f); // This is where the shadows emanate from relative to the sprite

		ls.addLight(light);

		lightShape = std::make_shared<ltbl::LightShape>();
		sf::RectangleShape shape({10, 10});
		lightShape->_shape.setPointCount(4);
		for(int i = 0; i < 4; i++){
			lightShape->_shape.setPoint(i, shape.getPoint(i));
		}
		lightShape->_shape.setPosition(200, 200);
		ls.addShape(lightShape);

		std::shared_ptr<ltbl::LightDirectionEmission> light2 = std::make_shared<ltbl::LightDirectionEmission>();

		directionLightTexture.loadFromFile("resources/LTBL2/directionLightTexture.png");
		directionLightTexture.setSmooth(true);
		light2->_emissionSprite.setTexture(directionLightTexture);
		light2->_castDirection = sf::Vector2f(1.0f, 10.0f);
		*/
		//ls.addLight(light2);

		background.loadFromFile("resources/background.png");
		backgroundSprite.setTexture(background);
	}
}

void Game::setSize(const sf::Vector2u size){
	SCREEN_SIZE = size;
	sf::RenderWindow::close();
	videoMode.width = size.x;
	videoMode.height = size.y;
	init();
}

sf::Vector2u Game::getSize(){
	return{videoMode.width, videoMode.height};
}

void Game::setFullScreen(){
	if(sf::RenderWindow::isOpen()){
		sf::RenderWindow::close();
		style = sf::Style::Fullscreen;
		init();
	}else{
		style = sf::Style::Fullscreen;
	}
}

GameState Game::play(){
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
		//TODO: check for a pause signal
		timeStep = clock.getElapsedTime().asSeconds();
		clock.restart();

		//store input
		if(Controls::updateControls() == CLOSE){
			state = CLOSING;
			return state;
		}

		//update events
		EventManager::checkEvents();

		//update physics
		b2World::Step(timeStep, VELOCITY_ITERATIONS, POSITION_ITERATIONS);

		//update entities/components
		EntityManager::update(timeStep);

		//reset screen
		sf::RenderWindow::clear();

		//draw background
		sf::RenderWindow::draw(backgroundSprite);

		//draw objects in the scene and display
		EntityManager::draw(*this);
		//light->_emissionSprite.setPosition(Controls::getMousePos().x, Controls::getMousePos().y);
		ltbl::LightSystem::render(sf::RenderWindow::getView(), unshadowShader, lightOverShapeShader);
		lightSprite.setTexture(ltbl::LightSystem::getLightingTexture());
		sf::RenderWindow::draw(lightSprite, sf::BlendAdd);
		sf::RenderWindow::display();
	}

	if(state == CLOSING){
		return state;
	}
	return IDLE;
}

GameState Game::getState(){
	return state;
}

void Game::endScene(){
	state = CLOSING;
	EntityManager::destroyAll();
}

void Game::close(){
	sf::RenderWindow::close();
	EntityManager::destroyAll();
	EntityManager::removeDeadEntities();
	state = CLOSED;
}

sf::FloatRect Game::getCameraRect(){
	sf::Vector2f cameraPosition = {getView().getCenter().x - (getSize().x / 2.0f), getView().getCenter().y - (getSize().y / 2.0f)};
	sf::FloatRect viewRect = {cameraPosition.x, cameraPosition.y, (float)getSize().x, (float)getSize().y};
	return viewRect;
}