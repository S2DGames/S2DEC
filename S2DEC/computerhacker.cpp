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

void loadWorld1(Game* game){
	Entity& background = game->createEntity("Background");
	background.addComponent<Background>(game, "resources/Level1.png");

	Entity& hacker = game->createEntity("Hacker");
	HackerPhysics& hp = hacker.addComponent<HackerPhysics>(game, sf::Vector2f{100.0f, 10.0f});
	hacker.addComponent<ComputerAttack>(game);
	hacker.addComponent<HackerImage>(game, "resources/heroWalking.png");
	hacker.addComponent<Health>(10);
	hacker.addComponent<HealthBar>(game);

	Entity& floor = game->createEntity("Floor");
	Floor& f = floor.addComponent<Floor>(game);
	//World 1
	f.addVertex({0.0f / SCALE, 0.0f / SCALE});
	f.addVertex({0.0f / SCALE, 720.0f / SCALE});
	f.addVertex({2560.0f / SCALE, 720.0f / SCALE});
	f.addVertex({2560.0f / SCALE, 0.0f / SCALE});

	Entity& enemy = game->createEntity("Enemy");
	enemy.addComponent<EnemyMovement>(game, &hp, stand, sf::Vector2f{600, 500});// , sf::Vector2f{ 700, 500 });
	enemy.addComponent<EnemyPhysics>(game);
	enemy.addComponent<EnemyImage>("resources/hacker.png");
	enemy.addComponent<Health>(2);

	Entity& levelExit = game->createEntity("LevelExit");
	levelExit.addComponent<LevelExit>(game, sf::Vector2f{840.0f, 700.0f}, "resources/hacker.png");
}

void loadWorld2(Game* game){
	Entity& background = game->createEntity("Background");
	background.addComponent<Background>(game, "resources/Level1.png");

	Entity& hacker = game->createEntity("Hacker");
	HackerPhysics& hp = hacker.addComponent<HackerPhysics>(game, sf::Vector2f{10.0f, 10.0f});
	hacker.addComponent<HackerImage>(game, "resources/hacker.png");
	hacker.addComponent<Health>(10);
	hacker.addComponent<HealthBar>(game);
	hacker.addComponent<ComputerAttack>(game);

	Entity& floor = game->createEntity("Floor");
	Floor& f = floor.addComponent<Floor>(game);

	//World 2
	f.addVertex({0.0f / SCALE, 0.0f / SCALE});
	f.addVertex({0.0f / SCALE, 360.0f / SCALE});
	f.addVertex({840.0f / SCALE, 360.0f / SCALE});
	f.addVertex({840.0f / SCALE, 420.0f / SCALE});
	f.addVertex({1640.0f / SCALE, 420.0f / SCALE});
	f.addVertex({1640.0f / SCALE, 480.0f / SCALE});
	f.addVertex({2040.0f / SCALE, 480.0f / SCALE});
	f.addVertex({2040.0f / SCALE, 620.0f / SCALE});
	f.addVertex({2640.0f / SCALE, 620.0f / SCALE});
	f.addVertex({2640.0f / SCALE, 800.0f / SCALE});
	f.addVertex({3640.0f / SCALE, 800.0f / SCALE});
	f.addVertex({3640.0f / SCALE, 690.0f / SCALE});
	f.addVertex({4040.0f / SCALE, 690.0f / SCALE});
	f.addVertex({4040.0f / SCALE, 580.0f / SCALE});
	f.addVertex({5240.0f / SCALE, 580.0f / SCALE});
	f.addVertex({5240.0f / SCALE, 440.0f / SCALE});
	f.addVertex({6440.0f / SCALE, 440.0f / SCALE});
	f.addVertex({6440.0f / SCALE, 300.0f / SCALE});
	f.addVertex({8000.0f / SCALE, 300.0f / SCALE});
	f.addVertex({8000.0f / SCALE, 0.0f / SCALE});

	Entity& enemy = game->createEntity("Enemy");
	enemy.addComponent<EnemyMovement>(game, &hp, stand, sf::Vector2f{600, 500});// , sf::Vector2f{ 700, 500 });
	enemy.addComponent<EnemyPhysics>(game);
	enemy.addComponent<EnemyImage>("resources/heroWalking.png");
	enemy.addComponent<Health>(2);
}

