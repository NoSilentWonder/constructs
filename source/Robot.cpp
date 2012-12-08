/*
	Copyright	Kangaroo Magic 2011
	Created 	Jonathan Jones
				Elinor Townsend
	
	Name		Robot
	Brief		Contains everything associated with the robot 
*/

// Includes 
#include "Robot.hpp"
#include "Quad.hpp"
#include "Material.hpp"
#include "SoundEffect.hpp"


/*
	Name	Robot::Robot
	Syntax	Robot::Robot()
	Brief	Use init list and set variables	
*/
Robot::Robot()
: x_(0)	
, y_(400)
, z_(0)
, width_(255)
, height_(510)
, speed_(0)
, idleTopMat_(0)
, idleBottomMat_(0)
, walkingTopMat_(0)
, walkingBottomMat_(0)
, idleTopTex_(0)
, idleBottomTex_(0)
, walkingTopTex_(0)
, walkingBottomTex_(0)
, movingLeft_(false)
, walking_(false)
, offsetFromAlien_(150)
, talkHappy_(0)
, talkStandard_(0)
, talkUncertain_(0)
, talkConflict_(0)
, talkConfused_(0)
, walkNormal_(0)
, walkGrass_(0)
, throwingTopTex_(0)
, throwingBottomTex_(0)
, throwingTopMat_(0)
, throwingBottomMat_(0)
, throwing_(false)
{
}

/*
	Name	Robot::~Robot
	Syntax	Robot::~Robot()
	Brief	Delete variables
*/
Robot::~Robot()
{
}

/*
	Name	Robot::initialise
	Syntax	Robot::initialise()
	Brief	initialise any variables that still need to be initialised
*/
void Robot::initialise()
{
	// Set quads up
	robotTop_.moveTo(x_, y_);
	robotTop_.setDimensions(width_, height_/2);
	robotTop_.setZ(z_);

	robotBottom_.moveTo(x_, y_ + height_ - 2);
	robotBottom_.setDimensions(width_, height_/2);
	robotBottom_.setZ(z_);

	// Set the idle textures for the robot
	idleTopTex_ = new CIwTexture;
	idleTopTex_->LoadFromFile("sprites/robot/IdleTop.png");
    idleTopTex_->Upload();
	idleBottomTex_ = new CIwTexture;
	idleBottomTex_->LoadFromFile("sprites/robot/IdleBottom.png");
    idleBottomTex_->Upload();

	// Set the walking textures for the robot
	walkingTopTex_ = new CIwTexture;
	walkingTopTex_->LoadFromFile("sprites/robot/RobotWalk1Top.png");
    walkingTopTex_->Upload();
	walkingBottomTex_ = new CIwTexture;
	walkingBottomTex_->LoadFromFile("sprites/robot/RobotWalk1Bottom.png");
    walkingBottomTex_->Upload();
	
	// Create and set the throwing texture top
	throwingTopTex_ = new CIwTexture;
	throwingTopTex_->LoadFromFile("sprites/robot/FlingBackwardsTop48.png");
	throwingTopTex_->Upload();

	// Create and set the throwing texture bottom
	throwingBottomTex_ = new CIwTexture;
	throwingBottomTex_->LoadFromFile("sprites/robot/FlingBackwardsBottom48.png");
	throwingBottomTex_->Upload();

	// Create the idle materials and set up the animations
	idleTopMat_ = new Material;
    idleTopMat_->setTexture(idleTopTex_);
	idleTopMat_->createAnim();
	idleTopMat_->setFrameDelay(5);
	idleTopMat_->setFrameWidth(255);
	idleTopMat_->setFrameHeight(255);
	idleTopMat_->setNumberOfFrames(48);

	idleBottomMat_ = new Material;
    idleBottomMat_->setTexture(idleBottomTex_);
	idleBottomMat_->createAnim();
	idleBottomMat_->setFrameDelay(5);
	idleBottomMat_->setFrameWidth(255);
	idleBottomMat_->setFrameHeight(255);
	idleBottomMat_->setNumberOfFrames(48);

	// Create the walking material and set up the animation
	walkingTopMat_ = new Material;
    walkingTopMat_->setTexture(walkingTopTex_);
	walkingTopMat_->createAnim();
	walkingTopMat_->setFrameDelay(1);
	walkingTopMat_->setFrameWidth(255);
	walkingTopMat_->setFrameHeight(255);
	walkingTopMat_->setNumberOfFrames(47);

	walkingBottomMat_ = new Material;
    walkingBottomMat_->setTexture(walkingBottomTex_);
	walkingBottomMat_->createAnim();
	walkingBottomMat_->setFrameDelay(1);
	walkingBottomMat_->setFrameWidth(255);
	walkingBottomMat_->setFrameHeight(255);
	walkingBottomMat_->setNumberOfFrames(47);

	// Create and set throwing top material
	throwingTopMat_ = new Material;
	throwingTopMat_->setTexture(throwingTopTex_);
	throwingTopMat_->createAnim();
	throwingTopMat_->setFrameDelay(2);
	throwingTopMat_->setFrameWidth(255);
	throwingTopMat_->setFrameHeight(255);
	throwingTopMat_->setNumberOfFrames(48);

	// Create and set throwing bottom material
	throwingBottomMat_ = new Material;
	throwingBottomMat_->setTexture(throwingBottomTex_);
	throwingBottomMat_->createAnim();
	throwingBottomMat_->setFrameDelay(2);
	throwingBottomMat_->setFrameWidth(255);
	throwingBottomMat_->setFrameHeight(255);
	throwingBottomMat_->setNumberOfFrames(48);

	// Set the UV coordinates for materials	
	CIwSVec2 topLeft = CIwSVec2(0<<12, 0<<12);
	CIwSVec2 bottomLeft = CIwSVec2(0<<12, 1<<9);
	CIwSVec2 topRight = CIwSVec2(1<<9, 0<<12);
	CIwSVec2 bottomRight = CIwSVec2(1<<9, 1<<9);

	idleTopMat_->setUVs(topLeft, bottomLeft, topRight, bottomRight);
	idleBottomMat_->setUVs(topLeft, bottomLeft, topRight, bottomRight);
	walkingTopMat_->setUVs(topLeft, bottomLeft, topRight, bottomRight);
	walkingBottomMat_->setUVs(topLeft, bottomLeft, topRight, bottomRight);
	throwingTopMat_->setUVs(topLeft, bottomLeft, topRight, bottomRight);
	throwingBottomMat_->setUVs(topLeft, bottomLeft, topRight, bottomRight);

	initialiseSounds();

}

