/*
	Copyright	Kangaroo Magic 2011
	Created 	Elinor Townsend
	
	Name		TestState
	Brief		Definition of TestState class methods
*/

#include "IwGx.h"
#include "Iw2D.h"

#include "TestState.hpp"
#include "MenuState.hpp"	
#include "Game.hpp"
#include "Input.hpp"


/*
	Name		TestState::TestState
	Syntax		TestState()
	Brief		TestState constructor initialises member variables
*/
TestState::TestState()
{
	screenWidth_ = IwGxGetScreenWidth();
	screenHeight_ = IwGxGetScreenHeight();	
}

/*
	Name		TestState::~TestState
	Syntax		~TestState()
	Brief		TestState destructor
*/
TestState::~TestState()
{
	
}

/*
	Name		TestState::getNextState
	Syntax		TestState::getNextState(Condition condition)
	Param		Condition condition - Condition parameter used to determine the next state
	Return		State* - A pointer to the next state type object
	Brief		Creates a new object of the next state type
*/
State* TestState::getNextState(Condition condition)
{
	State* state = NULL;
	return state;
}

/*
	Name		TestState::initialise
	Syntax		TestState::initialise()
	Brief		Initialises the state
*/
void TestState::initialise()
{
    // Set the background colour to white
    IwGxSetColClear(0xff, 0xff, 0xff, 0xff);

	input_ = Game::instance()->getInput();

	background_.initialise("TestLayer3.txt");
	midground_.initialise("TestLayer2.txt");
	foreground_.initialise("TestLayer1.txt");

}

/*
	@Name		TestState::deinitialise
	@Syntax		TestState::deinitialise()
	@Brief		Deinitialises the state
*/
void TestState::deinitialise()
{
	background_.deinitialise();
	midground_.deinitialise();
	foreground_.deinitialise();
}

/*
	Name		TestState::update
	Syntax		TestState::update()
	Brief		Updates the state
	Details		Time-critical logic updates are performed by this method
*/
void TestState::update()
{

}

/*
	Name		TestState::independentUpdate
	Syntax		TestState::independentUpdate(float deltaTime)
	Param		float deltaTime - The time taken for the frame to run
	Brief		Updates the state
*/
void TestState::independentUpdate(float deltaTime)
{
	screenWidth_ = IwGxGetScreenWidth();
	screenHeight_ = IwGxGetScreenHeight();

	// Rotates the screen so that it is always displayed in landscape on the device
	if (screenWidth_ < screenHeight_)
	{
		IwGxSetScreenOrient(IW_GX_ORIENT_90);
	}

	int direction = 0;
	// Update pointer system
	input_->update();
	if (input_->getTouchCount() != 0)
	{
		Touch* touch = input_->getTouch(0);
		if (touch != NULL)
		{
			// Add update input effects here
			if (touch->x_ > (screenWidth_/2))
			{
				direction = -1;
			}
			if (touch->x_ < (screenWidth_/2))
			{
				direction = 1;
			}
		}
	}

	background_.update(direction*deltaTime*0.1);
	midground_.update(direction*deltaTime*0.3);
	foreground_.update(direction*deltaTime*0.85);
}

/*
	Name		TestState::render
	Syntax		TestState::render()
	Brief		Renders the state
*/
void TestState::render()
{
	// Clear the surface  
	IwGxClear();

	background_.render();
	midground_.render();
	foreground_.render();

    // Standard EGL-style flush of drawing to the surface
    IwGxFlush();

    // Standard EGL-style flipping of double-buffers
    IwGxSwapBuffers();
        
    // Sleep for 0ms to allow the OS to process events etc.
    s3eDeviceYield(0);
}
