/*
	Copyright	Kangaroo Magic 2011
	Created 	Jonathan Jones
	Modified	Karl Inglott

	Name		RobotBuildingPuzzle.cpp
	Brief		Description of methods for escape pod building puzzle 
*/

// Includes 
#include "RobotBuildingPuzzle.hpp"
#include "BuildPiece.hpp"
#include "BuildPieceSilhouette.hpp"

/*
	Name	RobotBuildingPuzzle::RobotBuildingPuzzle
	Syntax	RobotBuildingPuzzle::RobotBuildingPuzzle()
	Brief	Sets up variables and objects 
*/
RobotBuildingPuzzle::RobotBuildingPuzzle()
:	movingABuildPiece_(false)
,	buildPieceBeingMoved_(0)
,	START_X							(600)
,	ROBOT_HEAD_WIDTH				(46)
,	ROBOT_HEAD_HEIGHT				(27)
,	ROBOT_HEAD_X					(START_X + 10)
,	ROBOT_HEAD_Y					(700)
,	ROBOT_HEAD_SILHOUETTE_WIDTH		(ROBOT_HEAD_WIDTH)
,	ROBOT_HEAD_SILHOUETTE_HEIGHT	(ROBOT_HEAD_HEIGHT)
,	ROBOT_HEAD_SILHOUETTE_X			(START_X + 150)
,	ROBOT_HEAD_SILHOUETTE_Y			(430)
,	ROBOT_TORSO_WIDTH				(145)
,	ROBOT_TORSO_HEIGHT				(173)
,	ROBOT_TORSO_X					(START_X - 100)
,	ROBOT_TORSO_Y					(600)
,	ROBOT_TORSO_SILHOUETTE_WIDTH	(ROBOT_TORSO_WIDTH)
,	ROBOT_TORSO_SILHOUETTE_HEIGHT	(ROBOT_TORSO_HEIGHT)
,	ROBOT_TORSO_SILHOUETTE_X		(ROBOT_HEAD_SILHOUETTE_X)
,	ROBOT_TORSO_SILHOUETTE_Y		( ( (int)((((float)ROBOT_HEAD_SILHOUETTE_HEIGHT) / 2) + (((float)ROBOT_TORSO_SILHOUETTE_HEIGHT) / 2) ) )  + ROBOT_HEAD_SILHOUETTE_Y - 25)
,	ROBOT_LEGS_WIDTH				(105)
,	ROBOT_LEGS_HEIGHT				(139)
,	ROBOT_LEGS_X					(START_X + 300)
,	ROBOT_LEGS_Y					(650)
,	ROBOT_LEGS_SILHOUETTE_WIDTH		(ROBOT_LEGS_WIDTH)
,	ROBOT_LEGS_SILHOUETTE_HEIGHT	(ROBOT_LEGS_HEIGHT)
,	ROBOT_LEGS_SILHOUETTE_X			(ROBOT_HEAD_SILHOUETTE_X)
,	ROBOT_LEGS_SILHOUETTE_Y			( ( (int)((((float)ROBOT_TORSO_SILHOUETTE_HEIGHT) / 2) + (((float)ROBOT_LEGS_SILHOUETTE_HEIGHT) / 2) ) )  + ROBOT_TORSO_SILHOUETTE_Y - 25)
,	ROBOT_POWER_CELL_WIDTH					(28)
,	ROBOT_POWER_CELL_HEIGHT					(24)
,	ROBOT_POWER_CELL_X						(START_X + 150)
,	ROBOT_POWER_CELL_Y						(600)
,	ROBOT_POWER_CELL_SILHOUETTE_WIDTH		(ROBOT_POWER_CELL_WIDTH)
,	ROBOT_POWER_CELL_SILHOUETTE_HEIGHT		(ROBOT_POWER_CELL_HEIGHT)
,	ROBOT_POWER_CELL_SILHOUETTE_X			(ROBOT_TORSO_SILHOUETTE_X)
,	ROBOT_POWER_CELL_SILHOUETTE_Y			(ROBOT_TORSO_SILHOUETTE_Y + 15)
,	ROBOT_LEFT_UPPER_ARM_WIDTH				(76)
,	ROBOT_LEFT_UPPER_ARM_HEIGHT				(88)
,	ROBOT_LEFT_UPPER_ARM_X					(START_X + 230)
,	ROBOT_LEFT_UPPER_ARM_Y					(670)
,	ROBOT_LEFT_UPPER_ARM_SILHOUETTE_WIDTH	(ROBOT_LEFT_UPPER_ARM_WIDTH)
,	ROBOT_LEFT_UPPER_ARM_SILHOUETTE_HEIGHT	(ROBOT_LEFT_UPPER_ARM_HEIGHT)
,	ROBOT_LEFT_UPPER_ARM_SILHOUETTE_X		( ROBOT_TORSO_SILHOUETTE_X - ( (int)((((float)ROBOT_TORSO_SILHOUETTE_WIDTH) / 2) + (((float)ROBOT_LEFT_UPPER_ARM_SILHOUETTE_WIDTH) / 2) ) ) + 25)
,	ROBOT_LEFT_UPPER_ARM_SILHOUETTE_Y		(ROBOT_TORSO_SILHOUETTE_Y)
,	ROBOT_RIGHT_UPPER_ARM_WIDTH				(ROBOT_LEFT_UPPER_ARM_WIDTH)
,	ROBOT_RIGHT_UPPER_ARM_HEIGHT			(ROBOT_LEFT_UPPER_ARM_HEIGHT)
,	ROBOT_RIGHT_UPPER_ARM_X					(START_X + 100)
,	ROBOT_RIGHT_UPPER_ARM_Y					(700)
,	ROBOT_RIGHT_UPPER_ARM_SILHOUETTE_WIDTH	(ROBOT_LEFT_UPPER_ARM_WIDTH)
,	ROBOT_RIGHT_UPPER_ARM_SILHOUETTE_HEIGHT	(ROBOT_LEFT_UPPER_ARM_HEIGHT)
,	ROBOT_RIGHT_UPPER_ARM_SILHOUETTE_X		( ( (int)((((float)ROBOT_TORSO_SILHOUETTE_WIDTH) / 2) + (((float)ROBOT_RIGHT_UPPER_ARM_SILHOUETTE_WIDTH) / 2) ) )  + ROBOT_TORSO_SILHOUETTE_X - 25)
,	ROBOT_RIGHT_UPPER_ARM_SILHOUETTE_Y		(ROBOT_LEFT_UPPER_ARM_SILHOUETTE_Y)
,	ROBOT_LEFT_LOWER_ARM_WIDTH				(87)
,	ROBOT_LEFT_LOWER_ARM_HEIGHT				(121)
,	ROBOT_LEFT_LOWER_ARM_X					(START_X + 180)
,	ROBOT_LEFT_LOWER_ARM_Y					(640)
,	ROBOT_LEFT_LOWER_ARM_SILHOUETTE_WIDTH	(ROBOT_LEFT_LOWER_ARM_WIDTH)
,	ROBOT_LEFT_LOWER_ARM_SILHOUETTE_HEIGHT	(ROBOT_LEFT_LOWER_ARM_HEIGHT)
,	ROBOT_LEFT_LOWER_ARM_SILHOUETTE_X		(ROBOT_LEFT_UPPER_ARM_SILHOUETTE_X-55)
,	ROBOT_LEFT_LOWER_ARM_SILHOUETTE_Y		( ( (int)((((float)ROBOT_LEFT_UPPER_ARM_SILHOUETTE_HEIGHT) / 2) + (((float)ROBOT_LEFT_LOWER_ARM_SILHOUETTE_HEIGHT) / 2) ) )  + ROBOT_LEFT_UPPER_ARM_SILHOUETTE_Y - 20)
,	ROBOT_RIGHT_LOWER_ARM_WIDTH				(ROBOT_LEFT_LOWER_ARM_WIDTH)
,	ROBOT_RIGHT_LOWER_ARM_HEIGHT			(ROBOT_LEFT_LOWER_ARM_HEIGHT)
,	ROBOT_RIGHT_LOWER_ARM_X					(START_X - 200)
,	ROBOT_RIGHT_LOWER_ARM_Y					(670)
,	ROBOT_RIGHT_LOWER_ARM_SILHOUETTE_WIDTH	(ROBOT_LEFT_LOWER_ARM_WIDTH)
,	ROBOT_RIGHT_LOWER_ARM_SILHOUETTE_HEIGHT	(ROBOT_LEFT_LOWER_ARM_HEIGHT)
,	ROBOT_RIGHT_LOWER_ARM_SILHOUETTE_X		(ROBOT_RIGHT_UPPER_ARM_SILHOUETTE_X+55)
,	ROBOT_RIGHT_LOWER_ARM_SILHOUETTE_Y		( ( (int)((((float)ROBOT_RIGHT_UPPER_ARM_SILHOUETTE_HEIGHT) / 2) + (((float)ROBOT_RIGHT_LOWER_ARM_SILHOUETTE_HEIGHT) / 2) ) )  + ROBOT_RIGHT_UPPER_ARM_SILHOUETTE_Y -20)
{
}

