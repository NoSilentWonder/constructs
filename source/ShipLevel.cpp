/*
	Copyright	Kangaroo Magic 2011
	Created 	Jonathan Jones
				Elinor Townsend
	
	Name		ShipLevel
	Brief		Definition of ShipLevel class methods
*/

// Declerations 
#include "ShipLevel.hpp"
#include "Alien.hpp"
#include "Robot.hpp"
#include "Input.hpp"
#include "BuildPiece.hpp"
#include "Material.hpp"
#include "Quad.hpp"
#include "RobotBuildingPuzzle.hpp"
#include "LevelList.hpp"
#include "SoundEffect.hpp"
#include "Video.hpp"

/*
	Name		ShipLevel::ShipLevel
	Syntax		ShipLevel::ShipLevel(Alien* alien, Robot* robot, Input* input)
	Params		Alien* alien - A pointer to the alien used for all levels
				Robot* robot - A pointer to the robot used for all levels
				Input* input - A pointer to the singleton input object used in all aspects of the game 
	Brief		Give initial values to member variables using an init list
	Details		Uses level constuctor to set alien and robot pointers as every level will use the alien and the robot
*/
ShipLevel::ShipLevel(Alien* alien, Robot* robot, Input* input)
: Level(alien, robot, input)			// Set the alien and robot pointers
, deadZone_(10)
, nextLevel_(SHIP_BUILDING_AREA)
, setRobotX(false)
, ambientSound_(0)
{
	nextLevelButton_ = new CircularButton("play.png", 700, 540, 0, 35, false);
}

/*
	Name		ShipLevel::~ShipLevel
	Syntax		ShipLevel::~ShipLevel()
	Brief		Deinitialise ship level
*/
ShipLevel::~ShipLevel()
{
	delete nextLevelButton_;
	nextLevelButton_ = 0;
}

/*
	Name		ShipLevel::initialise
	Syntax		ShipLevel::initialise()
	Brief		Initialise ship level elements
	Details		Initialise the robot parts vector with the head, torso and legs
*/
void ShipLevel::initialise()
{
	background_.initialise("environment/background/shipInteriorBackground.png", 1024, 768, 512, 384);

	// Initialise the robot building puzzle
	robotBuildingPuzzle_.initialise();

	/////////////////////////////////////
	// Position Alien and robot in scene
	/////////////////////////////////////

	// Set alien x 
	alien()->setX(330);

	// Set alien and robot y so that the base of each sprite is sprite is on the same level
	int baseY = 750;
	alien()->setY(baseY - alien()->getHeight()/2);
	robot()->setCentreY(baseY - robot()->getHeight()/2);

	ambientSound_ = new SoundEffect;
	ambientSound_->initialise("audio/Background Ambience/Ambience1.wav");
	ambientSound_->play(0);

	activates_ = new Video;
	activates_->initialise("cutscenes/2RobotActivates.mp4");
	activatesPlaying_ = false;
	activatesPlayed_ = false;
}

/*
	Name		ShipLevel::deinitialise
	Syntax		ShipLevel::deinitialise()
	Brief		Deinitialise elements in the ship level
	Details		Deinitialise any robot parts left over
*/
void ShipLevel::deinitialise()
{	
	robot()->stopAllSounds();
	robotBuildingPuzzle_.deinitialise();
	
	background_.deinitialise();


	delete ambientSound_;
	ambientSound_ = 0;

	delete activates_;
	activates_ = 0;
}

/*
	Name		ShipLevel::update
	Syntax		ShipLevel::update()
	Brief		
*/
void ShipLevel::update()
{
	setScreenWidth( IwGxGetScreenWidth() );
	setScreenHeight( IwGxGetScreenHeight() );
	
	// If the alien is in the last 10% of the screen then
	if( alien()->getX()	>= ( (int)((float)screenWidth() - (((float)screenWidth() / 100.0)*10)))	)
	{
		// Move to the next level
		ambientSound_->stop();
		robot()->stopAllSounds();
		alien()->stopAllSounds();
		Level::playerExitingLevel();
		Level::moveToNextLevel();
		
	}
}

