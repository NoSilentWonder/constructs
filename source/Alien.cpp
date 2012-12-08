/*
	Copyright	Kangaroo Magic 2011
	Created 	Jonathan Jones
				Elinor Townsend
	
	Name		Alien
	Brief		Contains everything associated with the alien 
*/

#include "Alien.hpp"
#include "Quad.hpp"
#include "Material.hpp"
#include "SoundEffect.hpp"

/*
	Name	Alien::Alien
	Syntax	Alien::Alien()
	Brief	Use init list and set variables	
*/
Alien::Alien()
: x_(512)
, y_(528)
, z_(0)
, width_(255)
, height_(255)
, speed_(10)
, idleMat_(0)
, walkingMat_(0)
, hoseMat_(0)
, idleTex_(0)
, walkingTex_(0)
, hoseTex_(0)
, movingLeft_(false)
, walking_(false)
, holdingGravityHose_(false)
, walkNormal_(0)
, walkGrass_(0)
{
	//x_ = IwGxGetScreenWidth() / 2;
	//y_ = IwGxGetScreenHeight() / 2;


}

/*
	Name		Alien::~Alien
	Syntax		Alien::~Alien()
	Brief		Delete variables
*/
Alien::~Alien()
{
}

/*
	Name		Alien::initialise
	Syntax		Alien::initialise()
	Brief		initialise any variables that still need to be initialised
*/
void Alien::initialise()
{
	// Set quad up
	alien_.moveTo(x_, y_);
	alien_.setDimensions(width_, height_);
	alien_.setZ(z_);

	// Set the texture to the alien png
	idleTex_ = new CIwTexture;
	idleTex_->LoadFromFile("sprites/alien/idle.png");
    idleTex_->Upload();

	// Set up walking animation
    walkingTex_ = new CIwTexture;
	walkingTex_->LoadFromFile("sprites/alien/walking.png");
    walkingTex_->Upload();

	// Set up gravity hose animation
    hoseTex_ = new CIwTexture;
	hoseTex_->LoadFromFile("sprites/alien/hose.png");
    hoseTex_->Upload();

	// Create the idle material and set up the animation
	idleMat_ = new Material;
    idleMat_->setTexture(idleTex_);
	idleMat_->createAnim();
	idleMat_->setFrameDelay(5);
	idleMat_->setFrameWidth(254);
	idleMat_->setFrameHeight(254);
	idleMat_->setNumberOfFrames(33);

	// Create the walking material and set up the animation
	walkingMat_ = new Material;
    walkingMat_->setTexture(walkingTex_);
	walkingMat_->createAnim();
	walkingMat_->setFrameDelay(1);
	walkingMat_->setFrameWidth(254);
	walkingMat_->setFrameHeight(254);
	walkingMat_->setNumberOfFrames(24);

	// Create the gravity hose material and set up the animation
	hoseMat_ = new Material;
    hoseMat_->setTexture(hoseTex_);
	hoseMat_->createAnim();
	hoseMat_->setFrameDelay(1);
	hoseMat_->setFrameWidth(254);
	hoseMat_->setFrameHeight(254);
	hoseMat_->setNumberOfFrames(24);

	// Set the UV coordinates for materials	
	CIwSVec2 topLeft = CIwSVec2(0<<12, 0<<12);
	CIwSVec2 bottomLeft = CIwSVec2(0<<12, 1<<9);
	CIwSVec2 topRight = CIwSVec2(1<<9, 0<<12);
	CIwSVec2 bottomRight = CIwSVec2(1<<9, 1<<9);

	idleMat_->setUVs(topLeft, bottomLeft, topRight, bottomRight);

	walkingMat_->setUVs(topLeft, bottomLeft, topRight, bottomRight);

	hoseMat_->setUVs(topLeft, bottomLeft, topRight, bottomRight);

	walkNormal_ = new SoundEffect;
	walkNormal_->initialise("audio/Movement/Alien/AlienWalk2.wav");

	walkGrass_ = new SoundEffect;
	walkGrass_->initialise("audio/Movement/Alien/AlienWalkGrass.wav");

}

/*
	Name		Alien::deinitialise
	Syntax		Alien::deinitialise()	
	Brief		delete any resources that need explict deletion
*/
void Alien::deinitialise()	
{
	if (idleMat_)
	{
		delete idleMat_;
		idleMat_ = 0;
	}

	if (walkingMat_)
	{
		delete walkingMat_;
		walkingMat_ = 0;
	}

	if (hoseMat_)
	{
		delete hoseMat_;
		hoseMat_ = 0;
	}

	if (idleTex_)
	{
		delete idleTex_;
		idleTex_ = 0;
	}

	if (walkingTex_)
	{
		delete walkingTex_;
		walkingTex_ = 0;
	}

	if (hoseTex_)
	{
		delete hoseTex_;
		hoseTex_ = 0;
	}

	delete walkNormal_;
	walkNormal_ = 0;

	delete walkGrass_;
	walkGrass_ = 0;

}