/*
	Name	RobotBuildingPuzzle::~RobotBuildingPuzzle
	Syntax	RobotBuildingPuzzle::~RobotBuildingPuzzle()
	Brief	Destroys any left over varibles or ojects that need deletion before termination of the application
*/
RobotBuildingPuzzle::~RobotBuildingPuzzle()
{
}

/*
	Name	RobotBuildingPuzzle::initialise
	Syntax	RobotBuildingPuzzle::initialise()
	Brief	Sets up any variables that have not been set up in the constructor
*/
void RobotBuildingPuzzle::initialise()
{

	// Create robot power cell
	robotParts_.push_back( new BuildPiece("textures/robotParts/robotPowercell.png", 
										  ROBOT_POWER_CELL_X, 
										  ROBOT_POWER_CELL_Y, 
										  ROBOT_POWER_CELL_WIDTH, 
										  ROBOT_POWER_CELL_HEIGHT));

	// Create robot power cell silhouette
	robotSilhouette_.push_back( new BuildPieceSilhouette(	"textures/robotPartsSilhouettes/PC.png", 
															ROBOT_POWER_CELL_SILHOUETTE_X, 
															ROBOT_POWER_CELL_SILHOUETTE_Y, 
															ROBOT_POWER_CELL_SILHOUETTE_WIDTH, 
															ROBOT_POWER_CELL_SILHOUETTE_HEIGHT, 
															robotParts_.back() ));
	// Turn the alpha on for the silhouette
	robotSilhouette_.back()->turnAlphaOn();
	// Create the head
	robotParts_.push_back(	new BuildPiece(	"textures/robotParts/robotHead.png", 
											ROBOT_HEAD_X, 
											ROBOT_HEAD_Y, 
											ROBOT_HEAD_WIDTH, 
											ROBOT_HEAD_HEIGHT));

	// Create the head silhouette
	robotSilhouette_.push_back( new BuildPieceSilhouette(	"textures/robotPartsSilhouettes/robot_head_holo.png", 
															ROBOT_HEAD_SILHOUETTE_X, 
															ROBOT_HEAD_SILHOUETTE_Y, 
															ROBOT_HEAD_SILHOUETTE_WIDTH, 
															ROBOT_HEAD_SILHOUETTE_HEIGHT, 
															robotParts_.back() ));
	
	// Turn the alpha on for the silhouette
	robotSilhouette_.back()->turnAlphaOn();

	// Create the torso
	robotParts_.push_back( new BuildPiece(	"textures/robotParts/robotBody.png", 
											ROBOT_TORSO_X, 
											ROBOT_TORSO_Y, 
											ROBOT_TORSO_WIDTH, 
											ROBOT_TORSO_HEIGHT));

	// Create the torso silhouette
	robotSilhouette_.push_back( new BuildPieceSilhouette(	"textures/RobotTorsoSilhouette.png",
															ROBOT_TORSO_SILHOUETTE_X, 
															ROBOT_TORSO_SILHOUETTE_Y, 
															ROBOT_TORSO_SILHOUETTE_WIDTH, 
															ROBOT_TORSO_SILHOUETTE_HEIGHT, 
															robotParts_.back() ));

	// Turn the alpha on for the silhouette
	robotSilhouette_.back()->turnAlphaOn();
	
	// Create the legs
	robotParts_.push_back( new BuildPiece("textures/robotParts/robotLegs.png", 
										  ROBOT_LEGS_X, 
										  ROBOT_LEGS_Y, 
										  ROBOT_LEGS_WIDTH, 
										  ROBOT_LEGS_HEIGHT));

	// Create the legs silhouette
	robotSilhouette_.push_back( new BuildPieceSilhouette(	"textures/RobotLegsSilhouette.png", 
															ROBOT_LEGS_SILHOUETTE_X, 
															ROBOT_LEGS_SILHOUETTE_Y, 
															ROBOT_LEGS_SILHOUETTE_WIDTH, 
															ROBOT_LEGS_SILHOUETTE_HEIGHT, 
															robotParts_.back() ));

	// Turn the alpha on for the silhouette
	robotSilhouette_.back()->turnAlphaOn();

	// Create robot left upper arm
	robotParts_.push_back( new BuildPiece("textures/robotParts/robotUpperarm.png", 
										  ROBOT_LEFT_UPPER_ARM_X, 
										  ROBOT_LEFT_UPPER_ARM_Y, 
										  ROBOT_LEFT_UPPER_ARM_WIDTH, 
										  ROBOT_LEFT_UPPER_ARM_HEIGHT));

	// Create robot left upper arm silhouette
	robotSilhouette_.push_back( new BuildPieceSilhouette(	"textures/robotPartsSilhouettes/ULA.png", 
															ROBOT_LEFT_UPPER_ARM_SILHOUETTE_X, 
															ROBOT_LEFT_UPPER_ARM_SILHOUETTE_Y, 
															ROBOT_LEFT_UPPER_ARM_SILHOUETTE_WIDTH, 
															ROBOT_LEFT_UPPER_ARM_SILHOUETTE_HEIGHT, 
															robotParts_.back() ));

	// Turn the alpha on for the silhouette
	robotSilhouette_.back()->turnAlphaOn();

	// Create robot lower left arm 
	robotParts_.push_back( new BuildPiece("textures/robotParts/robotLowerarm.png", 
										  ROBOT_LEFT_LOWER_ARM_X, 
										  ROBOT_LEFT_LOWER_ARM_Y, 
										  ROBOT_LEFT_LOWER_ARM_WIDTH, 
										  ROBOT_LEFT_LOWER_ARM_HEIGHT));

	// Create robot lower left arm silhouette
	robotSilhouette_.push_back( new BuildPieceSilhouette(	"textures/robotPartsSilhouettes/LLA.png", 
															ROBOT_LEFT_LOWER_ARM_SILHOUETTE_X, 
															ROBOT_LEFT_LOWER_ARM_SILHOUETTE_Y, 
															ROBOT_LEFT_LOWER_ARM_SILHOUETTE_WIDTH, 
															ROBOT_LEFT_LOWER_ARM_SILHOUETTE_HEIGHT, 
															robotParts_.back() ));

	// Turn the alpha on for the silhouette
	robotSilhouette_.back()->turnAlphaOn();

	// Create robot upper right arm 
	robotParts_.push_back( new BuildPiece("textures/robotParts/robotUpperarm.png", 
										  ROBOT_RIGHT_UPPER_ARM_X, 
										  ROBOT_RIGHT_UPPER_ARM_Y, 
										  ROBOT_RIGHT_UPPER_ARM_WIDTH, 
										  ROBOT_RIGHT_UPPER_ARM_HEIGHT));

	// Robot upper right arm uses same arm texture as the upper left arm but the draw order is reversed to make it appear to be the upper right arm
	robotParts_.back()->reverseDrawOrder();

	// Create robot upper right arm silhouette
	robotSilhouette_.push_back( new BuildPieceSilhouette(	"textures/robotPartsSilhouettes/URA.png", 
															ROBOT_RIGHT_UPPER_ARM_SILHOUETTE_X, 
															ROBOT_RIGHT_UPPER_ARM_SILHOUETTE_Y, 
															ROBOT_RIGHT_UPPER_ARM_SILHOUETTE_WIDTH, 
															ROBOT_RIGHT_UPPER_ARM_SILHOUETTE_HEIGHT, 
															robotParts_.back() ));


	robotSilhouette_.back()->turnAlphaOn();
	// Create robot lower right arm 
	robotParts_.push_back( new BuildPiece("textures/robotParts/robotLowerarm.png", 
										  ROBOT_RIGHT_LOWER_ARM_X, 
										  ROBOT_RIGHT_LOWER_ARM_Y, 
										  ROBOT_RIGHT_LOWER_ARM_WIDTH, 
										  ROBOT_RIGHT_LOWER_ARM_HEIGHT));

	// Robot lower right arm uses same arm texture as the lower left arm but the draw order is reversed to make it appear to be the lower right arm
	robotParts_.back()->reverseDrawOrder();

	// Create robot lower right arm silhouette
	robotSilhouette_.push_back( new BuildPieceSilhouette(	"textures/robotPartsSilhouettes/LRA.png", 
															ROBOT_RIGHT_LOWER_ARM_SILHOUETTE_X, 
															ROBOT_RIGHT_LOWER_ARM_SILHOUETTE_Y, 
															ROBOT_RIGHT_LOWER_ARM_SILHOUETTE_WIDTH, 
															ROBOT_RIGHT_LOWER_ARM_SILHOUETTE_HEIGHT, 
															robotParts_.back() ));

	// Reverse the draw order as the lower right arm is using a mirror image of the lower left arm
	robotSilhouette_.back()->turnAlphaOn();
}

