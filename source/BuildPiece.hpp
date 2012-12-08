/*
	Copyright	Kangaroo Magic 2011
	Created 	Jonathan Jones
	
	Name		Build Piece
	Brief		Represents a single piece of an object that has to be constructed within the game to create a new object
*/

#ifndef BUILD_PIECE_HPP
#define BUILD_PIECE_HPP

// Includes 
#include "s3eTypes.h"

// Forward declarations
class Sprite;

/*
	Name		Build Piece
	Brief		Represents a single piece of an object that has to be constructed within the game to create a new object
*/
class BuildPiece
{
public:
	BuildPiece(char* nameOfFile, int16 x, int16 y, int16 width, int16 height);	// Set the variables of the build piece
	virtual ~BuildPiece();												// Deinitialise all elements associated with build piece
	virtual void render();												// Render the image the build piece is using
	virtual void setCenterAt(int16 x, int16 y);							// Place the build pieces center at the x and y position passed into the function
	virtual bool collisionDetection(int16 touchX, int16 touchY);		// Checks to see if the touch is colliding with the build piece
	virtual bool beingMoved();											// Returns a bool which describes if the object is being moved
	virtual int16 getCentreX();											// Return the centre x coordinate of the build piece
	virtual int16 getCentreY();											// Return the centre y coordinate of the build piece
	void reverseDrawOrder();											// Reverses draw order of build piece silhouette
	void turnAlphaOn();													// Turn alpha on
	void setPlaced();
	void setUnplaced();
	bool getPlaced();
private:
	int16 getLeftSide();												// Returns the x coord of the left side
	int16 getRightSide();												// Returns the x coord of the right side
	int16 getTop();														// Returns the y coord of the top of the build piece
	int16 getBottom();													// Returns the y coord of the bottom of the build piece
private:
	int16 width_;														// The width of the build piece
	int16 height_;														// The height of the build piece
	int16 x_;															// The top left x coord of the build piece
	int16 y_;															// The top left y coord of the build piece
	int16 z_;															// The z coordinate of the build piece
	bool beingMoved_;													// A bool describing if the build piece is been moved
	Sprite* buildPiece_;												// The sprite of the build piece
	bool setProperly_;
};

#endif // BUILD_PIECE_HPP