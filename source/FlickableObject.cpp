/*
	Copyright	Kangaroo Magic 2011
	Created		Jonathan Jones

	Name		Flickable object source
	Brief		Represents a game object which can be flicked in game  
*/

// Includes 
#include "FlickableObject.hpp"
#include "Sprite.hpp"

/*
	Name		FlickableObject::FlickableObject
	Syntax		FlickableObject::FlickableObject(CIwResGroup* group, const char* nameOfFile, int16 x, int16 y, int16 width, int16 height)
	Params		CIwResGroup* group		- A pointer to the resource group which contains the texture information
				const char* nameOfFile	- The location of the image
				int16 x					- The x position to place the build piece
				int16 y					- The y position to place the build piece
				int16 width				- The width to set the build piece to 
				int16 height			- The height to set the build piece to 	
	Brief		Set the variables of the flickable object
*/

FlickableObject::FlickableObject(char* nameOfFile, int16 x, int16 y, int16 width, int16 height): width_(width)			// Set width
, height_(height)		// Set height
, x_(x)					// Set x
, y_(y)					// Set y
, z_(0)					// Set z
, beenTouched_(false)	// Set the flickable object to not been touched 
, sprite_(0)			// Set the sprite pointer to zero
, velocitySet_(false)	// Set the boolean which describes if the velocity of the flickable object has been set to false
{
	// Initialise velcocity components to 0

	velocity_[0] = 0;
	velocity_[1] = 0;
	////////////////////////////
	// Create sprite
	////////////////////////////
	
	// Create new sprite object
	sprite_ = new Sprite;
	sprite_->initialise(nameOfFile, width, height, x, y);
	//////////////////////////////
	// End creation of sprite
	//////////////////////////////
}

/*
	Name		FlickableObject::~FlickableObject
	Syntax		FlickableObject::~FlickableObject()
	Brief		Delete anything contained within the object which is not implicitly deleted
*/
FlickableObject::~FlickableObject()
{
	////////////////////////////
	// Delete sprite object 
	////////////////////////////

	// Deinitialise sprite
	sprite_->deinitialise();

	// Delete sprite object
	delete sprite_;

	// Set sprite pointer to zero
	sprite_ = 0;

	/////////////////////////////
	// End sprite deletion
	/////////////////////////////
}

/*
	Name		FlickableObject::render
	Syntax		FlickableObject::render() 
	Brief		Render the sprite contained within flickable object
*/
void FlickableObject::render() const
{
	// Render the sprite
	sprite_->render();
}

/*
	Name		FlickableObject::setCenterAt
	Syntax		FlickableObject::setCenterAt(int16 x, int16 y)
	Params		int16 x - The x coordinate to place the flickable object at
				int16 y - The y coordinate to place the flickable object at
	Brief		Sets the centre position of the flickable object at the passed x and y coordinates
*/
void FlickableObject::setCenterAt(int16 x, int16 y)
{
	x_ = x;		// Set flickable object x position to new x position 
	y_ = y;		// Set flickable object y position to new y position

	// Move sprite to new position
	sprite_->moveTo(x_, y_);
}

/*
	Name		FlickableObject::collisionDetection
	Syntax		FlickableObject::collisionDetection(int16 touchX, int16 touchY)
	Params		int16 x - The x coordinate to place the flickable object at
				int16 y - The y coordinate to place the flickable object at	
	Brief		Checks to see the x and y coordinates passed in to the function exist within the flickable objects bounding box (bounding box = sprite dimension and position)
*/
bool FlickableObject::collisionDetection(int16 touchX, int16 touchY)
{
	if( touchX > getLeftSide()  &&		// If touch is on the right of the left side of the build piece 
		touchX < getRightSide() &&		// If touch is on the left of the right side of the build piece 
		touchY > getTop()		 &&		// If the touch is below the top of the build piece
		touchY < getBottom()			// If the touch is above the bottom of the build piece 
		)
	{
		// return being collided with
		return true;
	}
	else
	{
		// Return not being collided with
		return false;
	}
}

/*
	Name		FlickableObject::beenTouched
	Syntax		FlickableObject::beenTouched()
	Return		True	- if the object has been touched
				False	- if the object has not been touched
	Brief		Returns the been touched bool
*/
bool FlickableObject::beenTouched() const
{
	return beenTouched_;
}