/*
	Name	RobotBuildingPuzzle::deinitialise
	Syntax	RobotBuildingPuzzle::deinitialise()
	Brief	Deletes any variables or objects that have been set up in RobotBuildingPuzzle::initialise method
*/
void RobotBuildingPuzzle::deinitialise()
{
	// While parts is not empty 
	while(!robotParts_.empty())
	{
		// Delete the back part  
		delete robotParts_.back();

		// Remove the last element
		robotParts_.pop_back();
	}

	// While Silhouette is not empty 
	while(!robotSilhouette_.empty())
	{
		// Delete the back part  
		delete robotSilhouette_.back();

		// Remove the last element
		robotSilhouette_.pop_back();
	}
}

/*
	Name	RobotBuildingPuzzle::update
	Syntax	RobotBuildingPuzzle::update()
	Brief	Updates the objects in the robot building puzzle
*/
void RobotBuildingPuzzle::update()
{
	// For all the robot parts
	for(int i = 0; i < robotParts_.size(); i++)
	{
		// Check to see if they are placed near the silhouette
		if(robotParts_[i]->collisionDetection( robotSilhouette_[i]->getCentreX(), robotSilhouette_[i]->getCentreY() ) )
		{
			// If they are then place the centre of the image ontop of the silhouette
			robotParts_[i]->setCenterAt( robotSilhouette_[i]->getCentreX(), robotSilhouette_[i]->getCentreY() );

			// Set the associated bool to true
			robotSilhouette_[i]->setHasBuildPiece(true);

			robotParts_[i]->setPlaced();
		} // end if
		else
		{
			// Set the silhouette state to not holding a build piece
			robotSilhouette_[i]->setHasBuildPiece(false);

			robotParts_[i]->setUnplaced();
		} // end else
	} // end for

	// Check to see if all the robots parts are on the silhouettes 
	if( robotSilhouette_[0]->hasBuildPiece() &&
		robotSilhouette_[1]->hasBuildPiece() &&
		robotSilhouette_[2]->hasBuildPiece() &&
		robotSilhouette_[3]->hasBuildPiece() &&
		robotSilhouette_[4]->hasBuildPiece() &&
		robotSilhouette_[5]->hasBuildPiece() &&
		robotSilhouette_[6]->hasBuildPiece() &&
		robotSilhouette_[7]->hasBuildPiece()
		)
	{
		// Set the puzzle state to complete
		Puzzle::setComplete();

		// Puzzle is complete so player cannot be moving a build piece
		movingABuildPiece_ = false;

		// Set the build piece being moved pointer to zero as the puzzle is now complete and the player cannot be moving one of the robot build pieces
		buildPieceBeingMoved_ = 0;
	}	// end if
}

