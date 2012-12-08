/*
	Copyright	Kangaroo Magic 2011
	Created 	Elinor Townsend
	
	Name		AnimatedSprite
	Brief		Declaration of AnimatedSprite class
*/

#ifndef _ANIMATED_SPRITE_HPP
#define _ANIMATED_SPRITE_HPP
 
#include "Sprite.hpp"

/*
	Name		AnimatedSprite class
	Brief		The AnimatedSprite class creates a sprite that has an
				animation material and can be rendered as a static sprite,
				play the animation a single time when triggered, or continually
				loop its animation
*/
class AnimatedSprite : public Sprite
{
public:
	AnimatedSprite();
	~AnimatedSprite();
	void setupAnim(char* fileName, uint8 frameWidth, uint8 frameHeight, uint8 numOfFrames, uint8 frameDelay);
	void triggerAnimation();
	void loopAnimation();
	void stopAnimation();
	void render();
	void setUVs(CIwSVec2 &topLeft, CIwSVec2 &bottomLeft, 
			CIwSVec2 &topRight, CIwSVec2 &bottomRight);
private:
	CIwTexture* animationTex_;
    Material* animationMat_;
	bool looping_;
	bool animating_;
	int8 delayTracker_;
};

#endif	// _ANIMATED_SPRITE_HPP