/*
	Copyright	Kangaroo Magic 2011
	Created 	Elinor Townsend
	
	Name		TitleState
	Brief		Definition of TitleState class methods
*/

#include "IwGx.h"
#include "Iw2D.h"

#include "TitleState.hpp"
#include "MenuState.hpp"	
#include "Game.hpp"
#include "Input.hpp"


/*
	Name		TitleState::TitleState
	Syntax		TitleState()
	Brief		TitleState constructor initialises member variables
*/
TitleState::TitleState()
{
	screenWidth_ = IwGxGetScreenWidth();
	screenHeight_ = IwGxGetScreenHeight();
	
}

/*
	Name		TitleState::~TitleState
	Syntax		~TitleState()
	Brief		TitleState destructor
*/
TitleState::~TitleState()
{

}

/*
	Name		TitleState::getNextState
	Syntax		TitleState::getNextState(Condition condition)
	Param		Condition condition - Condition parameter used to determine the next state
	Return		State* - A pointer to the next state type object
	Brief		Creates a new object of the next state type
*/
State* TitleState::getNextState(Condition condition)
{
	State* state = NULL;
    switch (condition) 
	{
		case CONDITION_GO_TO_MENU : 
			state = new MenuState;
			break;

		default : 
			state = NULL;
			break;
	}
	return state;
}

/*
	Name		TitleState::initialise
	Syntax		TitleState::initialise()
	Brief		Initialises the state
*/
void TitleState::initialise()
{
    // Set the background colour to (opaque) blue
    IwGxSetColClear(0, 0, 0xff, 0xff);

	input_ = Game::instance()->getInput();

	splashScreen_ = new GraphicsObject("SplashScreen.png", CIwSVec2(0,0), CIwSVec2(1024, 768));
}

/*
	Name		TitleState::deinitialise
	Syntax		TitleState::deinitialise()
	Brief		Deinitialises the state
*/
void TitleState::deinitialise()
{
	splashScreen_->deinitialise();
	delete splashScreen_;
	splashScreen_ = 0;
}

/*
	Name		TitleState::update
	Syntax		TitleState::update()
	Brief		Updates the state
	Details		Time-critical logic updates are performed by this method
*/
void TitleState::update()
{

}

/*
	Name		TitleState::independentUpdate
	Syntax		TitleState::independentUpdate(float deltaTime)
	Param		float deltaTime - The time taken for the frame to run
	Brief		Updates the state
*/
void TitleState::independentUpdate(float deltaTime)
{
	screenWidth_ = IwGxGetScreenWidth();
	screenHeight_ = IwGxGetScreenHeight();

	// Rotates the screen so that it is always displayed in landscape on the device
	if (screenWidth_ < screenHeight_)
	{
		IwGxSetScreenOrient(IW_GX_ORIENT_90);
	}

	// Update pointer system
	input_->update();
	if (input_->getTouchCount() != 0)
	{
		Game::instance()->changeCondition(CONDITION_GO_TO_MENU);
	}
}

/*
	Name		TitleState::render
	Syntax		TitleState::render()
	Brief		Renders the state
*/
void TitleState::render()
{
		// Clear the surface
        IwGxClear();

		splashScreen_->render();

        // Standard EGL-style flush of drawing to the surface
        IwGxFlush();

        // Standard EGL-style flipping of double-buffers
        IwGxSwapBuffers();
        
        // Sleep for 0ms to allow the OS to process events etc.
        s3eDeviceYield(0);
}