void loadWorld4(Game* game){

	Entity& background = game->createEntity("Background");
	background.addComponent<Background>(game, "resources/Level1.png");

	Entity& hacker = game->createEntity("Hacker");
	HackerPhysics& hp = hacker.addComponent<HackerPhysics>(game, sf::Vector2f{10.0f, 10.0f});
	hacker.addComponent<HackerImage>(game, "resources/heroWalking.png");
	hacker.addComponent<Health>(10);
	hacker.addComponent<HealthBar>(game);
	hacker.addComponent<ComputerAttack>(game);

	//Floors and walls
	Entity& floor = game->createEntity("Floor");
	Floor& f = floor.addComponent<Floor>(game);
	f.addVertex({0.0f / SCALE, 0.0f / SCALE});
	f.addVertex({0.0f / SCALE, 720.0f / SCALE});
	f.addVertex({1280.0f / SCALE, 720.0f / SCALE});
	f.addVertex({1280.0f / SCALE, 0.0f / SCALE});

	//Top Platform
	Entity& floor1 = game->createEntity("Floor1");
	Floor& f1 = floor1.addComponent<Floor>(game);
	f1.addVertex({120.0f / SCALE, 240.0f / SCALE});
	f1.addVertex({1160.0f / SCALE, 240.0f / SCALE});

	//Bottom Left Platform
	Entity& floor2 = game->createEntity("Floor2");
	Floor& f2 = floor2.addComponent<Floor>(game);
	f2.addVertex({0.0f / SCALE, 480.0f / SCALE});
	f2.addVertex({300.0f / SCALE, 480.0f / SCALE});

	//Top Right Platform
	/*Entity& floor3 = game->createEntity("Floor3");
	Floor& f3 = floor3.addComponent<Floor>(game);
	f3.addVertex({ 1040.0f / SCALE, 240.0f / SCALE });
	f3.addVertex({ 1280.0f / SCALE, 240.0f / SCALE });*/

	//Bottom Right Platform
	Entity& floor4 = game->createEntity("Floor4");
	Floor& f4 = floor4.addComponent<Floor>(game);
	f4.addVertex({920.0f / SCALE, 480.0f / SCALE});
	f4.addVertex({1280.0f / SCALE, 480.0f / SCALE});

	//Bottom Left Jumping Platform
	Entity& floor5 = game->createEntity("Floor5");
	Floor& f5 = floor5.addComponent<Floor>(game);
	f5.addVertex({360.0f / SCALE, 600.0f / SCALE});
	f5.addVertex({420.0f / SCALE, 600.0f / SCALE});

	//Top Left Jumping Platform
	Entity& floor6 = game->createEntity("Floor6");
	Floor& f6 = floor6.addComponent<Floor>(game);
	f6.addVertex({0.0f / SCALE, 360.0f / SCALE});
	f6.addVertex({60.0f / SCALE, 360.0f / SCALE});

	//Bottom Right Jumping Platform
	Entity& floor7 = game->createEntity("Floor7");
	Floor& f7 = floor7.addComponent<Floor>(game);
	f7.addVertex({800.0f / SCALE, 600.0f / SCALE});
	f7.addVertex({860.0f / SCALE, 600.0f / SCALE});

	//Top Right Jumping Platform
	Entity& floor8 = game->createEntity("Floor8");
	Floor& f8 = floor8.addComponent<Floor>(game);
	f8.addVertex({1220.0f / SCALE, 360.0f / SCALE});
	f8.addVertex({1280.0f / SCALE, 360.0f / SCALE});


	Entity& boss = game->createEntity("Boss1");
	EnemyMovement* bossOne = &boss.addComponent<EnemyMovement>(game, &hp, boss1, sf::Vector2f{640, 240});
	boss.addComponent<EnemyPhysics>(game);
	boss.addComponent<EnemyImage>("resources/FatKidRun.png");
	//boss.addComponent<Health>(2);
	bossOne->setSpeed(5.0f);
	setBoss1Vectors(bossOne);

}

void setBoss1Vectors(EnemyMovement* e){
	vector<sf::Vector2f> points;
	points.push_back({640.0f, 240.0f});
	points.push_back({1160.0f, 240.0f});
	points.push_back({1250.0f, 360.0f});
	points.push_back({1160.0f, 480.0f});
	points.push_back({920.0f, 480.0f});
	points.push_back({830.0f, 600.0f});
	points.push_back({770.0f, 720.0f});
	points.push_back({640.0f, 720.0f});
	points.push_back({480.0f, 720.0f});
	points.push_back({390.0f, 600.0f});
	points.push_back({300.0f, 480.0f});
	points.push_back({120.0f, 480.0f});
	points.push_back({30.0f, 360.0f});
	points.push_back({120.0f, 240.0f});
	points.push_back({60.0f, 480.0f});
	points.push_back({1220.0f, 480.0f});
	points.push_back({30.0f, 720.0f});
	points.push_back({1250.0f, 720.0f});
	e->setMapPointVectors(points);
}