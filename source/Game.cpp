/*
	Copyright	Kangaroo Magic 2011
	Created 	Elinor Townsend

	Name		Game
	Brief		The method definitions for the Game class
*/

#include "s3e.h"		// Core system
#include "IwGx.h"		// Rendering
#include "IwResManager.h"
#include "Iw2D.h"
#include "derbh.h"

#include "Game.hpp"
#include "TitleState.hpp"
#include "Input.hpp"

#include "PlayState.hpp"
#include "MenuState.hpp"

Game* Game::instance_ = 0;

/*
	Name		Game::instance
	Syntax		Game::instance()
	Return		Game*- Returns pointer to the single instance of Game
	Brief		Create a single instance of Game
*/
Game* Game::instance()
{
  if (!instance_)
      instance_ = new Game();

  return instance_;
}

/*
	Name		Game::Game
	Syntax		Game()
	Brief		Game constructor initialises member variables
*/
Game::Game()
	: currentState_(0), condition_(CONDITION_GO_TO_TITLE), UPS(60), MAX_UPDATES(6)
{

}

/*
	Name		Game::~Game
	Syntax		~Game()
	Brief		Game destructor
*/
Game::~Game()
{
}

/*
	Name		Game::initialise
	Syntax		Game::initialise()
	Brief		Initialises the modules used by the game
*/
void Game::initialise()
{
	// Initialise the IwGx drawing module
	IwGxInit();

	// Initialise Iw2D drawing module
	Iw2DInit();

	// Initialise IwResManager resource manager
	IwResManagerInit();

	int32 result = dzArchiveAttach("ConstructsResources-gles1.dz");
	if (result == S3E_RESULT_ERROR)
	{
		int banana = 40;
	}

	// Create Input 
	input_ = Input::instance();
	input_->initialise();
	
	// Set initial state for the game
	currentState_ = new TitleState;  // ;PlayState TitleState
	currentState_->initialise();
}

/*
	Name		Game::deinitialise
	Syntax		Game::deinitialise()
	Brief		Releases any resources used by the game
*/
void Game::deinitialise()
{
	if (currentState_)
	{
		currentState_->deinitialise();
		delete currentState_;
		currentState_ = NULL;
	}

	if (input_)
	{
		input_->deinitialise();
		delete input_;
		input_ = NULL;
	}

	dzArchiveDetach();

	// shut down the IwResManager resource manager
	IwResManagerTerminate();

	// Shut down the Iw2D drawing module
	Iw2DTerminate();
	
	// Shut down the IwGx drawing module
    IwGxTerminate();
	
}

/*
	Name		Game::run
	Syntax		Game::run()
	Brief		Runs the main game loop
*/
void Game::run()
{
	int time0 = getUpdateFrame();
	int time1 = 0;
	float deltaTime = 0;
	float tickTime = static_cast<float>(1000/UPS);

	// Loop forever, until the user or the OS performs some action to quit the app
	while (!s3eDeviceCheckQuitRequest()
          && !(s3eKeyboardGetState(s3eKeyEsc) & S3E_KEY_STATE_DOWN)
          && !(s3eKeyboardGetState(s3eKeyAbsBSK) & S3E_KEY_STATE_DOWN)
          )
	{
		
		// Update IwGx state time stamp
		IwGxTickUpdate();
		time1 = getUpdateFrame();
		deltaTime = 0;
		// Update the state logic every tick time, or until the FPS drops below 10
        int frames = time1 - time0;
        frames = MIN(MAX_UPDATES, frames);
        while (frames--)
        {
			// Time-critical updates, such as AI
			update();
			deltaTime += tickTime;
		}
		// Any updates which are not time-critical e.g. player input
		independentUpdate(deltaTime);
		time0 = time1;
		render();
        
        // Sleep for 0ms to allow the OS to process events etc.
        s3eDeviceYield(0);
	}
}

/*
	Name		Game::setCondition
	Syntax		Game::setCondition(Condition condition)
	Param		int condition - Condition to set 
	Brief		Sets the condition
*/
void Game::setCondition(Condition condition)
{
	condition_ = condition;
}

/*
	Name		Game::changeCondition
	Syntax		Game::changeCondition(Condition condition)
	Param		Condition condition - Condition parameter used to determine the next state
	Brief		Changes the condition and requests a change of states if different
*/
void Game::changeCondition(Condition condition)
{
	if (condition_ != condition)
	{
		condition_ = condition;
		changeState();
	}
}

/*
	Name		Game::update
	Syntax		Game::update()
	Brief		Updates the current state - time critial
*/
void Game::update()
{

	currentState_->update();
}

/*
	Name		Game::independentUpdate
	Syntax		Game::independentUpdate(float deltaTime)
	Param		float deltaTime - The time taken for the frame to run
	Brief		Updates the current state - not time-critical
*/
void Game::independentUpdate(float deltaTime)
{
	currentState_->independentUpdate(deltaTime);
}

/*
	Name		Game::render
	Syntax		Game::render()
	Brief		Renders the current state
*/
void Game::render()
{
	currentState_->render();
}

/*
	Name		Game::changeState
	Syntax		Game::changeState()
	Brief		Changes the current state
*/
void Game::changeState()
{
	if (currentState_)
	{
		State* state = currentState_->getNextState(condition_);

		if (state)
		{
			currentState_->deinitialise();
			delete currentState_;

			currentState_ = state;
			currentState_->initialise();
		}
	}
}

/*
	Name		Game::getUpdateFrame
	Syntax		Game::getUpdateFrame()
	Return		int - Returns the update frame as an integer
	Brief		Gets the update frame by dividing the current time in ms by the time interval for updates
*/
int Game::getUpdateFrame()
{
	int updateFrame = static_cast<int>(s3eTimerGetMs() / (1000/UPS));
    return updateFrame;
}