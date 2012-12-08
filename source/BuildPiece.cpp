// BuildPiece.cpp

#include "BuildPiece.hpp"
#include "Sprite.hpp"

/*
	Name	BuildPiece::BuildPiece
	Syntax	BuildPiece::BuildPiece(const char* nameOfFile, int16 x, int16 y, int16 width, int16 height)
	Params	std::string name	- The location of the image
			int16 x				- The x position to place the build piece
			int16 y				- The y position to place the build piece
			int16 width			- The width to set the build piece to 
			int16 height		- The height to set the build piece to 
	Brief	Set the variables of the build piece
*/
BuildPiece::BuildPiece(char* nameOfFile, int16 x, int16 y, int16 width, int16 height)
: width_(width)			// Set the width
, height_(height)		// Set the height
, x_(x)					// Set the x
, y_(y)					// Set the y
, z_(0)					// Set the z
, beingMoved_(false)	// Set being moved to false
, buildPiece_(0)		// Set sprite pointer initally to zero
, setProperly_(false)
{
	/////////////////////
	// Setup the sprite
	/////////////////////
	
	// Create new sprite
	buildPiece_ = new Sprite;
	buildPiece_->initialise(nameOfFile, width, height, x, y);
}

/*
	Name	BuildPiece::~BuildPiece
	Syntax	BuildPiece::~BuildPiece()
	Brief	Deinitialise all elements associated with build piece
	Details Releases the image and sets the pointer to 0
*/
BuildPiece::~BuildPiece()
{
	///////////////////////
	// Delete the sprite
	///////////////////////

	// Deinitialise the sprite
	buildPiece_->deinitialise();

	// Delete the sprite object
	delete buildPiece_;

	// Set the pointer to zero to stop accidental access to now deleted sprite
	buildPiece_ = 0;

	//////////////////////////
	// End deletion of sprite
	//////////////////////////
}

/*
	Name	BuildPiece::render
	Syntax	BuildPiece::render()
	Brief	Render the image the build piece is using
*/
void BuildPiece::render()
{
	// Render the image
	buildPiece_->render();
}

/*
	Name	BuildPiece::setCenterAt
	Syntax	BuildPiece::setCenterAt(int16 x, int16 y)
	Params	int16 x - The x coord where the build pieces center should be placed
			int16 y - The y coord where the build pieces center should be placed
	Brief	Place the build pieces center at the x and y position passed into the function
*/
void BuildPiece::setCenterAt(int16 x, int16 y)
{
	// Set x and y position of the build piece to the touch x and y
	x_ = x;
	y_ = y;

	// Change the position
	buildPiece_->moveTo(x_, y_);
}

/*
	Name	BuildPiece::collisionDetection
	Syntax	BuildPiece::collisionDetection(int16 touchX, int16 touchY)
	Params	int16 touchX - The x coord of the touch
			int16 touchY - The y coord of the touch
	Brief	Checks to see if the touch is colliding with the build piece
	Returns true	- If the touch is colliding 
			false	- If the touch is not colliding 
*/
bool BuildPiece::collisionDetection(int16 touchX, int16 touchY)
{
	// Check to see if the touch is colliding with the build piece
	if( touchX > getLeftSide()  &&		// If touch is on the right of the left side of the build piece 
		touchX < getRightSide() &&		// If touch is on the left of the right side of the build piece 
		touchY > getTop()		 &&		// If the touch is below the top of the build piece
		touchY < getBottom()			// If the touch is above the bottom of the build piece 
		)
	{
		// It is colliding so
		// Set being moved to true
		beingMoved_ = true;

		// return being collided with
		return true;
	}
	else
	{
		// Else being moved is false
		beingMoved_ = false;
		
		// Return not being collided with
		return false;
	}
}

/*
	Name	BuildPiece::beingMoved
	Syntax	BuildPiece::beingMoved()
	Brief	Returns a bool which describes if the object is being moved
	Returns	True	- if being moved
			False	- if not being moved
*/
bool BuildPiece::beingMoved()
{
	// Return the being moved bool 
	return beingMoved_;
}

/*
	Name	BuildPiece::getCentreX
	Syntax	BuildPiece::getCentreX()
	Brief	Returns the centre X coordinate of the build piece 
	Returns	The centre x coord of the build piece
*/
int16 BuildPiece::getCentreX()
{
	return x_;
}

/*
	Name	BuildPiece::getCentreY
	Syntax	BuildPiece::getCentreY()
	Brief	Returns the centre y coordinate of the build piece
	Returns	The centre y coord of the build piece
*/
int16 BuildPiece::getCentreY()
{
	return y_;
}

/*
	Name	BuildPiece::getLeftSide
	Syntax	BuildPiece::getLeftSide()
	Brief	Returns the x coord of the left side
	Details Private member function
*/
inline int16 BuildPiece::getLeftSide()
{
	// Return the x coord of the left side
	return (x_ - (width_/2));
}

/*
	Name	BuildPiece::getRightSide
	Syntax	BuildPiece::getRightSide()
	Brief	Returns the x coord of the right side
	Details Private member function
*/
inline int16 BuildPiece::getRightSide()
{
	// Return the x coord of the right side
	return (x_ + (width_/2));
}

/*
	Name	BuildPiece::getTop
	Syntax	BuildPiece::getTop()
	Brief	Returns the y coord of the top of the build piece
	Details Private member function
*/
inline int16 BuildPiece::getTop()
{
	// Return the y coord of the top of the build piece
	return (y_ - (height_/2));
}

/*
	Name	BuildPiece::getBottom
	Syntax	BuildPiece::getBottom()
	Brief	Returns the y coord of the bottom of the build piece
	Details Private member function
*/
inline int16 BuildPiece::getBottom()
{
	// Return the y coord of the bottom of the build piece
	return (y_ + (height_/2));
}

/*
	Name		BuildPieceSilhouette::reverseDrawOrder
	Syntax		BuildPieceSilhouette::reverseDrawOrder()
	Brief		Reverses draw order of build piece silhouette
*/
void BuildPiece::reverseDrawOrder()
{
	buildPiece_->reverse();
}

/*
	Name	BuildPiece::turnAlphaOn
	Syntax	BuildPiece::turnAlphaOn()
	Brief	Turn alpha on the sprite on
*/
void BuildPiece::turnAlphaOn()
{
	buildPiece_->turnAlphaOn();
}

void BuildPiece::setPlaced()
{
	setProperly_ = true;
}
	
bool BuildPiece::getPlaced()
{
	return setProperly_;
}

void BuildPiece::setUnplaced()
{
	setProperly_ = false;
}