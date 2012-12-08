/*
	Copyright	Kangaroo Magic 2011
	Created 	Elinor Townsend
	
	Name		AnimatedSprite
	Brief		Definition of the methods of AnimatedSprite class
*/

#include "AnimatedSprite.hpp"

/*
	Name		AnimatedSprite::AnimatedSprite
	Syntax		AnimatedSprite()
	Brief		AnimatedSprite constructor initialises member variables
*/
AnimatedSprite::AnimatedSprite()
	: Sprite(), animationTex_(0), animationMat_ (0), looping_(false), 
	  animating_(false), delayTracker_(0)
{
	
}

/*
	Name		AnimatedSprite::~AnimatedSprite
	Syntax		~AnimatedSprite()
	Brief		AnimatedSprite destructor 
*/
AnimatedSprite::~AnimatedSprite()
{
	if (animationMat_)
	{
		delete animationMat_;
		animationMat_ = 0;
	}

	if (animationTex_)
	{
		delete animationTex_;
		animationTex_ = 0;
	}
}

/*
	Name		AnimatedSprite::setupAnim
	Syntax		AnimatedSprite::setupAnim(char* fileName, uint8 frameWidth, 
										  uint8 frameHeight, uint8 numOfFrames, 
										  uint8 frameDelay)
	Param		char* fileName - The name of the texture resource to be used
	Param		uint8 frameWidth - Width of each frame
	Param		uint8 frameHeight - Height of each frame
	Param		uint8 numOfFrames - The number of frames
	Param		uint8 frameDelay - The time to pause on each frame
	Brief		Creates the sprite's animation
*/
void AnimatedSprite::setupAnim(char* fileName, uint8 frameWidth, uint8 frameHeight, 
							   uint8 numOfFrames, uint8 frameDelay)
{
	// Create animation texture
	animationTex_ = new CIwTexture;
	animationTex_->LoadFromFile(fileName);
	animationTex_->Upload();

	// Set the animation material to the sprite texture
	animationMat_ = new Material;
    animationMat_->setTexture(animationTex_);

	// Create animation
	animationMat_->createAnim();
	animationMat_->setFrameDelay(frameDelay);
	animationMat_->setFrameWidth(frameWidth);
	animationMat_->setFrameHeight(frameHeight);
	animationMat_->setNumberOfFrames(numOfFrames);

	// Set delay tracker used for stopping animation from playing
	delayTracker_ = frameDelay;
}

/*
	Name		AnimatedSprite::triggerAnimation
	Syntax		AnimatedSprite::triggerAnimation()
	Brief		Triggers the sprite's animation to play
*/
void AnimatedSprite::triggerAnimation()
{
	animating_ = true;
	animationMat_->restartAnim();
}

/*
	Name		AnimatedSprite::loopAnimation
	Syntax		AnimatedSprite::loopAnimation()
	Brief		Sets the animation of the sprite to loop
*/
void AnimatedSprite::loopAnimation()
{
	looping_ = true;
	animating_ = true;
}

/*
	Name		AnimatedSprite::stopAnimation
	Syntax		AnimatedSprite::stopAnimation()
	Brief		Stops the sprite animating
*/
void AnimatedSprite::stopAnimation()
{
	looping_ = false;
	animating_ = false;
}

/*
	Name		AnimatedSprite::render
	Syntax		AnimatedSprite::render()
	Brief		Renders the sprite
	Details		If the sprite is animating then use the animation material, 
				otherwise render the sprite using the static material.
				If looping is not turned on, check for when the final frame
				of the animation has been played and switch animating off.
*/
void AnimatedSprite::render()
{
	if (animating_)
	{
		animationMat_->use(reversed_);

		// Check to see if animation has reached the end and disable it
		// if it is not set to loop
		if (!looping_)
		{
			uint8 numOfFrames = animationMat_->getNumberOfFrames();
			uint8 currentFrame = animationMat_->getCurrentFrame();

			if (numOfFrames == currentFrame + 1)
			{
				delayTracker_--;
				if (!delayTracker_)
				{
					animating_ = false;
					delayTracker_ = animationMat_->getFrameDelay();
				}			
			}
		}
	}
	else
	{
		spriteMat_->use(reversed_);
	}
	sprite_.render();
}

/*
	Name		AnimatedSprite::setUVs
	Syntax		AnimatedSprite::setUVs(CIwSVec2 &topLeft, CIwSVec2 &bottomLeft, 
				CIwSVec2 &topRight, CIwSVec2 &bottomRight)
	Param		CIwSVec2 &bottomLeft - Bottom left UV coordinates
	Param		CIwSVec2 &topLeft - Top left UV coordinates
	Param		CIwSVec2 &bottomRight - Bottom right UV coordinates
	Param		CIwSVec2 &topRight - Top right UV coordinates
	Brief		Sets the uv coordinates to be used for the sprite
*/
void AnimatedSprite::setUVs(CIwSVec2 &topLeft, CIwSVec2 &bottomLeft, 
				CIwSVec2 &topRight, CIwSVec2 &bottomRight)
{
	spriteMat_->setUVs(topLeft, bottomLeft, topRight, bottomRight);
	animationMat_->setUVs(topLeft, bottomLeft, topRight, bottomRight);
}