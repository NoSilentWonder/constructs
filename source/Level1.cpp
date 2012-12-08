/*
	Copyright	Kangaroo Magic 2011
	Created 	Jonathan Jones
	
	Name		Level1.cpp
	Brief		Contains definitons of functions for level 1
*/

#include "Level1.hpp"
#include "Alien.hpp"
#include "Robot.hpp"
#include "Input.hpp"
#include "LevelList.hpp"
#include "Video.hpp"

Level1::Level1(Alien* alien, Robot* robot, Input* input)
: Level			(alien, robot, input)
, SCROLL_SPEED	(0.15)
, rubblePuzzle_	()
, deadZone_		(20.0)
, nextLevel_	(SHIP_BUILDING_AREA)
, gift_(0), prebuild_(0), ending_(0), 
  giftPlayed_(false), prebuildPlayed_(false), endingPlayed_(false)
, playGift_(false)
{
}

Level1::~Level1()
{
}

void Level1::initialise()
{
	// Initialise robot puzzle
	rubblePuzzle_.initialise();

	sky_.initialise("scripts/DayOneSky.txt");
	distantBackground_.initialise("scripts/DayOneDistantBackground.txt");
	closeBackground_.initialise("scripts/DayOneCloseBackground.txt");
	midground_.initialise("scripts/DayOneMidground.txt");
	playerStage_.initialise("scripts/DayOnePlayerStage.txt");
	foreground_.initialise("scripts/DayOneForeground.txt");

	gift_ = new Video;
	gift_->initialise("cutscenes/3RobotGift.mp4");

	prebuild_ = new Video;
	prebuild_->initialise("cutscenes/4PreBuild.mp4");

	ending_ = new Video;
	ending_->initialise("cutscenes/5Ending.mp4");

	// Set alien x 
	alien()->setX(300);
	robot()->setCenterX(150);
}

void Level1::deinitialise()
{
	// Stop all sounds
	robot()->stopAllSounds();
	alien()->stopAllSounds();

	// Deintialise robot puzzle
	rubblePuzzle_.deinitialise();

	sky_.deinitialise();
	distantBackground_.deinitialise();
	closeBackground_.deinitialise();
	midground_.deinitialise();
	playerStage_.deinitialise();
	foreground_.deinitialise();

	delete gift_;
	delete prebuild_;
	delete ending_;
}

void Level1::update()
{
	rubblePuzzle_.update();
}

void Level1::independentUpdate(float deltaTime)
{	
	if (giftPlayed_)
	{
		if (!prebuildPlayed_)
		{
			if (!gift_->isPlaying())
			{
				robot()->stopAllSounds();
				alien()->stopAllSounds();
				prebuild_->play();
				prebuildPlayed_ = true;
				return;
			}
			return;
		}

		if (!prebuild_->isPlaying())
		{
			Level::playerExitingLevel();
			return;
		}
		/*
		if (!endingPlayed_)
		{
			if (!prebuild_->isPlaying())
			{
				ending_->play();
				endingPlayed_ = true;
				return;
			}
			return;
		}
		*/
	}

	setScreenWidth( IwGxGetScreenWidth() );
	setScreenHeight( IwGxGetScreenHeight() );
	
	int direction = 0;

	if(!playGift_)
	{
		// Make the robot follow the alien
		robot()->followAlien(alien()->getX(), alien()->getY());
	

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
				// Check to see if any of the robot pieces are being touched
				if(alien()->getWalkingState() == false)
				{
					rubblePuzzle_.touchUpdate(touch);
				}

				if(!rubblePuzzle_.getPieceBeingTouched())
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

						//bool check = false;
						// If the alien	is beyond a set distance from the escape pod
						if ( (alien()->getX() < 205) && playerStage_.tileIsBeingRendered(0) )
						{
							playGift_ = true;
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
				} // end if(rubble
			} // end if (touch != NULL)

			rubblePuzzle_.setSecondTouch(touch);

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
			rubblePuzzle_.touchCountZero();

			// Set the alien walking to false as there are no touch events
			alien()->setWalkingState(false);
		}

		sky_.update(direction*deltaTime*SCROLL_SPEED*0.2);
		distantBackground_.update(direction*deltaTime*SCROLL_SPEED*0.4);
		closeBackground_.update(direction*deltaTime*SCROLL_SPEED*0.6);
		midground_.update(direction*deltaTime*SCROLL_SPEED*0.8);
		playerStage_.update(direction*deltaTime*SCROLL_SPEED);
		foreground_.update(direction*deltaTime*SCROLL_SPEED*1.8);

		rubblePuzzle_.movePuzzle(direction*deltaTime*SCROLL_SPEED);

		if (playerStage_.tileIsBeingRendered(12) && !giftPlayed_)
		{
			robot()->stopAllSounds();
			alien()->stopAllSounds();
			gift_->play();
			giftPlayed_ = true;
		}
	}

	if(playGift_ && !giftPlayed_)
	{
		robot()->stopAllSounds();
		alien()->stopAllSounds();
		gift_->play();
		giftPlayed_ = true;
	}
}

void Level1::render()
{

	sky_.render();
	distantBackground_.render();
	closeBackground_.render();
	midground_.render();
	playerStage_.render();

	rubblePuzzle_.render();
		
	// Render the robot
	robot()->render();
	
	if(!playGift_)
	{
		// Render alien
		alien()->render();
	}

	foreground_.render();

	if(playGift_)
	{
		robot()->stopAllSounds();
		alien()->stopAllSounds();
	}
}

int Level1::getNextLevel()
{
	return nextLevel_;
}