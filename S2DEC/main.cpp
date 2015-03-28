#include "Game.h"
#include "ShipImage.h"
#include "StarImage.h"
#include <random>

using namespace S2D;

int main(){
	Game game(1366, 768, "S2DEC");
	std::default_random_engine rng;
	std::uniform_real_distribution<float> xDist(0, 1366);
	std::uniform_real_distribution<float> yDist(0, 768);
	std::uniform_real_distribution<float> offsetDist(0.0f, 30.65f);

	Entity* ship = new Entity("test entity");
	ship->addComponent<ShipControls>(&game);
	ship->addComponent<ShipPhysics>(&game);
	ship->addComponent<ShipImage>("resources/ship.png");

	game.addEntity(ship);
	
	for(int i = 0; i < 1000; i++){
		Entity* star = new Entity("star" + std::to_string(i));
		star->addComponent<StarImage>("resources/stars.png", sf::Vector2f{xDist(rng), yDist(rng)}, offsetDist(rng));
		game.addEntity(star);
	}

	game.init();
	game.play();
	return 0;
}