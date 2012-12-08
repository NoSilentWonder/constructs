/*
	Copyright	Kangaroo Magic 2011
	Created 	Jonathan Jones
	
	Name		PlayState
	Brief		Definition of PlayState class methods
*/

// Includes 
#include "PlayState.hpp"
#include "MenuState.hpp"
#include "Game.hpp"
#include "Input.hpp"
#include "ShipLevel.hpp"
//#include "ShipBuildingArea.hpp"
#include "LevelList.hpp"
#include "Level1.hpp"


/*
	Name		PlayState::getNextState
	Syntax		PlayState::getNextState(Condition condition)
	Param		Condition condition - Condition parameter used to determine the next state
	Return		State* - A pointer to the next state type object
	Brief		Creates a new object of the next state type
*/
State* PlayState::getNextState(Condition condition)
{
	State *state;
    switch (condition) 
	{
		case CONDITION_GO_TO_MENU : 
			state = new MenuState;
			break;

		default : 
			state = 0;
			break;
	}
	return state;
}

/*
	Name		PlayState::initialise
	Syntax		PlayState::initialise()
	Brief		Initialises the state
*/
void PlayState::initialise()	
{
	// Set the background colour to (opaque) white
    IwGxSetColClear(0xff, 0xff, 0xff, 0xff);

	// Set the pointer to input to the input object
	input_ = Game::instance()->getInput();

	// Initialise the alien
	alien_.initialise();

	// Initialsie the robot
	robot_.initialise();

	// Create all the levels
	shipLevel_			=	new ShipLevel(&alien_, &robot_, input_);
	shipBuildingLevel_	=	new ShipBuildingArea(&alien_, &robot_, input_);
	level1_				=	new Level1(&alien_, &robot_, input_);

	// Set the current level
	//currentLevel_ = new Level1(&alien_, &robot_, input_); //  ShipLevel   ShipBuildingArea
	currentLevel_ = shipLevel_;

	// Initialise the current level
	currentLevel_->initialise();

	//shipBuildingLevel_->playerEnteringFromLevel1();

	// Set level1WasLastLevel bool
	level1WasLastLevel = false;
}

/*
	Name		PlayState::deinitialise
	Syntax		PlayState::deinitialise()
	Brief		Deinitialises the state
*/
void PlayState::deinitialise()						
{
	// Deinitialise the current level
	currentLevel_->deinitialise();

	// Delete ship level
	delete shipLevel_;
	shipLevel_ = 0;

	// Delete ship building level
	delete shipBuildingLevel_;
	shipBuildingLevel_ = 0;

	// Delete level1
	delete level1_;
	level1_ = 0;

	// Set the current level pointer to zero for saftey
	currentLevel_ = 0;

	// Deinitialise the robot
	robot_.deinitialise();

	// Deinitialise the alien
	alien_.deinitialise();


}

/*
	Name		PlayState::update
	Syntax		PlayState::update()
	Brief		Update the objects in the state
*/
void PlayState::update()
{
	// Update the current level
	currentLevel_->update();

	// If the level indicated it needs to move to the next level
	if(currentLevel_->moveToNextLevel() )
	{
		// Change the level
		PlayState::changeLevel();
	}
}

/*
	Name		PlayState::independentUpdate
	Syntax		PlayState::independentUpdate(float deltaTime)
	Param		float deltaTime - The time taken for the frame to run
	Brief		Update all elements which only need to be updated once ?per frame?
*/
void PlayState::independentUpdate(float deltaTime)
{
	// Set the screen width and height 
	screenWidth_ = IwGxGetScreenWidth();
	screenHeight_ = IwGxGetScreenHeight();

	// Rotates the screen so that it is always displayed in landscape on the device
	if (screenWidth_ < screenHeight_)
	{
		IwGxSetScreenOrient(IW_GX_ORIENT_90);
	}

	// Call independant update on the level
	currentLevel_->independentUpdate(deltaTime);
}

/*
	Name		PlayState::render
	Syntax		PlayState::render()
	Brief		Renders the state
*/
void PlayState::render()
{
	// Clear the surface
    IwGxClear();

	// Render the current level
	currentLevel_->render();

	// Standard EGL-style flush of drawing to the surface
    IwGxFlush();

    // Standard EGL-style flipping of double-buffers
    IwGxSwapBuffers();
      
    // Sleep for 0ms to allow the OS to process events etc.
    s3eDeviceYield(0);
}

/*
	Name		PlayState::changeLevel
	Syntax		PlayState::changeLevel()
	Brief		Changes the current level
*/
void PlayState::changeLevel()
{
	if(currentLevel_ == level1_)
	{
		level1WasLastLevel = true;
	}
	// Get the level which should be displayed next  
	// Set current level to that level
	switch(currentLevel_->getNextLevel())
	{
	case SHIP_BUILDING_AREA:
		{
			currentLevel_->deinitialise();
			currentLevel_->playerMovedLevel();
			//delete currentLevel_;
			//currentLevel_ = new ShipBuildingArea(&alien_, &robot_, input_);
			currentLevel_ = shipBuildingLevel_;
			currentLevel_->initialise();
			
			if(level1WasLastLevel)
			{
				shipBuildingLevel_->playerEnteringFromLevel1();
				level1WasLastLevel = false;
			}

			break;
		}	// end case SHIP_BUILDING_AREA
	case LEVEL_1:
		{
			currentLevel_->deinitialise();
			currentLevel_->playerMovedLevel();
			//delete currentLevel_;
			//currentLevel_ = new Level1(&alien_, &robot_, input_);
			currentLevel_ = level1_;
			currentLevel_->initialise();
			break;
		}	// end case LEVEL_1
	}	// end switch
}