/*
	Name	Robot::deinitialise
	Syntax	Robot::deinitialise()
	Brief	delete any resources that need explict deletion
*/
void Robot::deinitialise()
{
	if (idleTopMat_)
	{
		delete idleTopMat_;
		idleTopMat_ = 0;
	}

	if (idleBottomMat_)
	{
		delete idleBottomMat_;
		idleBottomMat_ = 0;
	}

	if (walkingTopMat_)
	{
		delete walkingTopMat_;
		walkingTopMat_ = 0;
	}

	if (walkingBottomMat_)
	{
		delete walkingBottomMat_;
		walkingBottomMat_ = 0;
	}

	if (idleTopTex_)
	{
		delete idleTopTex_;
		idleTopTex_ = 0;
	}

	if (idleBottomTex_)
	{
		delete idleBottomTex_;
		idleBottomTex_ = 0;
	}

	if (walkingTopTex_)
	{
		delete walkingTopTex_;
		walkingTopTex_ = 0;
	}

	if (walkingBottomTex_)
	{
		delete walkingBottomTex_;
		walkingBottomTex_ = 0;
	}

	if( throwingTopTex_ )
	{
		delete throwingTopTex_;
		throwingTopTex_ = 0;
	}

	if( throwingBottomTex_ )
	{
		delete throwingBottomTex_;
		throwingBottomTex_ = 0;
	}

	if( throwingTopMat_ )
	{
		delete throwingTopMat_;
		throwingTopMat_ = 0;
	}

	if( throwingBottomMat_ )
	{
		delete throwingBottomMat_;
		throwingBottomMat_ = 0;
	}

	deinitialiseSounds();
}