/*
	Name	RobotBuildingPuzzle::update
	Syntax	RobotBuildingPuzzle::update()
	Brief	Updates the objects in the robot building puzzle
*/
void RobotBuildingPuzzle::touchUpdate(int touchX, int touchY) // Change to const int 
{
	// If the robot is not constructed
	if( !Puzzle::isComplete() )
	{
		// Check to see if we are currently moving a build piece
		if(movingABuildPiece_)
		{
			// Move the build piece to the touch 
			buildPieceBeingMoved_->setCenterAt(touchX, touchY);
		} // end if 
		else	// If we are not currently moving a build piece
		{
			// For all the robot building pieces 
			for(std::vector<BuildPiece*>::iterator iter = robotParts_.begin(); iter != robotParts_.end(); iter++)
			{
				// Check to see if current touch is on a one of the robots parts
				if( (*iter)->collisionDetection(touchX, touchY) && !(*iter)->getPlaced())
				{
					// Center the robot part on the touch position
					(*iter)->setCenterAt(touchX, touchY);

					// Set a pointer to the object being moved 
					buildPieceBeingMoved_ = (*iter);

					// Moving a building piece is currently true so set it
					movingABuildPiece_ = true;
					break;
				}	// end if
				else
				{
					// Set moving piece to false as none of the robot pieces are being moved
					movingABuildPiece_ = false;
				}	// end else
			}	// end for 
		}	// end else
	}	// end if
}

