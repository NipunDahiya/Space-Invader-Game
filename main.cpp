#include <iostream>
#include "Game.h"
#include <time.h>



int main()
{

	srand(time(nullptr));
	Game game; 
	game.run();


	return 0;

}