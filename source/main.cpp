/*
	Copyright	Kangaroo Magic 2011
	Created 	Elinor Townsend
	
	Name		main
	Brief		Constructs of Friendship game entry point
*/

#include "Game.hpp"

/*
	Name		main
	Syntax		main()
	Return		int - May be used for debugging
	Brief		Standard program entry point
*/
int main()
{
    Game* game;

	game = Game::instance();	
	game->initialise();
	
	game->run();
	
	game->deinitialise();
	delete game;

    // Return
    return 0;
}
