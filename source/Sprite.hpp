/*
	Copyright	Kangaroo Magic 2011
	Created 	Elinor Townsend
	
	Name		Sprite
	Brief		Declaration of Sprite class
*/

#ifndef _SPRITE_HPP
#define _SPRITE_HPP

#include "s3eTypes.h"
#include "IwGx.h"
#include "Quad.hpp"
#include "Material.hpp"

/*
	Name		Sprite class
	Brief		The Sprite class creates a quad, material, and 
				texture used to create a static sprite and provides 
				methods for creating and positioning the sprite
*/
class Sprite
{
public:
	Sprite();
	~Sprite();
	void initialise(char* fileName, int16 width, 
					int16 height, int16 posX, int16 posY);
	void deinitialise();
	void render();
	void renderPerspective();
	void moveTo(const int16 x, const int16 y);
	void setDimensions(const int16 width, const int16 height);
	void moveDeltaX(const int16 x);
	void moveDeltaY(const int16 y);
	void setZ(const int16 z);	
	void setRotation(const int16 angle);
	void scale(const int16 scale);  
	void setUVs(CIwSVec2 &topLeft, CIwSVec2 &bottomLeft, 
				CIwSVec2 &topRight, CIwSVec2 &bottomRight);
	void reverse();
	int16 getX();
	int16 getY();
	int16 getZ();
	int16 getWidth();
	int16 getHeight();	
	void turnAlphaOn();
protected:
	Quad sprite_;
	CIwTexture* spriteTex_;
    Material* spriteMat_;
	bool reversed_;
};

#endif	// _SPRITE_HPP