/*
	Name	Robot::render
	Syntax	Robot::render()
	Brief	Render the robot sprite
*/
void Robot::render()
{
	Material* matTop;
	Material* matBottom;

	// Select active materials
	if (walking_)
	{
		matTop = walkingTopMat_;
		matBottom = walkingBottomMat_;
		walkNormal_->play(0);
	}
	else
	{
		matTop = idleTopMat_;
		matBottom = idleBottomMat_;
		walkNormal_->stop();
	}

	// Use material for top of robot 
	if (!movingLeft_)
	{
		// Sets the uv's to be drawn from right to left (reversed)
		matTop->use(true);
	}
	else
	{
		// Sets the uv's to be drawn from left to right (normal)
		matTop->use(false);
	}


	//matTop = throwingTopMat_;
	//matTop->use(true);

	// Render the bottom of the robot
	robotTop_.render();

	// Use material for bottom of robot 
	if (!movingLeft_)
	{
		// Sets the uv's to be drawn from right to left (reversed)
		matBottom->use(true);
	}
	else
	{
		// Sets the uv's to be drawn from left to right (normal)
		matBottom->use(false);
	}

	//matBottom = throwingBottomMat_;
	//matBottom->use(true);

	// Render the bottom of the robot
	robotBottom_.render();
	
	matTop = 0;
	matBottom = 0;

	walking_ = false;
}

/*
	Name	Robot::followAlien
	Syntax	Robot::followAlien(int16 alienX, int16 alienY)
	Params	int16 alienX - The x coordinate of the alien
			int16 alienY - The y coordinate of the alien
	Brief	Makes the robot follow behind the alien
*/
void Robot::followAlien(int16 alienX, int16 alienY)
{
	y_ = alienY - height_ + 2;

	// Check to see if the robot is close to the alien and return true if he is
	// if robot x is greater than alien left hand side and robot x is less than alien right hand side 
	if( ( x_ >= (alienX - offsetFromAlien_)) && 
		( x_ <= (alienX + offsetFromAlien_)) )
	{
		// Check to see if the velocity is above its minimum value
		if(speed_ > MIN_VELOCITY_)
		{
			// If its not below the minimum then reduce the velocity
			speed_--;
		}
	}

	// If robot is on the left of the alien
	else if( x_ < (alienX - offsetFromAlien_) )
	{
		movingLeft_ = false;
		// Check to see if the velocity has reached its max
		if(speed_ < MAX_VELOCITY_)
		{
			// If it hasnt then add one to the velocity
			speed_++;
		}
		
		// Make the robot appear to move right by adding the velocity to the x coordinate
		x_ += speed_;
	}
	
	// If the robot is on the right of the alien
	else if( x_ > (alienX + offsetFromAlien_))
	{
		movingLeft_ = true;
		// Check to see if the velocity has reached its max
		if(speed_ < MAX_VELOCITY_)
		{
			// If it hasnt then add one to the velocity
			speed_++;
		}

		// Make the robot appear to move left by adding the velocity to the x coordinate
		x_ -= speed_;
	}

	if (speed_ != 0)
	{
		setWalking();
	}

	// Set the position of the robot
	robotTop_.moveTo(x_, y_ + (height_/2));
	robotBottom_.moveTo(x_, y_ + height_ - 2);
}

/*
	Name		Robot::moveRight
	Syntax		Robot::moveRight(int16 alienX)
	Param		int16 alienX - The alien's centre x coordinate
	Brief		Move the robot right
*/
void Robot::moveRight(int16 alienX)
{
	// If the robot is on right of the alien
	if( x_ >= (alienX - offsetFromAlien_) )
	{
		x_ += 5;
	
		// Set the position of the robot
		robotTop_.moveTo(x_, y_  + (height_/2));
		robotBottom_.moveTo(x_, y_ + height_ - 2);
	}
}

/*
	Name		Robot::moveLeft
	Syntax		Robot::moveLeft(int16 alienX)
	Param		int16 alienX - The alien's centre x coordinate
	Brief		Move the robot left
*/
void Robot::moveLeft(int16 alienX)
{
	// If the robot is on left of the alien
	if( x_ <= (alienX + offsetFromAlien_) )
	{
		x_ -= 5;
	
		// Set the position of the robot
		robotTop_.moveTo(x_, y_  + (height_/2));
		robotBottom_.moveTo(x_, y_ + height_ - 2);
	}
}

