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
		lightSystemEnabled(lighting),
		mt(rd()){
	state = INITIALIZING;
	style = sf::Style::Resize;
	title = name;
	SCREEN_SIZE = {width, height};
	videoMode.width = width;
	videoMode.height = height;
	videoMode.bitsPerPixel = 32;
	b2World::SetContactListener(this);

	timeStep = 0.0f;
}

void Game::init(){
	//sf::Vector2i position = {(int)(sf::VideoMode::getDesktopMode().width / 2), (int)(sf::VideoMode::getDesktopMode().height / 2)};
	//settings.antialiasingLevel = 2;
	sf::RenderWindow::create(videoMode, title, style, settings);
	//sf::RenderWindow::setPosition(position);
	
	if(lightSystemEnabled){
		unshadowShader.loadFromFile("resources/LTBL2/unshadowShader.vert", "resources/LTBL2/unshadowShader.frag");
		lightOverShapeShader.loadFromFile("resources/LTBL2/lightOverShapeShader.vert", "resources/LTBL2/lightOverShapeShader.frag");
		penumbraTexture.loadFromFile("resources/LTBL2/penumbraTexture.png");
		penumbraTexture.setSmooth(true);
		ltbl::LightSystem::create(sf::FloatRect(-1000.0f, -1000.0f, 1000.0f, 1000.0f), sf::RenderWindow::getSize(), penumbraTexture, unshadowShader, lightOverShapeShader);
		directionLightTexture.loadFromFile("resources/LTBL2/directionLightTexture.png");
		directionLightTexture.setSmooth(true);

		globalLightSprite.setOrigin(getSize().x / 2.0f, getSize().y / 2.0f);
		globalLightSprite.setPosition(getView().getCenter());

		ltbl::LightSystem::_ambientColor = sf::Color::Black;
	}

	/*gridTexture.create(videoMode.width, videoMode.height);
	gridTexture.clear(sf::Color::Transparent);
	sf::RectangleShape rs;
	for(int i = 1; i < getSize().x; i += gridSpacing){
		for(int j = 0; j < getSize().y; j += gridSpacing){
			rs.setSize({(float)gridSpacing, (float)gridSpacing});
			rs.setPosition(i, j);
			rs.setFillColor(sf::Color::Transparent);
			rs.setOutlineColor(sf::Color::White);
			rs.setOutlineThickness(.5);
			gridTexture.draw(rs);
		}
	}
	gridTexture.display();
	gridSprite.setTexture(gridTexture.getTexture());
	gridSprite.setOrigin(getSize().x / 2.0f, getSize().y / 2.0f);
	gridHoveringOver.setSize({(float)gridSpacing - 1.0f, (float)gridSpacing - 1.0f});
	gridHoveringOver.setFillColor(sf::Color::Red);
	sf::Vector2i mousePos = Controls::getMousePos();
	gridPosition = {(mousePos.x - mousePos.x % gridSpacing) + 1, (mousePos.y - mousePos.y % gridSpacing) + 2};*/
}

void Game::setSize(const sf::Vector2u size){
	SCREEN_SIZE = size;
	//sf::RenderWindow::close();
	videoMode.width = size.x;
	videoMode.height = size.y;
	sf::RenderWindow::setSize(size);
	//sf::RenderWindow::setPosition({(int)(sf::VideoMode::getDesktopMode().width / 2), (int)(sf::VideoMode::getDesktopMode().height / 2)});
	//init();
}

sf::Vector2u Game::getSize(){
	return{videoMode.width, videoMode.height};
}

sf::Vector2f Game::getViewPosition(ViewPositionCoordinateType type){
	switch(type){
	case CENTER:
		return sf::RenderWindow::getView().getCenter();
	case TOP_LEFT:
		return{getViewPosition().x - (sf::RenderWindow::getView().getSize().x / 2.0f), getViewPosition().y - (sf::RenderWindow::getView().getSize().y / 2.0f)};
		//return{getViewPosition().x - (getSize().x / 2.0f), getViewPosition().y - (getSize().x / 2.0f)};
	}
	return {0.0f, 0.0f};
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

		//draw grid
		/*gridSprite.setPosition(getViewPosition());
		sf::RenderWindow::draw(gridSprite);

		sf::Vector2i mousePos = Controls::getMousePos();
		sf::Vector2i newGrid = {(mousePos.x - mousePos.x % gridSpacing) + 1, (mousePos.y - mousePos.y % gridSpacing) + 1};
		
		gridHoveringOver.setPosition(newGrid.x, newGrid.y);
		sf::RenderWindow::draw(gridHoveringOver);
		if(getMouseState(sf::Mouse::Left) == KEY_PRESSED){
			cout << newGrid.x - 1.0f << ":" << newGrid.y - 1.0f << endl;
		}
		gridPosition = newGrid;*/

		//draw objects in the scene and display
		//sf::RectangleShape white;
		//white.setSize({(float)getSize().x, (float)getSize().y});
		//white.setFillColor(sf::Color::White);
		//white.setOrigin(white.getSize().x / 2.0f, white.getSize().y / 2.0f);
		//white.setPosition(getViewPosition(ViewPositionCoordinateType::CENTER));
		//sf::RenderWindow::draw(white);
		EntityManager::draw(*this);
		
		if(lightSystemEnabled){
			ltbl::LightSystem::render(sf::RenderWindow::getView(), unshadowShader, lightOverShapeShader);
			globalLightSprite.setTexture(ltbl::LightSystem::getLightingTexture());
			sf::RenderWindow::draw(globalLightSprite, sf::BlendMultiply);
		}
		
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

int Game::getRandomInt(uniform_int_distribution<int> dist){
	return dist(mt);
}

sf::Vector2f Game::getRandomPointInView(){
	uniform_int_distribution<int> xDist(getViewPosition(S2D::TOP_LEFT).x, getView().getSize().x);
	uniform_int_distribution<int> yDist(getViewPosition(S2D::TOP_LEFT).y, getView().getSize().y);
	return{(float)xDist(mt), (float)yDist(mt)};
}