/*
	Name		ShipLevel::independentUpdate
	Syntax		ShipLevel::independentUpdate(float deltaTime)
	Param		float deltaTime - The time it took to complete the last frame
	Brief		Update any items that rely on delta time
	Details		Update the input object
				Check to see if the player is trying to move any of the robot parts 
				Update the aliens position
				Update the robots position
*/
void ShipLevel::independentUpdate(float deltaTime)
{
	if (!activatesPlaying_)
	{
		setScreenWidth( IwGxGetScreenWidth() );
		setScreenHeight( IwGxGetScreenHeight() );

		robotBuildingPuzzle_.update();

		if (!robotBuildingPuzzle_.isComplete())
		{
			alien()->setHoldingHose(true);
		}
		else
		{
			alien()->setHoldingHose(false);
		}

		// Make the robot follow the alien
		if( robotBuildingPuzzle_.isComplete() && !activatesPlayed_)
		{
			ambientSound_->stop();
			activatesPlaying_ = true;
			activates_->play();
		}
		if( robotBuildingPuzzle_.isComplete())
		{
			// Check to see if the robot position has already been set as this should only happen once
			if(!setRobotX)
			{
				robot()->setCenterX(robotBuildingPuzzle_.getCenterX());
				robot()->talk(ROBOT_TALK_HAPPY);
				setRobotX = true;
			}

			// Make the robot follow the alien
			robot()->followAlien(alien()->getX(), alien()->getY());
		}

		// Update pointer system
		input()->update();

		// Check for screen touches
		if (input()->getTouchCount() != 0)
		{
			// Create a touch pointer and let it point to the the current touch command
			Touch* touch = input()->getTouch(0);

			// If a touch was set correctly
			if (touch != NULL)
			{
				// If the alien isn't walking 
				if( !alien()->getWalkingState() )
				{
					// Check to see if any of the robot pieces are being touched
					robotBuildingPuzzle_.touchUpdate(touch->x_, touch->y_);
				}

				// If a robot piece is not being moved and the robot building puzzle is complete
				if( !robotBuildingPuzzle_.movingABuildPiece() && activatesPlayed_)
				{
					if( alien()->getX()	<= ( (int)(((float)screenWidth() / 100.0)*deadZone_) )		&&
							 touch->x_			<  ( (int)(((float)screenWidth() / 100.0)*deadZone_) ) )
					{
						alien()->setWalkingState(true);
						//direction = 1;
					}
					else
					{
						// If the touch is to the right of the alien
						if (touch->x_ > alien()->getX() )
						{
							// Move the alien right 
							alien()->moveRight();
							alien()->setWalkingState(true);
						}

						// If the touch is the left of the alien
						if (touch->x_ < alien()->getX())
						{
							// Move the alien left
							alien()->moveLeft();
							alien()->setWalkingState(true);
						}
					}
				}
			}

			// if multi-touch is available then ...
			if (input()->isMultiTouch())
			{
				if (input()->getTouchCount() > 1)
				{
					touch = input()->getTouch(1);
					if (touch != NULL)
					{
						// Add update input effects here
					}
				}
			}
		}
		if (input()->getTouchCount() == 0)
		{
			// Stop touch events
			robotBuildingPuzzle_.noTouchEventsActive();

			// Set the alien walking to false as there are no touch events
			alien()->setWalkingState(false);
		}
	}
	else
	{
		if (!activates_->isPlaying())
		{
			activatesPlaying_ = false;
			activatesPlayed_ = true;
			ambientSound_->play(0);
		}
	}
	//robotBuildingPuzzle_.movePuzzle(direction*deltaTime*SCROLL_SPEED); 
}

/*
	Name		ShipLevel::render
	Syntax		ShipLevel::render()
	Brief		Draw the objects in the scene
	Details		Draw the alien
				Draw the robot building puzzle
				Draw the robot
*/
void ShipLevel::render()
{	
	// Render background
	background_.render();

	// Render robot building puzzle
	robotBuildingPuzzle_.render();

	// Render robot 
	if( robotBuildingPuzzle_.isComplete() )
	{
		robot()->render();
	}

	// Render alien
	alien()->render();

	//nextLevelButton_->render();
}

int ShipLevel::getNextLevel()
{
	return nextLevel_;
}