/*
	Name		Robot::setWalking
	Syntax		Robot::setWalking()
	Brief		Sets the robot walking flag to true
*/
void Robot::setWalking()
{
	walking_ = true;
}

/*
	Name		Robot::setCenterX
	Syntax		Robot::setCenterX(int16 x)
	Param		int16 x - The x coordinate to set the robot to
	Brief		Sets the x coordinate to the passed x coordinate
*/
void Robot::setCenterX(int16 x)
{
	x_ = x;
}

/*
	Name		Robot::getCentreX
	Syntax		Robot::getCentreX()
	Return		The x coordinate of the robot
	Brief		Returns the x coordinate of the robot
*/
int16 Robot::getCentreX()
{
	return x_;
}

/*
	Name		Robot::setCentreY
	Syntax		Robot::setCentreY(int16 y)
	Param		Sets the y coordinate to the passed y
	Brief		Changes the y coordinate to the passed value
*/
void Robot::setCentreY(int16 y)
{
	y_ = y;
}

/*
	Name		Robot::getWidth
	Syntax		Robot::getWidth()
	Return		The width of the robot
	Brief		Returns the width of the robot
*/
int16 Robot::getWidth()
{
	return width_;
}

/*
	Name		Robot::getHeight
	Syntax		Robot::getHeight()
	Return		The height of the robot
	Brief		Returns the height of the robot
*/
int16 Robot::getHeight()
{
	return height_;
}

/*
	Name		Robot::initialiseSounds
	Syntax		Robot::initialiseSounds()
	Brief		Initialises the sound effects for the robot
*/
void Robot::initialiseSounds()
{
	talkHappy_ = new SoundEffect;
	talkHappy_->initialise("audio/Communicate/RobotHappyComplete.wav");

	talkStandard_ = new SoundEffect;
	talkStandard_->initialise("audio/Communicate/RobotStandard.wav");

	talkUncertain_ = new SoundEffect;
	talkUncertain_->initialise("audio/Communicate/RobotUncertain.wav");

	talkConflict_ = new SoundEffect;
	talkConflict_->initialise("audio/Communicate/RobotConflict.wav");

	talkConfused_ = new SoundEffect;
	talkConfused_->initialise("audio/Communicate/RobotConfused.wav");

	walkNormal_ = new SoundEffect;
	walkNormal_->initialise("audio/Movement/Robot/RobotWalk1.wav");

	walkGrass_ = new SoundEffect;
	walkGrass_->initialise("audio/Movement/Robot/RobotWalkGrass1.wav");
}

/*
	Name		Robot::deinitialiseSounds
	Syntax		Robot::deinitialiseSounds()
	Brief		Deinitialises the sound effects for the robot
*/
void Robot::deinitialiseSounds()
{
	delete talkHappy_;
	talkHappy_ = 0;

	delete talkStandard_;
	talkStandard_ = 0;

	delete talkUncertain_;
	talkUncertain_ = 0;

	delete talkConflict_;
	talkConflict_ = 0;

	delete talkConfused_;
	talkConfused_ = 0;

	delete walkNormal_;
	walkNormal_ = 0;

	delete walkGrass_;
	walkGrass_= 0;
}

/*
	Name		Robot::talk
	Syntax		Robot::talk(RobotTalk talk)
	Brief		Plays a robot talk sound
*/
void Robot::talk(RobotTalk talk)
{
	switch(talk)
	{
	case ROBOT_TALK_HAPPY:
		talkHappy_->play(1);
		break;
	case ROBOT_TALK_STANDARD:
		talkStandard_->play(1);
		break;
	case ROBOT_TALK_UNCERTAIN:
		talkUncertain_->play(1);
		break;
	case ROBOT_TALK_CONFLICT:
		talkConflict_->play(1);
		break;
	case ROBOT_TALK_CONFUSED:
		talkConfused_->play(1);
		break;
	default:
		break;
	}
}

/*
	Name		Robot::stopAllSounds
	Syntax		Robot::stopAllSounds()
	Brief		Stop all the sounds from playing
*/
void Robot::stopAllSounds()
{
	talkHappy_->stop();
	talkStandard_->stop();
	talkUncertain_->stop();
	talkConflict_->stop();
	talkConfused_->stop();
	walkNormal_->stop();
	walkGrass_->stop();
}