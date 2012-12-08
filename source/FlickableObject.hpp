/*
	Copyright	Kangaroo Magic 2011
	Created		Jonathan Jones

	Name		Flickable object header
	Brief		Represents a game object which can be flicked in game  
*/

#ifndef FLICKABLE_OBJECT_HPP
#define FLICKABLE_OBJECT_HPP

// Includes 
#include "s3eTypes.h"

// Forward declerations
class Sprite;

/*
	Name		Flickable object
	Brief		Represents a game object which can be flicked in game
*/
class FlickableObject
{
public:
	FlickableObject(char* nameOfFile, int16 x, int16 y, int16 width, int16 height);
	~FlickableObject();
	void render() const;												// Renders the flickable object
	void setCenterAt(int16 x, int16 y);									// Positions the centre of the flickable object at x and y coordinate passed to the function
	bool collisionDetection(int16 touchX, int16 touchY);				// Returns true if a touch has collided with the object, otherwise false
	bool beenTouched() const;											// Returns true if object has been touched, false otherwise
	int16 getCentreX() const;											// Returns the centre x coordinate of the object
	int16 getCentreY() const;											// Returns the centre y coordinate of the object
	void update();											
	void setVelocity(int startX, int startY, int endX, int endY);		// Set the velocity of the flickable object
	void setTouched();													// Set the flickable object state to being touched, which is described by a boolean.
	bool getVelocitySet();												// Returns true if the velocity has been set, false otherwise
private:
	int16 getLeftSide();												// Returns the x coord of the left side
	int16 getRightSide();												// Returns the x coord of the right side
	int16 getTop();														// Returns the y coord of the top of the flickable object 
	int16 getBottom();													// Returns the y coord of the bottom of the flickable object 
private:
	int16 width_;														// The width of the flickable object 
	int16 height_;														// The height of the flickable object 
	int16 x_;															// The top left x coord of the flickable object 
	int16 y_;															// The top left y coord of the flickable object 
	int16 z_;															// The z coordinate of the flickable object
	bool beenTouched_;													// A bool describing if the flickable object has been flicked
	Sprite* sprite_;													// The flickable object sprite
	int16 velocity_[2];													// velocity_[0] = i component , velocity_[1] = j component
	bool velocitySet_;													// Describes if the velocity of the flickable object has been set or not
};

#endif	// FLICKABLE_OBJECT_HPP