/*
	Copyright	Kangaroo Magic 2011
	Created 	Jonathan Jones
	Modified	Karl Inglott

	Name		EscapePodBuildingPuzzle.cpp
	Brief		Description of methods for escape pod building puzzle 
*/

// Includes 
#include "EscapePodBuildingPuzzle.hpp"
#include "BuildPiece.hpp"
#include "BuildPieceSilhouette.hpp"

/*
	Name	EscapePodBuildingPuzzle::EscapePodBuildingPuzzle
	Syntax	EscapePodBuildingPuzzle::EscapePodBuildingPuzzle()
	Brief	Sets up variables and objects 
*/
EscapePodBuildingPuzzle::EscapePodBuildingPuzzle()
: START_X							(512)
, START_Y							(400)
, LEFT_THRUSTER_X					(START_X + 100)
, LEFT_THRUSTER_Y					(START_Y)
, LEFT_THRUSTER_WIDTH				(172)
, LEFT_THRUSTER_HEIGHT				(306)
, LEFT_THRUSTER_SILHOUETTE_X		(START_X + 400)
, LEFT_THRUSTER_SILHOUETTE_Y		(START_Y - 50)
, LEFT_THRUSTER_SILHOUETTE_WIDTH	(LEFT_THRUSTER_WIDTH)
, LEFT_THRUSTER_SILHOUETTE_HEIGHT	(LEFT_THRUSTER_HEIGHT)
, RIGHT_THRUSTER_X					(START_X + 100)
, RIGHT_THRUSTER_Y					(100)
, RIGHT_THRUSTER_WIDTH				(170)
, RIGHT_THRUSTER_HEIGHT				(307)
, RIGHT_THRUSTER_SILHOUETTE_X		(LEFT_THRUSTER_SILHOUETTE_X + 630)
, RIGHT_THRUSTER_SILHOUETTE_Y		(LEFT_THRUSTER_SILHOUETTE_Y)
, RIGHT_THRUSTER_SILHOUETTE_WIDTH	(RIGHT_THRUSTER_WIDTH)
, RIGHT_THRUSTER_SILHOUETTE_HEIGHT	(RIGHT_THRUSTER_HEIGHT)
, POD_BOTTOM_RIGHT_X				(START_X + 100)
, POD_BOTTOM_RIGHT_Y				(200)
, POD_BOTTOM_RIGHT_WIDTH			(446)
, POD_BOTTOM_RIGHT_HEIGHT			(426)
, POD_BOTTOM_RIGHT_SILHOUETTE_X		(LEFT_THRUSTER_SILHOUETTE_X + 380)
, POD_BOTTOM_RIGHT_SILHOUETTE_Y		(START_Y + 40)
, POD_BOTTOM_RIGHT_SILHOUETTE_WIDTH	(POD_BOTTOM_RIGHT_WIDTH)
, POD_BOTTOM_RIGHT_SILHOUETTE_HEIGHT(POD_BOTTOM_RIGHT_HEIGHT)
, POD_BOTTOM_LEFT_X					(START_X + 100)
, POD_BOTTOM_LEFT_Y					(300)
, POD_BOTTOM_LEFT_WIDTH				(290)
, POD_BOTTOM_LEFT_HEIGHT			(540)
, POD_BOTTOM_LEFT_SILHOUETTE_X		(LEFT_THRUSTER_SILHOUETTE_X + 172)
, POD_BOTTOM_LEFT_SILHOUETTE_Y		(START_Y - 60)
, POD_BOTTOM_LEFT_SILHOUETTE_WIDTH	(POD_BOTTOM_LEFT_WIDTH)
, POD_BOTTOM_LEFT_SILHOUETTE_HEIGHT	(POD_BOTTOM_LEFT_HEIGHT)
, POD_TOP_RIGHT_X					(START_X + 100)
, POD_TOP_RIGHT_Y					(400)
, POD_TOP_RIGHT_WIDTH				(288)
, POD_TOP_RIGHT_HEIGHT				(242)
, POD_TOP_RIGHT_SILHOUETTE_X		(LEFT_THRUSTER_SILHOUETTE_X + 430)
, POD_TOP_RIGHT_SILHOUETTE_Y		(START_Y - 260)
, POD_TOP_RIGHT_SILHOUETTE_WIDTH	(POD_TOP_RIGHT_WIDTH)
, POD_TOP_RIGHT_SILHOUETTE_HEIGHT	(POD_TOP_RIGHT_HEIGHT)
, POD_TOP_LEFT_X					(START_X + 100)
, POD_TOP_LEFT_Y					(500)
, POD_TOP_LEFT_WIDTH				(372)
, POD_TOP_LEFT_HEIGHT				(293)
, POD_TOP_LEFT_SILHOUETTE_X			(LEFT_THRUSTER_SILHOUETTE_X + 230)
, POD_TOP_LEFT_SILHOUETTE_Y			(START_Y - 260)
, POD_TOP_LEFT_SILHOUETTE_WIDTH		(POD_TOP_LEFT_WIDTH)
, POD_TOP_LEFT_SILHOUETTE_HEIGHT	(POD_TOP_LEFT_HEIGHT)
, POD_WINDOW_X						(START_X + 100)
, POD_WINDOW_Y						(600)
, POD_WINDOW_WIDTH					(424)
, POD_WINDOW_HEIGHT					(328)
, POD_WINDOW_SILHOUETTE_X			(LEFT_THRUSTER_SILHOUETTE_X + 300)
, POD_WINDOW_SILHOUETTE_Y			(START_Y - 130)
, POD_WINDOW_SILHOUETTE_WIDTH		(POD_WINDOW_WIDTH)
, POD_WINDOW_SILHOUETTE_HEIGHT		(POD_WINDOW_HEIGHT)
, movingABuildPiece_(false)
, buildPieceBeingMoved_(0)
{
}