/*
	Name		Alien::moveRight
	Syntax		Alien::moveRight()
	Brief		move the alien sprite right
*/
void Alien::moveRight()
{
	// If not moving right
	if (movingLeft_)
	{
		// Set moving left to false 
		movingLeft_ = false;
	}

	// Move the alien to the right 
	x_ += speed_;

	// Set the aliens new position
	alien_.moveTo(x_, y_);
}

/*
	Name		Alien::moveLeft
	Syntax		Alien::moveLeft()
	Brief		Move the alien sprite left
*/
void Alien::moveLeft()
{
	// If not moving left
	if (!movingLeft_)
	{
		// Set moving left to true
		movingLeft_ = true;
	}

	// Move the alien left
	x_ -= speed_;

	// Set the aliens new position
	alien_.moveTo(x_, y_);
}

/*
	Name		Alien::render
	Syntax		Alien::render()
	Brief		Render the alien sprite
*/
void Alien::render()
{
	if (walking_)
	{
		walkNormal_->play(0);
		// If the alien is moving left 
		if (movingLeft_)
		{
			// Sets the uv to be drawn from right to left (reversed)
			walkingMat_->use(true);
		}
		else
		{
			// Sets the uv to be drawn from left to right (normal)
			walkingMat_->use(false);
		}
	}
	else
	{
		if (holdingGravityHose_)
			hoseMat_->use(false);			
		else
		{
			walkNormal_->stop();
			// If the alien is moving left 
			if (movingLeft_)
			{
				// Sets the uv to be drawn from right to left (reversed)
				idleMat_->use(true);
			}
			else
			{
				// Sets the uv to be drawn from left to right (normal)
				idleMat_->use(false);
			}
		}
	}

    // Render the sprite
    alien_.render();
}

/*
	Name		Alien::getX
	Syntax		Alien::getX()
	Return		int16 - Returns x coordinate of the alien
	Brief		Return the X coordinate of the alien 
*/
int16 Alien::getX()
{
	return x_;
}

/*
	Name		Alien::getY
	Syntax		Alien::getY()
	Return		int16 - Returns y coordinate of the alien
	Brief		Return the Y coordinate of the alien
*/
int16 Alien::getY()
{
	return y_;
}

void Alien::movingLeft()
{
	movingLeft_ = true;
}

void Alien::movingRight()
{
	movingLeft_ = false;
}

/*
	Name		Alien::setWalking
	Syntax		Alien::setWalking()
	Brief		Sets the alien walking flag to true
*/
void Alien::setWalkingState(bool state)
{
	walking_ = state;
}

/*
	Name		Alien::setHoldingHose
	Syntax		Alien::setHoldingHose(bool holding)
	Param		bool holding - IS alien holding gravity hose
	Brief		Sets the alien gravity hose flag
*/
void Alien::setHoldingHose(bool holding)
{
	holdingGravityHose_ = holding;
}

/*
	Name		Alien::setX
	Syntax		Alien::setX(int16 X)
	Param		int16 x - The x coordinate to set the alien position to
	Brief		Set the x value of the alien
*/
void Alien::setX(int16 x)
{
	// Set the x coordinate to the passed value
	x_ = x;

	// Move the alien to the new position
	alien_.moveTo(x_, y_);
}

/*
	Name		Alien::setY
	Syntax		Alien::setY(int16 y)
	Param		int16 y - The y coordinate to set the alien position to
	Brief		Set the y value of the alien
*/
void Alien::setY(int16 y)
{
	// Set the y coordinate to the passed value
	y_ = y;

	// Move the alien to the new position
	alien_.moveTo(x_, y_);
}

/*
	Name		Alien::getWidth()
	Syntax		Alien::getWidth()
	Return		The width of the alien
	Brief		Returns the width of the alien
*/
int16 Alien::getWidth()
{
	return width_;
}

/*
	Name		Alien::getHeight
	Syntax		Alien::getHeight()
	Return		The height of the alien
	Brief		Returns the height of the alien
*/
int16 Alien::getHeight()
{
	return height_;
}

/*
	Name		Alien::getWalkingState
	Syntax		Alien::getWalkingState()
	Return		true  - if the alien is walking
				false - if the alien is not walking 
	Brief		Returns the walking state of the alien
*/
bool Alien::getWalkingState()
{
	return walking_;
}

/*
	Name		Alien::setSpeed
	Syntax		Alien::setSpeed(int16 speed)
	Param		int16 speed - The walking speed to give the alien
	Brief		Set the walking speed of the alien
*/
void Alien::setSpeed(int16 speed)
{
	speed_ = speed;
}

/*
	Name		Alien::stopAllSounds
	Syntax		Alien::stopAllSounds()
	Brief		Stop all the sounds from playing
*/
void Alien::stopAllSounds()
{
	walkNormal_->stop();
	walkGrass_->stop();
}