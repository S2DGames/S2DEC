#include "Game.h"
#include "ShipImage.h"
#include "StarImage.h"
#include "Gun.h"
#include <random>

using namespace S2D;
using std::default_random_engine;
using std::uniform_real_distribution;

int main(){
	Game game(1280, 720, "S2DEC");
	default_random_engine rng;
	uniform_real_distribution<float> xDist(-(float)Game::SCREEN_SIZE.x, Game::SCREEN_SIZE.x);
	uniform_real_distribution<float> yDist(-(float)Game::SCREEN_SIZE.y, Game::SCREEN_SIZE.y);
	uniform_real_distribution<float> offsetDist(0.0f, 30.65f);
	
	for(int i = 0; i < 1000; i++){
		Entity& star = game.createEntity("star" + std::to_string(i));
		star.addComponent<StarImage>(&game, "resources/stars.png", sf::Vector2f{xDist(rng), yDist(rng)}, offsetDist(rng));
	}

	Entity& ship = game.createEntity("ship");
	ship.addComponent<ShipControls>(&game);
	ship.addComponent<ShipPhysics>(&game);
	ship.addComponent<ShipImage>("resources/ship.png");
	ship.addComponent<Gun>(&game);

	game.init();
	game.play();
	return 0;
}