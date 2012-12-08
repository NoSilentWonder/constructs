/*
	Copyright	Kangaroo Magic 2011
	Created 	Elinor Townsend
	
	Name		MenuState
	Brief		Definition of MenuState class methods
*/

#include "IwGx.h"
#include "Game.hpp"
#include "MenuState.hpp"
#include "TitleState.hpp"
#include "PlayState.hpp"
#include "Input.hpp"
#include "MusicPlayer.hpp"
#include "Video.hpp"

/*
	Name		MenuState::getNextState
	Syntax		MenuState::getNextState(Condition condition)
	Param		Condition condition - Condition parameter used to determine the next state
	Return		State* - A pointer to the next state type object
	Brief		Creates a new object of the next state type
*/
State* MenuState::getNextState(Condition condition)
{
    State *state;
    switch (condition) 
	{
		case CONDITION_GO_TO_TITLE : 
			state = new TitleState;
			break;

		case CONDITION_GO_TO_SETTINGS :
			state = 0; //new SettingsState;

		case CONDITION_GO_TO_PLAY : 
			state = new PlayState;
			break;

		default : 
			state = 0;
			break;
	}
	return state;
}

/*
	Name		MenuState::initialise
	Syntax		MenuState::initialise()
	Brief		Initialises the state
*/
void MenuState::initialise()
{
	musicPlayer_ = new MusicPlayer;
	musicPlayer_->play("music/compressed/Constructs1.mp3");

	intro_ = new Video;
	intro_->initialise("cutscenes/1Intro.mp4");
	introPlayed_ = false;

    // Set the background colour to (opaque) red
    IwGxSetColClear(0xff, 0, 0, 0xff);
	
	background_.initialise("menu_background.png", 1024, 768, 512, 384);

	input_ = Game::instance()->getInput();

	playButton_ = new CircularButton("play.png", 700, 540, 0, 35, false);

	changeState_ = false;
}

/*
	Name		MenuState::deinitialise
	Syntax		MenuState::deinitialise()
	Brief		Deinitialises the state
*/
void MenuState::deinitialise()
{
	delete playButton_;
	playButton_ = 0;

	background_.deinitialise();

	musicPlayer_->stop();
	delete musicPlayer_;
	musicPlayer_ = 0;
	if (intro_->isPlaying())
		intro_->stop();
	delete intro_;
	intro_ = 0;
}

/*
	Name		MenuState::update
	Syntax		MenuState::update()
	Brief		Updates the state
	Details		Time-critical logic updates are performed by this method
*/
void MenuState::update()
{

}

/*
	Name		MenuState::independentUpdate
	Syntax		MenuState::independentUpdate(float deltaTime)
	Param		float deltaTime - The time taken for the frame to run
	Brief		Updates the state
*/
void MenuState::independentUpdate(float deltaTime)
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
		Touch* touch = input_->getTouch(0);
		if (touch != NULL)
		{
			if (!introPlayed_)
			{
				// Add update input effects here
				if( playButton_->collisionDetection( touch->x_, touch->y_) )
				{
					introPlayed_ = true;
					musicPlayer_->stop();
					intro_->play();
				}
			}
		}

		// if multi-touch is available then ...
		if (input_->isMultiTouch())
		{
			if (input_->getTouchCount() > 1)
			{
				touch = input_->getTouch(1);
				if (touch != NULL)
				{
					// Add update input effects here
				}
			}
		}
	}
	if (input_->getTouchCount() == 0)
	{
		// Stop touch events
	}

	if (introPlayed_)
	{
		if (!intro_->isPlaying())
		{
			changeState_ = true;
		}
	}

	if( changeState_ )
	{
		// DELETE LATER USED FOR TESTING PURPOSES ONLY	
		Game::instance()->changeCondition(CONDITION_GO_TO_PLAY);
	}
}

/*
	Name		MenuState::render
	Syntax		MenuState::render()
	Brief		Renders the state
*/
void MenuState::render()
{
	// Clear the surface
    IwGxClear();

	// Render background
	background_.render();

	playButton_->render();

    // Standard EGL-style flush of drawing to the surface
    IwGxFlush();

    // Standard EGL-style flipping of double-buffers
    IwGxSwapBuffers();
      
    // Sleep for 0ms to allow the OS to process events etc.
    s3eDeviceYield(0);
}
