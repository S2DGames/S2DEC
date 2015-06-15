#include "Game.h"
#include "Games/Pong/Pong.h"
#include "Games/Snake/SnakeScene.h"
#include "Games/SpaceInvaders/SpaceInvaders.h"

using namespace S2D;

int main(){

	Game game(1280, 840, "S2DEC");
	game.init();

	//loadPong(&game);
	//loadSnake(&game);
	//loadSpaceInvaders(&game);

	game.play();
	game.close();

	return 0;
}