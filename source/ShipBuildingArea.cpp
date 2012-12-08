#include "ShipBuildingArea.hpp"
#include "Robot.hpp"
#include "Alien.hpp"
#include "Input.hpp"
#include "SoundEffect.hpp"
#include "LevelList.hpp"
#include "Video.hpp"

ShipBuildingArea::ShipBuildingArea(Alien* alien, Robot* robot, Input* input)
: Level					(alien, robot, input)
, SCROLL_SPEED			(0.15)
, deadZone_				(20.0)
, nextLevel_			(LEVEL_1)
, offsetFromEscapePod	(1250)
, ending_(0)
, secondPass_(false)
, endingPlayed_(false)
{
}

ShipBuildingArea::~ShipBuildingArea()
{
}

void ShipBuildingArea::initialise()
{
	ambientSound_ = new SoundEffect;
	ambientSound_->initialise("audio/Background Ambience/Ambience1.wav");
	ambientSound_->play(0);

	escapePodBuildingPuzzle_.initialise();

	sky_.initialise("scripts/ShipBuildingAreaSky.txt");
	distantBackground_.initialise("scripts/ShipBuildingAreaDistantBackground.txt");
	closeBackground_.initialise("scripts/ShipBuildingAreaCloseBackground.txt");
	midground_.initialise("scripts/ShipBuildingAreaMidground.txt");
	playerStage_.initialise("scripts/ShipBuildingAreaPlayerStage.txt");
	foreground_.initialise("scripts/ShipBuildingAreaForeground.txt");

	// Set alien x 
	alien()->setX(200);
	robot()->setCenterX(150);

	ending_ = new Video;
	ending_->initialise("cutscenes/5Ending.mp4");
}

void ShipBuildingArea::deinitialise()
{
	// Stop all sounds
	ambientSound_->stop();
	robot()->stopAllSounds();
	alien()->stopAllSounds();

	// Delete sound
	delete ambientSound_;
	ambientSound_ = 0;

	escapePodBuildingPuzzle_.deinitialise();

	sky_.deinitialise();
	distantBackground_.deinitialise();
	closeBackground_.deinitialise();
	midground_.deinitialise();
	playerStage_.deinitialise();
	foreground_.deinitialise();

	delete ending_;
}

void ShipBuildingArea::update()
{
	escapePodBuildingPuzzle_.update();
}

void ShipBuildingArea::independentUpdate(float deltaTime)
{
	setScreenWidth( IwGxGetScreenWidth() );
	setScreenHeight( IwGxGetScreenHeight() );

	int direction = 0;

	// Make the robot follow the alien
	if(!secondPass_)
	{
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
			escapePodBuildingPuzzle_.touchUpdate(touch->x_, touch->y_);

			if( !escapePodBuildingPuzzle_.movingABuildPiece() && !secondPass_)
			{
				// If player is trying to move right while the alien is at the edge of its moving area
				if( alien()->getX()	>= ( (int)((float)screenWidth() - (((float)screenWidth() / 100.0)*deadZone_))) &&
					touch->x_ > ( (int)((float)screenWidth() - (((float)screenWidth() / 100.0)*deadZone_)) ) )
				{
					if (playerStage_.isScrollingRight())
					{
						alien()->setWalkingState(true);
						robot()->setWalking();
						direction = -1;
					}
				}
				
				// If player is trying to move left while the alien is at the edge of its moving area
				else if( alien()->getX() <= ( (int)(((float)screenWidth() / 100.0)*deadZone_) ) &&
						 touch->x_ < ( (int)(((float)screenWidth() / 100.0)*deadZone_) ) )
				{
					if (playerStage_.isScrollingLeft())
					{
						alien()->setWalkingState(true);
						robot()->setWalking();
						direction = 1;
					}
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
		}	// end if (touch != NULL)


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
	if (input()->getTouchCount() == 0 )
	{

		escapePodBuildingPuzzle_.noTouchEventsActive();
		// Set the alien walking to false as there are no touch events
		alien()->setWalkingState(false);
	}

	sky_.update(direction*deltaTime*SCROLL_SPEED*0.2);
	distantBackground_.update(direction*deltaTime*SCROLL_SPEED*0.4);
	closeBackground_.update(direction*deltaTime*SCROLL_SPEED*0.6);
	midground_.update(direction*deltaTime*SCROLL_SPEED*0.8);
	playerStage_.update(direction*deltaTime*SCROLL_SPEED);
	foreground_.update(direction*deltaTime*SCROLL_SPEED*1.8);

	escapePodBuildingPuzzle_.movePuzzle(direction*deltaTime*SCROLL_SPEED);

	// If the alien	is beyond a set distance from the escape pod
	if( alien()->getX()	>= ( escapePodBuildingPuzzle_.getCenterX() + offsetFromEscapePod) )
	{
		// Move to the next level
		ambientSound_->stop();
		robot()->stopAllSounds();
		alien()->stopAllSounds();
		Level::playerExitingLevel();
		
	}
	
	if(escapePodBuildingPuzzle_.isComplete() && !endingPlayed_)
	{
		ambientSound_->stop();
		ending_->play();
		endingPlayed_ = true;
	}

	if(secondPass_)
	{
		alien()->setHoldingHose(true);
	}
}

void ShipBuildingArea::render()
{
	sky_.render();
	distantBackground_.render();
	closeBackground_.render();
	midground_.render();
	playerStage_.render();

	if(secondPass_)
	{
		escapePodBuildingPuzzle_.render();
	}
	
	if(!secondPass_)
	{
		// Render the robot
		robot()->render();
	}

	// Render alien
	alien()->render();

	foreground_.render();
}

int ShipBuildingArea::getNextLevel()
{
	return nextLevel_;
}

void ShipBuildingArea::playerEnteringFromLevel1()
{
	secondPass_ = true;

	/*
	// Set alien x 
	alien()->setX(700);
	robot()->setCenterX(800);
	*/
	float moveVal = 600.0;

	sky_.update(-moveVal*0.2);
	distantBackground_.update(-moveVal*0.4);
	closeBackground_.update(-moveVal*0.6);
	midground_.update(-moveVal*0.8);
	playerStage_.update(-moveVal);
	foreground_.update(-moveVal*1.8);

	escapePodBuildingPuzzle_.movePuzzle(-moveVal);
}
