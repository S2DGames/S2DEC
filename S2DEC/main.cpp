#include "Game.h"
#include "Computer Hacker/HackerPhysics.h"
#include "Computer Hacker/HackerImage.h"
#include "Computer Hacker/Floor.h"
#include "Computer Hacker/EnemyMovement.h"
#include "Computer Hacker/EnemyPhysics.h"
#include "Computer Hacker/EnemyImage.h"
#include "Util.h"

using namespace S2D;

int main(){
	Game game(1280, 720, "S2DEC");
	game.SetGravity({0, .5 * SCALE});
	
	Entity& hacker = game.createEntity("Hacker");
	hacker.addComponent<HackerPhysics>(&game);
	hacker.addComponent<HackerImage>(&game, "resources/hacker.png");

	Entity& floor = game.createEntity("Floor");
	Floor& f = floor.addComponent<Floor>(&game);
	f.addVertex({0.0f / SCALE, 720.0f / SCALE});
	f.addVertex({1280.0f / SCALE, 720.0f / SCALE});

	Entity& enemy = game.createEntity("Enemy");
	enemy.addComponent<EnemyMovement>(&game, patrol, sf::Vector2f{600, 500}, sf::Vector2f{700, 500});
	enemy.addComponent<EnemyPhysics>(&game);
	enemy.addComponent<EnemyImage>("resources/hacker.png");

	game.init();
	game.play();
	return 0;
}