/*
	Name	RobotBuildingPuzzle::render
	Syntax	RobotBuildingPuzzle::render()
	Brief	Renders all the objects in the puzzle
*/
void RobotBuildingPuzzle::render()
{
	// If the puzzle is not complete
	if( !Puzzle::isComplete() )
	{
		// For all the robot Silhouettes
		for(std::vector<BuildPieceSilhouette*>::iterator iter = robotSilhouette_.begin(); iter != robotSilhouette_.end(); iter++)
		{
			// Render robot Silhouette
			(*iter)->render();
		}

		// For all the robot pieces
		std::vector<BuildPiece*>::reverse_iterator iterSil;
		for(iterSil = robotParts_.rbegin(); iterSil != robotParts_.rend(); iterSil++)
		{
			// Render robot piece
			(*iterSil)->render();
		}	
	}
}

/*
	Name	RobotBuildingPuzzle::movingABuildPiece
	Syntax	RobotBuildingPuzzle::movingABuildPiece()
	Return	true	- if a robot build piece is being moved 
			false	- if none of the robot build pieces are being moved
	Brief	Returns if one of the robot build pieces is being moved
*/
bool RobotBuildingPuzzle::movingABuildPiece()
{
	return movingABuildPiece_;
}

/*
	Name	RobotBuildingPuzzle::noTouchEventsActive
	Syntax	RobotBuildingPuzzle::noTouchEventsActive()
	Brief	Resets variables to a default state if there are no touch events active
*/
void RobotBuildingPuzzle::noTouchEventsActive()
{
	// Set moving a build piece to false as there are no touch events
	movingABuildPiece_ = false;

	// Set the pointer which points to the current build piece being moved to zero as there are no touch events
	buildPieceBeingMoved_ = 0;
}

