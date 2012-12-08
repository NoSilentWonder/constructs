/*
	Copyright	Kangaroo Magic 2011
	Created 	Elinor Townsend
	
	Name		ScrollingLayer
	Brief		Declaration of ScrollingLayer class
*/

#ifndef _SCROLLING_LAYER_H
#define _SCROLLING_LAYER_H

#include <vector>
#include "IwGx.h"
#include "Sprite.hpp"
#include "AnimatedSprite.hpp"

class Quad;

/*
	Name		MappedSpriteEntry struct
	Brief		Struct to pair a Sprite object with a value giving
				its position in a map
*/
struct SpriteEntry 
{
	int mapPosition_;
	int offsetX_;
	int offsetY_;
	Sprite sprite_;
	~SpriteEntry() 
	{
		sprite_.deinitialise();
	}
};

/*
	Name		MappedAnimatedSpriteEntry struct
	Brief		Struct to pair an AnimatedSprite object with a value giving
				its position in a map
*/
struct AnimatedSpriteEntry 
{
	int mapPosition_;
	int offsetX_;
	int offsetY_;
	AnimatedSprite sprite_;
};

/*
	Name		ScrollingLayer class
	Brief		The ScrollingLayer class creates a scrolling tiled
				layer used for parallax scrolling within levels
*/

class ScrollingLayer
{
public:
	ScrollingLayer();
	~ScrollingLayer();

	void initialise(const char* filename);
	void deinitialise();

	void update(int16 deltaX);
	void render();

	void positionMap(int mapPosition);
	void setMapOffsets(int16 offsetX, int16 offsetY);

	bool isScrollingLeft() const { return isScrollingLeft_; }
	bool isScrollingRight() const { return isScrollingRight_; }

	bool tileIsBeingRendered(int tileNo);

private:
	CIwTexture** tileTextures_;
	int* map_;
	Quad* displayedTile_;
	std::vector<SpriteEntry> decorativeSprites_;
	std::vector<AnimatedSpriteEntry> interactiveSprites_;

	int texturesNo_;

	int mapWidth_;
	int mapDisplayWidth_;	
	int mapPosition_;
	int16 mapDeltaX_;

	int16 mapOffsetX_;
	int16 mapOffsetY_;
	
	int16 tileWidth_;
	int16 tileHeight_;

	bool isScrollingLeft_;
	bool isScrollingRight_;

	CIwSVec2 uvs_[4];
};

#endif // _SCROLLING_LAYER_H