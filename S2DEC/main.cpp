#include "Game.h"

#include "Computer Hacker/HackerPhysics.h"
#include "Computer Hacker/HackerImage.h"
#include "Computer Hacker/Floor.h"
#include "Computer Hacker/EnemyMovement.h"
#include "Computer Hacker/EnemyPhysics.h"
#include "Computer Hacker/EnemyImage.h"
#include "Computer Hacker/Backbground.h"
#include "Computer Hacker/LevelExit.h"
#include "Computer Hacker/Health.h"
#include "Computer Hacker/HealthBar.h"
#include "Computer Hacker/ComputerAttack.h"

#include "Util.h"

using namespace S2D;

void loadWorld1(Game* game);
void loadWorld2(Game* game);

int main(){
	Game game(1280, 720, "S2DEC");
	game.SetGravity({0, .5 * SCALE});

	loadWorld1(&game);

	game.init();
	if(game.play() != CLOSED){
		game.removeDeadEntities();
		loadWorld2(&game);
		game.play();
	}

	game.close();
	game.removeDeadEntities();

	return 0;
}

void loadWorld1(Game* game){
	Entity& background = game->createEntity("Background");
	background.addComponent<Background>(game, "resources/Level1.png");

	Entity& hacker = game->createEntity("Hacker");
	HackerPhysics& hp = hacker.addComponent<HackerPhysics>(game, sf::Vector2f{ 10.0f, 10.0f });
	hacker.addComponent<HackerImage>(game, "resources/hacker.png");
	hacker.addComponent<Health>(10);
	hacker.addComponent<HealthBar>(game);
	hacker.addComponent<ComputerAttack>(game);

	Entity& floor = game->createEntity("Floor");
	Floor& f = floor.addComponent<Floor>(game);
	//World 1
	f.addVertex({ 0.0f / SCALE, 0.0f / SCALE });
	f.addVertex({ 0.0f / SCALE, 720.0f / SCALE });
	f.addVertex({ 2560.0f / SCALE, 720.0f / SCALE });
	f.addVertex({ 2560.0f / SCALE, 0.0f / SCALE });

	Entity& enemy = game->createEntity("Enemy");
	enemy.addComponent<EnemyMovement>(game, &hp, stand, sf::Vector2f{ 600, 500 });// , sf::Vector2f{ 700, 500 });
	enemy.addComponent<EnemyPhysics>(game);
	enemy.addComponent<EnemyImage>("resources/hacker.png");
	enemy.addComponent<Health>(2);

	Entity& levelExit = game->createEntity("LevelExit");
	enemy.addComponent<LevelExit>(game, sf::Vector2f{ 840.0f, 700.0f }, "resources/hacker.png");
}

void loadWorld2(Game* game){
	Entity& background = game->createEntity("Background");
	background.addComponent<Background>(game, "resources/Level1.png");

	Entity& hacker = game->createEntity("Hacker");
	HackerPhysics& hp = hacker.addComponent<HackerPhysics>(game, sf::Vector2f{ 10.0f, 10.0f });
	hacker.addComponent<HackerImage>(game, "resources/hacker.png");
	hacker.addComponent<Health>(10);
	hacker.addComponent<HealthBar>(game);
	hacker.addComponent<ComputerAttack>(game);

	Entity& floor = game->createEntity("Floor");
	Floor& f = floor.addComponent<Floor>(game);

	//World 2
	f.addVertex({ 0.0f / SCALE, 0.0f / SCALE });
	f.addVertex({ 0.0f / SCALE, 360.0f / SCALE });
	f.addVertex({ 840.0f / SCALE, 360.0f / SCALE });
	f.addVertex({ 840.0f / SCALE, 420.0f / SCALE });
	f.addVertex({ 1640.0f / SCALE, 420.0f / SCALE });
	f.addVertex({ 1640.0f / SCALE, 480.0f / SCALE });
	f.addVertex({ 2040.0f / SCALE, 480.0f / SCALE });
	f.addVertex({ 2040.0f / SCALE, 620.0f / SCALE });
	f.addVertex({ 2640.0f / SCALE, 620.0f / SCALE });
	f.addVertex({ 2640.0f / SCALE, 800.0f / SCALE });
	f.addVertex({ 3640.0f / SCALE, 800.0f / SCALE });
	f.addVertex({ 3640.0f / SCALE, 690.0f / SCALE });
	f.addVertex({ 4040.0f / SCALE, 690.0f / SCALE });
	f.addVertex({ 4040.0f / SCALE, 580.0f / SCALE });
	f.addVertex({ 5240.0f / SCALE, 580.0f / SCALE });
	f.addVertex({ 5240.0f / SCALE, 440.0f / SCALE });
	f.addVertex({ 6440.0f / SCALE, 440.0f / SCALE });
	f.addVertex({ 6440.0f / SCALE, 300.0f / SCALE });
	f.addVertex({ 8000.0f / SCALE, 300.0f / SCALE });
	f.addVertex({ 8000.0f / SCALE, 0.0f / SCALE });

	Entity& enemy = game->createEntity("Enemy");
	enemy.addComponent<EnemyMovement>(game, &hp, stand, sf::Vector2f{ 600, 500 });// , sf::Vector2f{ 700, 500 });
	enemy.addComponent<EnemyPhysics>(game);
	enemy.addComponent<EnemyImage>("resources/hacker.png");
	enemy.addComponent<Health>(2);
}