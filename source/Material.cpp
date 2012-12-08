/*
	Copyright	Kangaroo Magic 2011
	Created 	Elinor Townsend
	
	Name		Material
	Brief		Definitions of the methods from the Material class
*/

#include "Material.hpp"

/*
	Name		Material::Material
	Syntax		Material()
	Brief		Material constructor initialises member variables
*/
Material::Material()
{
    uvs_[0] = CIwSVec2(0<<12, 0<<12); // Top left
    uvs_[1] = CIwSVec2(0<<12, 1<<12); // Bottom left
	uvs_[2] = CIwSVec2(1<<12, 0<<12); // Top right
    uvs_[3] = CIwSVec2(1<<12, 1<<12); // Bottom right
}

/*
	Name		Material::~Material
	Syntax		~Material()
	Brief		Material destructor
*/
Material::~Material()
{

}

/*
	Name		Material::use
	Syntax		Material::use(bool reversed)
	Param		bool reversed - Flag for using mirrored texture
	Brief		Sets the material as active to be used for rendering
*/
void Material::use(bool reversed)
{
	IwGxSetMaterial(&material_);

	if (material_.GetTexture())
	{
		if (!reversed)
		{
			// Set the vertex UV stream
			IwGxSetUVStream(uvs_);
		}
		else
		{
			reversedUVs[0] = uvs_[2];
			reversedUVs[1] = uvs_[3];
			reversedUVs[2] = uvs_[0];
			reversedUVs[3] = uvs_[1];

			IwGxSetUVStream(reversedUVs);
		}
	}
}

/*
	Name		Material::setTexture
	Syntax		Material::setTexture(CIwTexture* texture)
	Param		CIwTexture* texture - Texture to set for the material
	Brief		Sets the material's texture
*/
void Material::setTexture(CIwTexture* texture)
{
	material_.SetTexture(texture);
}

/*
	Name		Material::setName
	Syntax		Material::setName(const char* name)
	Param		const char* name - Name to give the material
	Brief		Sets the material's name (used by Material Manager?)
*/
void Material::setName(const char* name)
{
	material_.SetName(name);
}

/*
	Name		Material::setUVs
	Syntax		Material::setUVs(CIwSVec2 &topLeft, CIwSVec2 &bottomLeft, 
				CIwSVec2 &topRight, CIwSVec2 &bottomRight)
	Param		CIwSVec2 &bottomLeft - Bottom left UV coordinates
	Param		CIwSVec2 &topLeft - Top left UV coordinates
	Param		CIwSVec2 &bottomRight - Bottom right UV coordinates
	Param		CIwSVec2 &topRight - Top right UV coordinates
	Brief		Sets the material's UV coordinates
*/
void Material::setUVs(CIwSVec2 &topLeft, CIwSVec2 &bottomLeft, 
				CIwSVec2 &topRight, CIwSVec2 &bottomRight)
{
	uvs_[0] = topLeft;
    uvs_[1] = bottomLeft;
	uvs_[2] = topRight;
    uvs_[3] = bottomRight;
}

/*
	Name		Material::createAnim
	Syntax		Material::createAnim() 
	Brief		Creates a UV animation structure for the material
	Details		This must be called before any other animation methods
*/
void Material::createAnim()
{
	material_.CreateAnim();
}

/*
	Name		Material::setFrameWidth
	Syntax		Material::setFrameWidth(uint8 width)
	Param		uint8 width - the width of each frame of the animation
	Brief		Sets the width of each frame of the animation
	Details		For scrolling UV animation, set width to 0x1
*/
void Material::setFrameWidth(uint8 width)
{
	material_.SetAnimCelW(width);
}

/*
	Name		Material::setFrameHeight
	Syntax		Material::setFrameHeight(uint8 height)
	Param		uint8 height - the height of each frame of the animation
	Brief		Sets the height of each frame of the animation
*/
void Material::setFrameHeight(uint8 height)
{
	material_.SetAnimCelH(height);
}

/*
	Name		Material::setFrameDelay
	Syntax		Material::setFrameDelay(uint8 delay)
	Param		uint8 delay - the time delay of each frame of the animation
	Brief		Sets the time delay of each frame of the animation
*/
void Material::setFrameDelay(uint8 delay)
{
	material_.SetAnimCelPeriod(delay);
}

/*
	Name		Material::setNumberOfFrames
	Syntax		Material::setNumberOfFrames(uint8 framesNo)
	Param		uint8 framesNo - The number of frames in the animation
	Brief		Sets the number of frames in the animation
	Details		If this is not explicitly set then the number of frames will
				be taken from the width of each frame and the size
				of the texture
*/
void Material::setNumberOfFrames(uint8 framesNo)
{
	material_.SetAnimCelNum(framesNo);
}

/*
	Name		Material::pauseAnim
	Syntax		Material::pauseAnim()
	Brief		Pauses the animation
*/
void Material::pauseAnim()
{
	material_.PauseAnim();
}

/*
	Name		Material::restartAnim
	Syntax		Material::restartAnim()
	Brief		Restarts the animation
*/
void Material::restartAnim()
{
	material_.RestartAnim();
}

/*
	Name		Material::getNumberOfFrames
	Syntax		Material::getNumberOfFrames()
	Return		The number of frames in the material's animation
	Brief		Returns the number of frames in the animation
				or 1 if no animation has been created
*/
const uint8 Material::getNumberOfFrames()
{
	if (material_.IsAnim())
	{
		return material_.GetAnimCelNum();
	}
	else
	{
		return 1;
	}
}

/*
	Name		Material::getCurrentFrame
	Syntax		Material::getCurrentFrame()
	Return		The current frame of the animation 
	Brief		Returns the current frame of the animation
				or 1 if no animation has been created
*/
const uint8 Material::getCurrentFrame()
{
	if (material_.IsAnim())
	{
		return material_.GetAnimCelID();
	}
	else
	{
		return 1;
	}
}

/*
	Name		Material::getFrameDelay
	Syntax		Material::getFrameDelay()
	Return		The number of game frames until the animation 
				frame will change
	Brief		Returns the number of game frames until the 
				animation frame will change
*/
const uint8 Material::getFrameDelay()
{
	if (material_.IsAnim())
	{
		return material_.GetAnimCelPeriod();
	}
	else
	{
		return 1;
	}
}