/*
	Name	EscapePodBuildingPuzzle::~EscapePodBuildingPuzzle
	Syntax	EscapePodBuildingPuzzle::~EscapePodBuildingPuzzle()
	Brief	Destroys any left over varibles or ojects that need deletion before termination of the application
*/
EscapePodBuildingPuzzle::~EscapePodBuildingPuzzle()
{
}

/*
	Name	EscapePodBuildingPuzzle::initialise
	Syntax	EscapePodBuildingPuzzle::initialise()
	Brief	Sets up any variables that have not been set up in the constructor
*/
void EscapePodBuildingPuzzle::initialise()
{
	// Create the left thruster
	escapePodParts_.push_back( new BuildPiece("textures/EscapePodPieces/leftThruster.png", 
											LEFT_THRUSTER_X,
											LEFT_THRUSTER_Y,
											LEFT_THRUSTER_WIDTH,
											LEFT_THRUSTER_HEIGHT));

		escapePodPartsSilhouettes_.push_back( new BuildPieceSilhouette("textures/EscapePodSilhouettes/leftThrusterSilhouette.png", 
												LEFT_THRUSTER_SILHOUETTE_X,
												LEFT_THRUSTER_SILHOUETTE_Y,
												LEFT_THRUSTER_SILHOUETTE_WIDTH,
												LEFT_THRUSTER_SILHOUETTE_HEIGHT,
												escapePodParts_.back()
												));
	
		// Turn the alpha on for the silhouette
		escapePodPartsSilhouettes_.back()->turnAlphaOn();

	// Create the right thruster
	escapePodParts_.push_back( new BuildPiece("textures/EscapePodPieces/rightThruster.png", 
											RIGHT_THRUSTER_X,
											RIGHT_THRUSTER_Y,
											RIGHT_THRUSTER_WIDTH,
											RIGHT_THRUSTER_HEIGHT));

		escapePodPartsSilhouettes_.push_back( new BuildPieceSilhouette("textures/EscapePodSilhouettes/rightThrusterSilhouette.png", 
											RIGHT_THRUSTER_SILHOUETTE_X,
											RIGHT_THRUSTER_SILHOUETTE_Y,
											RIGHT_THRUSTER_SILHOUETTE_WIDTH,
											RIGHT_THRUSTER_SILHOUETTE_HEIGHT,
											escapePodParts_.back()
											));

		// Turn the alpha on for the silhouette
		escapePodPartsSilhouettes_.back()->turnAlphaOn();

	// Create the pod bottom right section
	escapePodParts_.push_back( new BuildPiece("textures/EscapePodPieces/podBottomRight.png", 
											POD_BOTTOM_RIGHT_X,
											POD_BOTTOM_RIGHT_Y,
											POD_BOTTOM_RIGHT_WIDTH,
											POD_BOTTOM_RIGHT_HEIGHT));

			escapePodPartsSilhouettes_.push_back( new BuildPieceSilhouette("textures/EscapePodSilhouettes/podBottomRightSilhouette.png", 
											POD_BOTTOM_RIGHT_SILHOUETTE_X,
											POD_BOTTOM_RIGHT_SILHOUETTE_Y,
											POD_BOTTOM_RIGHT_SILHOUETTE_WIDTH,
											POD_BOTTOM_RIGHT_SILHOUETTE_HEIGHT,
											escapePodParts_.back()
											));

		// Turn the alpha on for the silhouette
		escapePodPartsSilhouettes_.back()->turnAlphaOn();

	// Create the pod bottom left section
	escapePodParts_.push_back( new BuildPiece("textures/EscapePodPieces/podBottomLeft.png", 
											POD_BOTTOM_LEFT_X,
											POD_BOTTOM_LEFT_Y,
											POD_BOTTOM_LEFT_WIDTH,
											POD_BOTTOM_LEFT_HEIGHT));

				escapePodPartsSilhouettes_.push_back( new BuildPieceSilhouette("textures/EscapePodSilhouettes/podBottomLeftSilhouette.png", 
											POD_BOTTOM_LEFT_SILHOUETTE_X,
											POD_BOTTOM_LEFT_SILHOUETTE_Y,
											POD_BOTTOM_LEFT_SILHOUETTE_WIDTH,
											POD_BOTTOM_LEFT_SILHOUETTE_HEIGHT,
											escapePodParts_.back()
											));

		// Turn the alpha on for the silhouette
		escapePodPartsSilhouettes_.back()->turnAlphaOn();

	// Create the pod top right section
	escapePodParts_.push_back( new BuildPiece("textures/EscapePodPieces/podTopRight.png", 
											POD_TOP_RIGHT_X,
											POD_TOP_RIGHT_Y,
											POD_TOP_RIGHT_WIDTH,
											POD_TOP_RIGHT_HEIGHT));
	
				escapePodPartsSilhouettes_.push_back( new BuildPieceSilhouette("textures/EscapePodSilhouettes/podTopRightSilhouette.png", 
											POD_TOP_RIGHT_SILHOUETTE_X,
											POD_TOP_RIGHT_SILHOUETTE_Y,
											POD_TOP_RIGHT_SILHOUETTE_WIDTH,
											POD_TOP_RIGHT_SILHOUETTE_HEIGHT,
											escapePodParts_.back()
											));

		// Turn the alpha on for the silhouette
		escapePodPartsSilhouettes_.back()->turnAlphaOn();

	// Create the pod top left section
	escapePodParts_.push_back( new BuildPiece("textures/EscapePodPieces/podTopLeft.png", 
											POD_TOP_LEFT_X,
											POD_TOP_LEFT_Y,
											POD_TOP_LEFT_WIDTH,
											POD_TOP_LEFT_HEIGHT));
		
				escapePodPartsSilhouettes_.push_back( new BuildPieceSilhouette("textures/EscapePodSilhouettes/podTopLeftSilhouette.png", 
											POD_TOP_LEFT_SILHOUETTE_X,
											POD_TOP_LEFT_SILHOUETTE_Y,
											POD_TOP_LEFT_SILHOUETTE_WIDTH,
											POD_TOP_LEFT_SILHOUETTE_HEIGHT,
											escapePodParts_.back()
											));

		// Turn the alpha on for the silhouette
		escapePodPartsSilhouettes_.back()->turnAlphaOn();

	// Create the pod window
	escapePodParts_.push_back( new BuildPiece("textures/EscapePodPieces/podWindow.png", 
											POD_WINDOW_X,
											POD_WINDOW_Y,
											POD_WINDOW_WIDTH,
											POD_WINDOW_HEIGHT));

	// Turn alpha on for the window
	escapePodParts_.back()->turnAlphaOn();
			
				escapePodPartsSilhouettes_.push_back( new BuildPieceSilhouette("textures/EscapePodSilhouettes/podWindowSilhouette.png", 
											POD_WINDOW_SILHOUETTE_X,
											POD_WINDOW_SILHOUETTE_Y,
											POD_WINDOW_SILHOUETTE_WIDTH,
											POD_WINDOW_SILHOUETTE_HEIGHT,
											escapePodParts_.back()
											));

		// Turn the alpha on for the silhouette
		escapePodPartsSilhouettes_.back()->turnAlphaOn();

}