/*
	Name	RobotBuildingPuzzle::movePuzzle
	Syntax	RobotBuildingPuzzle::movePuzzle(int deltaX)
	Params	int deltaX	- Offset to move the puzzle by in the x direction
	Brief	Changes the position of the puzzle by deltaX 
*/
void RobotBuildingPuzzle::movePuzzle(int deltaX)
{
	// For all the build piece silhouettes 
	for(std::vector<BuildPieceSilhouette*>::iterator iter = robotSilhouette_.begin(); iter != robotSilhouette_.end(); iter++)
	{
		// Set the new position 
		(*iter)->setCenterAt( (*iter)->getCentreX() + deltaX, (*iter)->getCentreY() );
	}

	// For all the build pieces 
	for(std::vector<BuildPiece*>::iterator iter = robotParts_.begin(); iter != robotParts_.end(); iter++)
	{
		// Set the new position
		(*iter)->setCenterAt( (*iter)->getCentreX() + deltaX, (*iter)->getCentreY() );
	}
}

/*
	Name	RobotBuildingPuzzle::getCenterX
	Syntax	RobotBuildingPuzzle::getCenterX()
	Return	int16	- The centre x coordinate of the robot body which is the centre x of the puzzle
	Brief	Returns the centre x coordinate of the robot body
*/
int16 RobotBuildingPuzzle::getCenterX()
{
	return robotSilhouette_[1]->getCentreX();
}