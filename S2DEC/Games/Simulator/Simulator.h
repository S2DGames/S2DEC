#include "Sim.h"
#include "House.h"
#include "AI.h"

void loadSimulator(Game* game){

	sf::Vector2f house1Pos = game->getViewPosition(TOP_LEFT);
	house1Pos.x += 300;
	house1Pos.y += 200;
	game->createEntity("house1").addComponent<House>("resources/simulator/house.png", sfTob2(house1Pos));

	sf::Vector2f house2Pos = game->getViewPosition(TOP_LEFT);
	house2Pos.x += 980;
	house2Pos.y += 200;
	game->createEntity("house2").addComponent<House>("resources/simulator/house.png", sfTob2(house2Pos));

	sf::Vector2f house3Pos = game->getViewPosition(TOP_LEFT);
	house3Pos.x += 980;
	house3Pos.y += 520;
	game->createEntity("house3").addComponent<House>("resources/simulator/house.png", sfTob2(house3Pos));

	sf::Vector2f house4Pos = game->getViewPosition(TOP_LEFT);
	house4Pos.x += 300;
	house4Pos.y += 520;
	game->createEntity("house4").addComponent<House>("resources/simulator/house.png", sfTob2(house4Pos));

	sf::Vector2f startingPos = {420.0f,150.0f};//game->getRandomPointInView();
	Entity& sim1 = game->createEntity("sim1");
	sim1.addComponent<Sim>("resources/simulator/sim.png", sfTob2(startingPos));
	sim1.addComponent<AI>((NPC&)sim1.getComponent<Sim>());

	startingPos = game->getRandomPointInView();
	Entity& sim2 = game->createEntity("sim2");
	//sim2.addComponent<Sim>("resources/simulator/sim.png", sfTob2(startingPos));
	//sim2.addComponent<AI>((NPC&)sim2.getComponent<Sim>());

	startingPos = game->getRandomPointInView();
	Entity& sim3 = game->createEntity("sim3");
	//sim3.addComponent<Sim>("resources/simulator/sim.png", sfTob2(startingPos));
	//sim3.addComponent<AI>((NPC&)sim3.getComponent<Sim>());

	/*startingPos = game->getRandomPointInView();
	Entity& sim4 = game->createEntity("sim4");
	sim4.addComponent<Sim>("resources/simulator/sim.png", sfTob2(startingPos));
	sim4.addComponent<AI>((NPC&)sim4.getComponent<Sim>());

	startingPos = game->getRandomPointInView();
	Entity& sim5 = game->createEntity("sim5");
	sim5.addComponent<Sim>("resources/simulator/sim.png", sfTob2(startingPos));
	sim5.addComponent<AI>((NPC&)sim5.getComponent<Sim>());

	startingPos = game->getRandomPointInView();
	Entity& sim6 = game->createEntity("sim6");
	sim6.addComponent<Sim>("resources/simulator/sim.png", sfTob2(startingPos));
	sim6.addComponent<AI>((NPC&)sim6.getComponent<Sim>());

	startingPos = game->getRandomPointInView();
	Entity& sim7 = game->createEntity("sim7");
	sim7.addComponent<Sim>("resources/simulator/sim.png", sfTob2(startingPos));
	sim7.addComponent<AI>((NPC&)sim7.getComponent<Sim>());
	*/
}