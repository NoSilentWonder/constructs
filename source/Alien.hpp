/*
	Copyright	Kangaroo Magic 2011
	Created 	Jonathan Jones
				Elinor Townsend
	
	Name		Alien
	Brief		Contains everything associated with the alien 
*/

#ifndef ALIEN_HPP
#define ALIEN_HPP

// Includes 
#include "s3eTypes.h"
#include "Quad.hpp"
#include "Material.hpp"

class SoundEffect;

/*
	Name		Alien
	Brief		Contains everything associated with the alien 
*/
class Alien
{
public:
	Alien();
	~Alien();
	void initialise();			// Sets up alien
	void deinitialise();		// Release resources associated with alien
	void moveRight();			// Moves the alien right 
	void moveLeft();			// Moves the alien left 
	void render();				// Render the alien
	int16 getX();				// Return the x coordinate of the alien
	int16 getY();				// Return the y coordinate of the alien
	void movingLeft();
	void movingRight();
	void setWalkingState(bool state);
	void setHoldingHose(bool holding);
	void setX(int16 x);
	void setY(int16 y);
	int16 getWidth();
	int16 getHeight();
	bool getWalkingState();
	void setSpeed(int16 speed);
	void stopAllSounds();
private:
	int16 x_;					// World x position
	int16 y_;					// World y position
	int16 z_;					// World z position
	int16 width_;				// The width of the alien quad
	int16 height_;				// The height of the alien quad
	int16 speed_;				// Speed at which the alien moves
	Quad alien_;				// Represents vertices in world space
    Material* idleMat_;			// The material holding the texture information for the alien
	Material* walkingMat_;
	Material* hoseMat_;
    CIwTexture* idleTex_;		// A pointer to the alien texture
	CIwTexture* walkingTex_;
	CIwTexture* hoseTex_;
	bool movingLeft_;			// Represents if the alien is moving right
	bool walking_;
	bool holdingGravityHose_;
	SoundEffect* walkNormal_;
	SoundEffect* walkGrass_;
};

#endif	// ALIEN_HPP