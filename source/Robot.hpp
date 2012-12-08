/*
	Copyright	Kangaroo Magic 2011
	Created 	Jonathan Jones
				Elinor Townsend
	
	Name		Robot
	Brief		Contains everything associated with the robot 
*/

#ifndef ROBOT_HPP
#define ROBOT_HPP

// Includes 
#include "s3eTypes.h"
#include "IwGx.h"
#include "Quad.hpp"
#include "Material.hpp"

class SoundEffect;

enum RobotTalk
{
	ROBOT_TALK_HAPPY,
	ROBOT_TALK_STANDARD,
	ROBOT_TALK_UNCERTAIN,
	ROBOT_TALK_CONFLICT,
	ROBOT_TALK_CONFUSED
};

/*
	Name		Robot
	Brief		Contains everything associated with the robot 
*/
class Robot
{
public:
	Robot();										
	~Robot();
	void initialise();								// initialise any variables that still need to be initialised
	void deinitialise();							// delete any resources that need explict deletion
	void render();									// render the sprite 
	void followAlien(int16 alienX, int16 alienY);	// move the robot relative to the alien position
	void moveRight(int16 alienX);
	void moveLeft(int16 alienX);
	void setWalking();
	void setCenterX(int16 x);
	int16 getCentreX();
	void setCentreY(int16 y);
	int16 getWidth();
	int16 getHeight();
	void talk(RobotTalk talk);
	void stopAllSounds();
private:
	void initialiseSounds();
	void deinitialiseSounds();
	int16 x_;										// World x position
	int16 y_;										// World y position
	int16 z_;										// World z position
	int16 width_;									// The width of the robot quad
	int16 height_;									// The height of the robot quad
	int16 speed_;									// Speed at which the robot moves
	Quad robotTop_;									// The vertices of the robot bounding box in world space
	Quad robotBottom_;
	Material* idleTopMat_;							// The material holding the texture information for the robot
	Material* idleBottomMat_;
	Material* walkingTopMat_;
	Material* walkingBottomMat_;
	CIwTexture* idleTopTex_;						// A pointer to the robot texture
	CIwTexture* idleBottomTex_;
	CIwTexture* walkingTopTex_;
	CIwTexture* walkingBottomTex_;
	bool movingLeft_;								// Represents which direction the robot is facing 
	bool walking_;
	enum{ MAX_VELOCITY_ = 4,						// The maximum velocity of the Robot
		  MIN_VELOCITY_ = 0,};						// The minimum velocity of the Robot								
	int16 offsetFromAlien_;							// The distance that the robot should be from the alien

	SoundEffect* talkHappy_;
	SoundEffect* talkStandard_;
	SoundEffect* talkUncertain_;
	SoundEffect* talkConflict_;
	SoundEffect* talkConfused_;
	SoundEffect* walkNormal_;
	SoundEffect* walkGrass_;

	CIwTexture* throwingTopTex_;
	CIwTexture* throwingBottomTex_;
	Material* throwingTopMat_;
	Material* throwingBottomMat_;
	
	bool throwing_;
};

#endif // ROBOT_HPP