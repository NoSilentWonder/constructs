/*
	Copyright	Kangaroo Magic 2011
	Created 	Elinor Townsend
	
	Name		Sprite
	Brief		Definition of the methods of Sprite class
*/

#include "Sprite.hpp"

/*
	Name		Sprite::Sprite
	Syntax		Sprite()
	Brief		Sprite constructor initialises member variables
*/
Sprite::Sprite()
	: reversed_(false), spriteMat_(0), spriteTex_(0)
{

}

/*
	Name		Sprite::~Sprite
	Syntax		~Sprite()
	Brief		Sprite destructor 
*/
Sprite::~Sprite()
{

}

/*
	Name		Sprite::initiailise
	Syntax		Sprite::initialise(char* fileName, int16 width, 
								   int16 height, int16 posX, int16 posY)
	Param		char* fileName - The name of the texture resource used for the sprite
	Param		int16 width - Width of the sprite
	Param		int16 height - Height of the sprite
	Param		int16 posX - x-position to set for sprite
	Param		int16 posY - y-position to set for sprite
	Brief		Initialises the sprite by setting up the texture and material and
				setting the dimensions and initial position of the sprite quad
*/
void Sprite::initialise(char* fileName, int16 width, 
						int16 height, int16 posX, int16 posY)
{
	// Create sprite texture
	spriteTex_ = new CIwTexture;
	spriteTex_->LoadFromFile(fileName);
	spriteTex_->Upload();

	// Create the material and set it to the sprite texture
	spriteMat_ = new Material;
    spriteMat_->setTexture(spriteTex_);

	// Set up sprite quad
	sprite_.setDimensions(width, height);
	sprite_.moveTo(posX, posY);

	//spriteMat_->getMaterial()->SetAlphaMode(CIwMaterial::ALPHA_HALF);
}

/*
	Name		Sprite::deinitialise
	Syntax		Sprite::deinitialise()
	Brief		Deinitialises the sprite
*/
void Sprite::deinitialise()
{
	if (spriteMat_)
	{
		delete spriteMat_;
		spriteMat_ = 0;
	}

	if (spriteTex_)
	{
		delete spriteTex_;
		spriteTex_ = 0;
	}
}

/*
	Name		Sprite::render
	Syntax		Sprite::render()
	Brief		Renders the sprite
*/
void Sprite::render()
{
	spriteMat_->use(reversed_);
	sprite_.render();
}

/*
	Name		Sprite::renderPerspective
	Syntax		Sprite::renderPerspective()
	Brief		Renders the sprite scaled based on the z-position
				of its quad
*/
void Sprite::renderPerspective()
{
	spriteMat_->use(reversed_);
	sprite_.renderPerspective();
}

/*
	Name		Sprite::moveTo
	Syntax		Sprite::moveTo(const int16 x, const int16 y)
	Param		int16 x - X-position to move sprite to
	Param		int16 y - Y-position to move sprite to
	Brief		Sets the x- and y-position of the sprite
*/
void Sprite::moveTo(const int16 x, const int16 y)
{
	sprite_.moveTo(x, y);
}

/*
	Name		Sprite::setDimensions
	Syntax		Sprite::setDimensions(const int16 width, const int16 height)
	Param		int16 width - Width to set for the sprite
	Param		int16 height - Height to set for the sprite
	Brief		Sets the dimensions of the sprite
*/
void Sprite::setDimensions(const int16 width, const int16 height)
{
	sprite_.setDimensions(width, height);
}

/*
	Name		Sprite::moveDeltaX
	Syntax		Sprite::moveDeltaX(const int16 x)
	Param		int16 x - Value to change the x-position of the sprite by
	Brief		Increases the sprite's x-position by x
*/
void Sprite::moveDeltaX(const int16 x)
{
	sprite_.moveDeltaX(x);
}

/*
	Name		Sprite::moveDeltaY
	Syntax		Sprite::moveDeltaY(const int16 y)
	Param		int16 y - Value to change the y-position of the sprite by
	Brief		Increases the sprite's y-position by y
*/
void Sprite::moveDeltaY(const int16 y)
{
	sprite_.moveDeltaY(y);
}

/*
	Name		Sprite::setZ
	Syntax		Sprite::setZ(const int16 z)
	Param		int16 z - Value to set the z-position of the sprite to
	Brief		Sets the z-position of the sprite
*/
void Sprite::setZ(const int16 z)
{
	sprite_.setZ(z);
}

/*
	Name		Sprite::setRotation
	Syntax		Sprite::setRotation(const int16 angle)
	Param		int16 angle - Angle to set the sprite to
	Brief		Sets the angle of rotation of the sprite
*/
void Sprite::setRotation(const int16 angle)
{
	sprite_.setRotation(angle);
}

/*
	Name		Sprite::scale
	Syntax		Sprite::scale(const int16 scale)
	Param		int16 scale - Factor to scale the sprite by
	Brief		Scales the dimensions of the sprite
*/
void Sprite::scale(const int16 scale)
{
	sprite_.scale(scale);
}

/*
	Name		Sprite::setUVs
	Syntax		Sprite::setUVs(CIwSVec2 &topLeft, CIwSVec2 &bottomLeft, 
				CIwSVec2 &topRight, CIwSVec2 &bottomRight)
	Param		CIwSVec2 &bottomLeft - Bottom left UV coordinates
	Param		CIwSVec2 &topLeft - Top left UV coordinates
	Param		CIwSVec2 &bottomRight - Bottom right UV coordinates
	Param		CIwSVec2 &topRight - Top right UV coordinates
	Brief		Sets the uv coordinates to be used for the sprite
*/
void Sprite::setUVs(CIwSVec2 &topLeft, CIwSVec2 &bottomLeft, 
				CIwSVec2 &topRight, CIwSVec2 &bottomRight)
{
	spriteMat_->setUVs(topLeft, bottomLeft, topRight, bottomRight);
}

/*
	Name		Sprite::reverse
	Syntax		Sprite::reverse()
	Brief		Toggle the reversed_ boolean used to reverse the uv 
				coordinates being used to render the sprite
*/
void Sprite::reverse()
{
	reversed_ = 1 - reversed_;
}

/*
	Name		Sprite::getX
	Syntax		Sprite::getX()
	Return		int16 - x-position
	Brief		Returns the x-position of the centre of the sprite
*/
int16 Sprite::getX()
{
	return sprite_.getX();
}

/*
	Name		Sprite::getY
	Syntax		Sprite::getY()
	Return		int16 - y-position
	Brief		Returns the y-position of the centre of the sprite
*/
int16 Sprite::getY()
{
	return sprite_.getY();
}

/*
	Name		Sprite::getZ
	Syntax		Sprite::getZ()
	Return		int16 - z-position
	Brief		Returns the z-position of the centre of the sprite
*/
int16 Sprite::getZ()
{
	return sprite_.getZ();
}

/*
	Name		Sprite::getWidth
	Syntax		Sprite::getWidth()
	Return		int16 - width
	Brief		Returns the width of the sprite
*/
int16 Sprite::getWidth()
{
	return sprite_.getWidth();
}

/*
	Name		Sprite::getHeight
	Syntax		Sprite::getHeight()
	Return		int16 - height
	Brief		Returns the height of the sprite
*/
int16 Sprite::getHeight()
{
	return sprite_.getHeight();
}

/*
	Name		Sprite::turnAlphaOn
	Syntax		Sprite::turnAlphaOn()
	Brief		Turn alpha on for the sprite
*/
void Sprite::turnAlphaOn()
{
	spriteMat_->getMaterial()->SetAlphaMode(CIwMaterial::ALPHA_ADD);
}