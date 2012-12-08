/*
	Copyright	Kangaroo Magic 2011
	Created 	Jonathan Jones
	
	Name		PlayState
	Brief		Declaration of PlayState cClass inherited from State
*/

#ifndef PLAY_STATE_HPP
#define PLAY_STATE_HPP

#include <memory>				// Necessary for unique_ptr

#include "State.hpp"
#include "Alien.hpp"
#include "Robot.hpp"
#include "Level.hpp"
#include "ShipBuildingArea.hpp"


/*
	Name		PlayState class
	Brief		The PlayState includes all the levels included within the game
*/
class PlayState : public State
{
public:
	State *getNextState(Condition condition);	// See state.hpp 
	void initialise();							// See state.hpp 
	void deinitialise();						// See state.hpp 
	void update();								// See state.hpp 
	void independentUpdate(float deltaTime);	// See state.hpp 
	void render();								// See state.hpp 

	void changeLevel();
private:
	Alien alien_;
	Robot robot_;
	Level *currentLevel_;
	Level *shipLevel_;
	ShipBuildingArea *shipBuildingLevel_;
	Level *level1_;
	bool level1WasLastLevel;
};

#endif	// PLAY_STATE_HPP