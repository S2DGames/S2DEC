#include "Game.h"
#include "Games/Pong/Pong.h"
#include "Games/Snake/SnakeScene.h"
#include "squaregame.h"
//#include "Games/SpaceInvaders/SpaceInvaders.h"

using namespace S2D;

int main(){

	//set resolution and title in the game constructor
	Game game(1280, 720, "S2DEC", true);

	//call functions to enable or disable certain settings such as fullscreen, vsync, fps limit, aa
	//game.setFullScreen();
	//These functions can be called after the window is created. They will just cause the window to be 
	//closed then opened again with the new settings.

	//load your entities and components.
	//It is probably best to do this before init so the player is not waiting for
	//everything to load with a black screen. If you want to add a loading screen,
	//you need to call init first.
	//loadPong(&game);
	//loadSnake(&game);
	loadsquaregame(&game);

	//the window is created when init is called.
	game.init();

	//The entry point to the main loop.
	GameState gs = game.play();

	if(gs == CLOSING){
		//once the game finishes/is exited, call this to ensure everything closes properly.
		game.close();
	}else{
		//close it anyway. there isnt anything else we want to do with it
		game.close();
	}
	return 0;
}