/*
	Name	EscapePodBuildingPuzzle::deinitialise
	Syntax	EscapePodBuildingPuzzle::deinitialise()
	Brief	Deletes any variables or objects that have been set up in EscapePodBuildingPuzzle::initialise
*/
void EscapePodBuildingPuzzle::deinitialise()
{
	// While escape pod parts is not empty 
	while(!escapePodParts_.empty())
	{
		// Delete the back object
		delete escapePodParts_.back();

		// Remove the last element
		escapePodParts_.pop_back();
	}

	// While escape pod parts silhouettes is not empty 
	while(!escapePodPartsSilhouettes_.empty())
	{
		// Delete the back object
		delete escapePodPartsSilhouettes_.back();

		// Remove the last element
		escapePodPartsSilhouettes_.pop_back();
	}
}

/*
	Name	EscapePodBuildingPuzzle::update
	Syntax	EscapePodBuildingPuzzle::update()
	Brief	Updates the objects in the escape pod building puzzle
*/
void EscapePodBuildingPuzzle::update()
{
	// For all the robot parts
	for(int i = 0; i < escapePodParts_.size(); i++)
	{
		// Check to see if they are placed near the silhouette
		if(escapePodParts_[i]->collisionDetection( escapePodPartsSilhouettes_[i]->getCentreX(), escapePodPartsSilhouettes_[i]->getCentreY() ) )
		{
			// If they are then place the centre of the image ontop of the silhouette
			escapePodParts_[i]->setCenterAt( escapePodPartsSilhouettes_[i]->getCentreX(), escapePodPartsSilhouettes_[i]->getCentreY() );

			// Set the associated bool to true
			escapePodPartsSilhouettes_[i]->setHasBuildPiece(true);

			escapePodParts_[i]->setPlaced();
		} // end if
		else
		{
			// Set the silhouette state to not holding a build piece
			escapePodPartsSilhouettes_[i]->setHasBuildPiece(false);

			escapePodParts_[i]->setUnplaced();
		} // end else
	} // end for

	// Check to see if all the robots parts are on the silhouettes 
	if( escapePodPartsSilhouettes_[0]->hasBuildPiece() &&
		escapePodPartsSilhouettes_[1]->hasBuildPiece() &&
		escapePodPartsSilhouettes_[2]->hasBuildPiece() &&
		escapePodPartsSilhouettes_[3]->hasBuildPiece() &&
		escapePodPartsSilhouettes_[4]->hasBuildPiece() &&
		escapePodPartsSilhouettes_[5]->hasBuildPiece() &&
		escapePodPartsSilhouettes_[6]->hasBuildPiece()
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
	Name	EscapePodBuildingPuzzle::render
	Syntax	EscapePodBuildingPuzzle::render()
	Brief	Renders the sprites to the screen 
*/
void EscapePodBuildingPuzzle::render()
{
	// If the puzzle is not complete
	if( !Puzzle::isComplete() )
	{
		// For all the escape pod pieces
		for(std::vector<BuildPieceSilhouette*>::iterator iter = escapePodPartsSilhouettes_.begin(); iter != escapePodPartsSilhouettes_.end(); iter++)
		{
			// Render robot piece
			(*iter)->render();
		}

		// For all the escape pod pieces
		for(std::vector<BuildPiece*>::iterator iter = escapePodParts_.begin(); iter != escapePodParts_.end(); iter++)
		{
			// Render robot piece
			(*iter)->render();
		}
	}
}

/*
	Name	EscapePodBuildingPuzzle::movePuzzle
	Syntax	EscapePodBuildingPuzzle::movePuzzle(int deltaX)
	Param	int deltaX - Offset to move the puzzle by in the x direction
	Brief	Moves the whole puzzle 
*/
void EscapePodBuildingPuzzle::movePuzzle(int deltaX)
{
	// For all the escape pod pieces
	for(std::vector<BuildPiece*>::iterator iter = escapePodParts_.begin(); iter != escapePodParts_.end(); iter++)
	{
		// Set the new position 
		(*iter)->setCenterAt( (*iter)->getCentreX() + deltaX, (*iter)->getCentreY() );
	}

	// For all the escape pod pieces
	for(std::vector<BuildPieceSilhouette*>::iterator iter = escapePodPartsSilhouettes_.begin(); iter != escapePodPartsSilhouettes_.end(); iter++)
	{
		// Set the new position 
		(*iter)->setCenterAt( (*iter)->getCentreX() + deltaX, (*iter)->getCentreY() );
	}
}

/*
	Name	EscapePodBuildingPuzzle::getCenterX
	Syntax	EscapePodBuildingPuzzle::getCenterX() 
	Return	int16 - center x coordinate of the puzzle
	Brief	Returns the centre x coordinate of the puzzle
*/
int16 EscapePodBuildingPuzzle::getCenterX() 
{
	return escapePodParts_[0]->getCentreX();
}

void EscapePodBuildingPuzzle::touchUpdate(int touchX, int touchY)
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
			for(std::vector<BuildPiece*>::iterator iter = escapePodParts_.begin(); iter != escapePodParts_.end(); iter++)
			{
				// Check to see if current touch is on a one of the robots parts
				if( (*iter)->collisionDetection(touchX, touchY)  && !(*iter)->getPlaced() )
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

bool EscapePodBuildingPuzzle::movingABuildPiece()
{
	return movingABuildPiece_;
}

void EscapePodBuildingPuzzle::noTouchEventsActive()
{
	// Set moving a build piece to false as there are no touch events
	movingABuildPiece_ = false;

	// Set the pointer which points to the current build piece being moved to zero as there are no touch events
	buildPieceBeingMoved_ = 0;
}