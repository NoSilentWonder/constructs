/*
	Copyright	Kangaroo Magic 2011
	Created 	Elinor Townsend
	
	Name		Material
	Brief		Declaration of Material class
*/

#ifndef _MATERIAL_H
#define _MATERIAL_H

#include "IwGx.h"
#include "IwMaterial.h"

/*
	Name		Material class
	Brief		The Material class creates a material, and provides methods to
				set up texture, UV coordinates, animations, and animation 
				positions for this material
*/

class Material
{
public:

	Material();
	~Material();
	
	void use(bool reversed);

	void setTexture(CIwTexture* texture);
	void setName(const char* name);
	void setUVs(CIwSVec2 &topLeft, CIwSVec2 &bottomLeft, 
				CIwSVec2 &topRight, CIwSVec2 &bottomRight);
	void createAnim();
	void setFrameWidth(uint8 width);
	void setFrameHeight(uint8 height);
	void setFrameDelay(uint8 delay);
	void setNumberOfFrames(uint8 framesNo);

	void pauseAnim();
	void restartAnim();

	const uint8 getNumberOfFrames();
	const uint8 getCurrentFrame();
	const uint8 getFrameDelay();

	CIwMaterial* getMaterial() { return &material_; };

private:
	CIwMaterial material_;
	CIwSVec2 uvs_[4];
	CIwSVec2 reversedUVs[4];
};

#endif // _MATERIAL_H