/*
	Name		FlickableObject::getCentreX
	Syntax		FlickableObject::getCentreX()
	Return		int16 - Centre X coord of the flickable object
	Brief		Returns the centre x coordinate of the flickable object
*/
int16 FlickableObject::getCentreX() const 
{
	return x_;
}

/*
	Name		FlickableObject::getCentreY
	Syntax		FlickableObject::getCentreY()
	Return		int16 - Centre Y coord of the flickable object
	Brief		Returns the centre y coordinate of the flickable object
*/
int16 FlickableObject::getCentreY() const 
{
	return y_;
}

/*
	Name		FlickableObject::getLeftSide
	Syntax		FlickableObject::getLeftSide()
	Return		int16 - x coord of the left side of the flickable object
	Brief		Returns the x coord of the left side of the flickable object
*/
inline int16 FlickableObject::getLeftSide()
{
	// Return the x coord of the left side
	return (x_ - (width_/2));
}

/*
	Name		FlickableObject::getRightSide	
	Syntax		FlickableObject::getRightSide()
	Return		int16 - x coord of the right side of the flickable object
	Brief		Returns the x coord of the right side of the flickable object
*/
inline int16 FlickableObject::getRightSide()
{
	// Return the x coord of the right side
	return (x_ + (width_/2));
}

/*
	Name		FlickableObject::getTop
	Syntax		FlickableObject::getTop()
	Return		int16 - y coord of the top of the flickable object
 	Brief		Returns the y coord of the top of the flickable object
*/
inline int16 FlickableObject::getTop()
{
	// Return the y coord of the top of the build piece
	return (y_ - (height_/2));
}

/*
	Name		FlickableObject::getBottom
	Syntax		FlickableObject::getBottom()
	Returns		int16 - y coord of the bottom of the flickable object
	Brief		Returns the y coord of the bottom of the flickable object
*/
inline int16 FlickableObject::getBottom()
{
	// Return the y coord of the bottom of the build piece
	return (y_ + (height_/2));
}

/*
	Name		FlickableObject::update
	Syntax		FlickableObject::update()
	Brief		Update the flickable object
*/
void FlickableObject::update()
{
	// Check to see if the velocity hs been set
	if(velocitySet_)
	{
		// Update the position of the flickable object by the velocity
		x_ += velocity_[0];
		y_ += velocity_[1];

		// Apply gravity
		y_ += 3;

		// If x velocity is greater than 0
		if( velocity_[0] > 0)
		{
			// Reduce x velocity 
			velocity_[0]--;
		}
		// If x velocity is less than 0 
		if( velocity_[0] < 0)
		{
			// Add to x velocity
			velocity_[0]++;
		}
		// If y velocity is greater than 0
		if( velocity_[1] > 0)
		{
			// Reduce y velocity
			velocity_[1]--;
		}
		// If y velocity is less than 0
		if( velocity_[1] < 0)
		{
			// Add to y velocity
			velocity_[1]++;
		}
	}	// End of check to see if velocity is set

	// Move sprite to new position
	sprite_->moveTo(x_, y_);
}

/*
	Name		FlickableObject::setVelocity
	Syntax		FlickableObject::setVelocity(int startX, int startY, int endX, int endY)
	Params		int startX - The x coordinate of the first touch
				int startY - The y coordinate of the first touch
				int endX   - The x coordinate of the second touch
				int endY   - The y coordinate of the second touch
	Brief		
*/
void FlickableObject::setVelocity(int startX, int startY, int endX, int endY)
{
	// Calculate x speed and y speed using parameters from function 
	int xSpeed = (endX - startX)/2;
	int ySpeed = (endY - startY)/2;

	// Set velocity with calculated speed
	velocity_[0] = xSpeed;
	velocity_[1] = ySpeed;

	// Velocity has been set so set the boolean describing this condition to true
	velocitySet_ = true;
}

/*
	Name		FlickableObject::setTouched
	Syntax		FlickableObject::setTouched()
	Brief		Sets been touched to true
*/
void FlickableObject::setTouched()
{
	beenTouched_ = true;
}

/*
	Name		
	Syntax		
	Brief		
*/
bool FlickableObject::getVelocitySet()
{
	return velocitySet_;
}