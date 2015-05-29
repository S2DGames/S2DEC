#include "Game.h"
#include "Pong.h"
#include "SnakeScene.h"

using namespace S2D;

int main(){

	Game game(1280, 840, "S2DEC");
	game.init();

	//loadPong(&game);
	loadSnake(&game);

	game.play();
	game.close();

	return 0;
}