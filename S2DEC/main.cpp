#include "TestObject.h"
#include "TestObject2.h"

using namespace S2D;

int main(){
	Game game(720, 568, "S2DEC");
	TestObject test(&game);
	game.play();
	return 0;
}