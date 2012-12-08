/*
	Copyright	Kangaroo Magic 2011
	Created 	Elinor Townsend
	
	Name		ScrollingLayer
	Brief		Definitions of methods for ScrollingLayer class
*/
#include <algorithm>
#include <cmath>
#include "ScrollingLayer.hpp"
#include "Quad.hpp"

/*
	Name		ScrollingLayer::ScrollingLayer
	Syntax		ScrollingLayer()
	Brief		ScrollingLayer constructor initialises member variables
*/
ScrollingLayer::ScrollingLayer()
	: tileTextures_(0), map_(0), displayedTile_(0), texturesNo_(0), 
	  mapWidth_(15), mapDisplayWidth_(3), mapPosition_(0), mapDeltaX_(0), 
	  mapOffsetX_(0), mapOffsetY_(0), tileWidth_(500), tileHeight_(500),
	  isScrollingLeft_(true), isScrollingRight_(true)
	  
{

}

/*
	Name		ScrollingLayer::~ScrollingLayer
	Syntax		~ScrollingLayer()
	Brief		ScrollingLayer denstructor
*/
ScrollingLayer::~ScrollingLayer()
{

}

/*
	Name		ScrollingLayer::initialise
	Syntax		ScrollingLayer::initialise(const char *filename)
	Param		const char *filename - The name of the file to read scrolling layer 
				data from
	Brief		Initialises the ScrollingLayer, setting sizes for tileTextures_, map_ and 
				displayedTiles_ dynamic arrays and creates the tiles
*/
void ScrollingLayer::initialise(const char* filename)
{
	int maxLength = 100;
	char aString[100];
	char str[100];
	int texNo = 0;
	int mapW = 0;
	int displayW = 0;
	int tileW = 0;
	int tileH = 0;
	int mapPos = 0;
	int offsetX = 0;
	int offsetY = 0;
	int ch = 0;
	int decorativeNo = 0;
	int interactiveNo = 0;
	int spriteMapPos = 0;
	int spriteWidth = 0;
	int spriteHeight = 0;
	int spriteX = 0;
	int spriteY = 0;

	s3eFile* file = s3eFileOpen(filename, "rb");

	if (file != NULL)
	{
		// Retrieve number of textures from file
		s3eFileReadString (aString, maxLength, file);
		sscanf(aString, "Number of Textures: %d\n", &texNo);
		texturesNo_ = texNo;
		tileTextures_ = new CIwTexture*[texturesNo_];

		// Create textures using string names from file
		for (int i = 0; i < texturesNo_; ++i)
		{
			s3eFileReadString (aString, maxLength, file);
			ch = 0;
			while ((aString[ch] != '\n') && (aString[ch] != '\r'))
			{
				str[ch] = aString[ch];
				ch++;
			}
			str[ch] = '\0';
			// Create texture
			tileTextures_[i] =  new CIwTexture;
			tileTextures_[i]->LoadFromFile(str);
			tileTextures_[i]->Upload();
		}

		// Empty line to make script more readable
		s3eFileReadString(aString, maxLength, file);

		// Get the map size
		s3eFileReadString (aString, maxLength, file);
		sscanf(aString, "Map size: %d\n", &mapW);
		mapWidth_ = mapW;
		map_ = new int[mapWidth_];
		int mapValue = 0;
		// Load in all the map values used for referencing textures
		for (int i = 0; i < mapWidth_; ++i)
		{
			s3eFileReadString (aString, maxLength, file);
			sscanf(aString, "%d\n", &mapValue);
			map_[i] = mapValue;
		}

		// Empty line to make script more readable
		s3eFileReadString(aString, maxLength, file);

		// Get number of displayed tiles
		s3eFileReadString (aString, maxLength, file);
		sscanf(aString, "Number of displayed tiles: %d\n", &displayW);
		mapDisplayWidth_ = displayW;

		// Get tile dimensions
		s3eFileReadString (aString, maxLength, file);
		sscanf(aString, "Tile width: %d\n", &tileW);
		tileWidth_ = tileW;
		s3eFileReadString (aString, maxLength, file);
		sscanf(aString, "Tile height: %d\n", &tileH);
		tileHeight_ = tileH;

		// Create quad
		displayedTile_ = new Quad(0, 0, 0, tileWidth_, tileHeight_, 0);

		// Starting position
		s3eFileReadString (aString, maxLength, file);
		sscanf(aString, "Starting position: %d\n", &mapPos); // Left-most visible tile
		mapPosition_ = mapPos;

		// Offsets
		s3eFileReadString (aString, maxLength, file);
		sscanf(aString, "Screen offset: %d, %d\n", &offsetX, &offsetY); 
		mapOffsetX_ = offsetX;
		mapOffsetY_ = offsetY;

		// Empty line to make script more readable
		s3eFileReadString(aString, maxLength, file);

		// Decorative sprites
		s3eFileReadString (aString, maxLength, file);
		sscanf(aString, "Number of decorative sprites: %d\n", &decorativeNo);
		decorativeSprites_.reserve(decorativeNo);

		// Create the decorative sprites using data from the file
		for (int i = 0; i < decorativeNo; ++i)
		{
			// Empty line to make script more readable
			s3eFileReadString(aString, maxLength, file);

			// Create a sprite entry
			decorativeSprites_.push_back(SpriteEntry());

			// Read the sprite's settings from the file
			// Map position
			s3eFileReadString (aString, maxLength, file);
			sscanf(aString, "map position: %d\n", &spriteMapPos);
		
			// Width
			s3eFileReadString (aString, maxLength, file);
			sscanf(aString, "sprite width: %d\n", &spriteWidth);

			// Height
			s3eFileReadString (aString, maxLength, file);
			sscanf(aString, "sprite height: %d\n", &spriteHeight);

			// X
			s3eFileReadString (aString, maxLength, file);
			sscanf(aString, "x offset: %d\n", &spriteX);

			// Y
			s3eFileReadString (aString, maxLength, file);
			sscanf(aString, "y offset: %d\n", &spriteY);

			// Texture
			s3eFileReadString (aString, maxLength, file);

			// Set the entry's map position and initialise the sprite
			decorativeSprites_.back().mapPosition_ = spriteMapPos;
			decorativeSprites_.back().offsetX_ = spriteX;
			decorativeSprites_.back().offsetY_ = spriteY;
			decorativeSprites_.back().sprite_.initialise(aString, spriteWidth, spriteHeight, 0, 0);
		}

		// Empty line to make script more readable
		s3eFileReadString(aString, maxLength, file);

		// Interactive sprites
		s3eFileReadString (aString, maxLength, file);
		sscanf(aString, "Number of interactive sprites: %d\n", &interactiveNo);
		interactiveSprites_.reserve(interactiveNo);

		// Create the interactive sprites using data from the file
		for (int i = 0; i < interactiveNo; ++i)
		{
			// Empty line to make script more readable
			s3eFileReadString(aString, maxLength, file);

			// Create a sprite entry
			interactiveSprites_.push_back(AnimatedSpriteEntry());

			// Read the sprite's settings from the file
			// Map position
			s3eFileReadString (aString, maxLength, file);
			sscanf(aString, "map position: %d\n", &spriteMapPos);
		
			// Width
			s3eFileReadString (aString, maxLength, file);
			sscanf(aString, "sprite width: %d\n", &spriteWidth);

			// Height
			s3eFileReadString (aString, maxLength, file);
			sscanf(aString, "sprite height: %d\n", &spriteHeight);

			// X
			s3eFileReadString (aString, maxLength, file);
			sscanf(aString, "x offset: %d\n", &spriteX);

			// Y
			s3eFileReadString (aString, maxLength, file);
			sscanf(aString, "y offset: %d\n", &spriteY);

			// Texture
			s3eFileReadString (aString, maxLength, file);

			// Set the entry's map position and initialise the sprite
			interactiveSprites_.back().mapPosition_ = spriteMapPos;
			interactiveSprites_.back().offsetX_ = spriteX;
			interactiveSprites_.back().offsetY_ = spriteY;
			interactiveSprites_.back().sprite_.initialise(aString, spriteWidth, spriteHeight, 0, 0);
		}
		
		s3eFileClose(file);
	}
	else
	{
		s3eFileGetError();
		s3eDebugOutputString(s3eFileGetErrorString());
	}

	// Set uv coordinates
	uvs_[0] = CIwSVec2(0<<12, 0<<12); // Top left
    uvs_[1] = CIwSVec2(0<<12, 1<<12); // Bottom left
	uvs_[2] = CIwSVec2(1<<12, 0<<12); // Top right
    uvs_[3] = CIwSVec2(1<<12, 1<<12); // Bottom right
}

/*
	Name		ScrollingLayer::deinitialise
	Syntax		ScrollingLayer::deinitialise()
	Brief		Deinitialises the ScrollingLayer - Deletes all dynamic arrays and
				pointers
*/
void ScrollingLayer::deinitialise()
{	
	if (tileTextures_)
	{
		for (int i = 0; i < texturesNo_; ++i)
		{
			delete tileTextures_[i];
		}
		delete [] tileTextures_;
		tileTextures_ = 0;
	}

	if (map_)
	{
		delete [] map_;
		map_ = 0;
	}

	if (displayedTile_)
	{
		delete displayedTile_;
		displayedTile_ = 0;
	}

	while (!decorativeSprites_.empty())
	{
//		decorativeSprites_.back().sprite_.deinitialise();
		decorativeSprites_.pop_back();
	}

	while (!interactiveSprites_.empty())
	{
		interactiveSprites_.back().sprite_.deinitialise();
		interactiveSprites_.pop_back();
	}
}

/*
	Name		ScrollingLayer::update
	Syntax		ScrollingLayer::update(int16 deltaX)
	Param		int16 deltaX - Change in x-position of layer
	Brief		Updates the layer with change in position
*/
void ScrollingLayer::update(int16 deltaX)
{
	isScrollingLeft_ = true;
	isScrollingRight_ = true;

	mapDeltaX_ += deltaX;
	
	int positionChange = 0;

	if (mapDeltaX_ >= tileWidth_)
	{
		positionChange = -1;
		mapDeltaX_ -= tileWidth_;
	}
	else if (mapDeltaX_ <= -tileWidth_)
	{
		positionChange = 1;
		mapDeltaX_ += tileWidth_;
	}

	mapPosition_ = std::max(std::min(mapPosition_ + positionChange, mapWidth_ - mapDisplayWidth_), 0);

	// Stop scrolling if the edge of the map has been reached
	if (mapPosition_ == (mapWidth_ - mapDisplayWidth_))
	{
		if (mapDeltaX_ < 0)
		{
			mapDeltaX_ = 0;
		}
		isScrollingRight_ = false;
	}

	if (mapPosition_ == 0)
	{
		if (mapDeltaX_ > 0)
		{
			mapDeltaX_ = 0;
		}
		isScrollingLeft_ = false;
	}
}

/*
	Name		ScrollingLayer::render
	Syntax		ScrollingLayer::render()
	Brief		Renders the visible portion of the scrolling
				layer
*/
void ScrollingLayer::render()
{
	CIwMaterial* material;
	int16 posX = 0;

	for (int x = 0; x < mapDisplayWidth_; ++x)
	{
		posX = (x * tileWidth_) + mapDeltaX_ + mapOffsetX_;
		
		// Allocate and initialise a material
		material = IW_GX_ALLOC_MATERIAL();
		// Set the diffuse map
		material->SetTexture(tileTextures_[map_[x + mapPosition_]]);
		// Set as active material
		IwGxSetMaterial(material);

		// Set the vertex UV stream
		IwGxSetUVStream(uvs_);

		displayedTile_->moveTo(posX, mapOffsetY_);
		displayedTile_->render();
	}

	std::vector<SpriteEntry>::iterator iter;
	for (iter = decorativeSprites_.begin(); iter != decorativeSprites_.end(); ++iter)
	{
		for (int x = 0; x < mapDisplayWidth_; ++x)
		{
			if (iter->mapPosition_ == (x + mapPosition_))
			{
				posX = (x * tileWidth_) + mapDeltaX_ + mapOffsetX_ + iter->offsetX_;
				int16 posY = mapOffsetY_ + iter->offsetY_;
				iter->sprite_.moveTo(posX, posY);
				iter->sprite_.render();
			}
		}
	}
}

/*
	Name		ScrollingLayer::positionMap
	Syntax		ScrollingLayer::positionMap(int mapPosition)
	Param		int mapPosition - position in map
	Brief		Sets the current starting position for displayed tiles
				in the map
*/
void ScrollingLayer::positionMap(int mapPosition)
{
	mapPosition_ = mapPosition;
}

/*
	Name		ScrollingLayer::setMapOffsets
	Syntax		ScrollingLayer::setMapOffsets(int16 offsetX, int16 offsetY)
	Param		int16 offsetX - Screen position offset from 0 on the x-axis
	Param		int16 offsetY - Screen position offset from 0 on the y-axis
	Brief		Sets the screen position offset from (0, 0) to be applied to
				the ScrollingLayer
	Details		The offset coordinates should position the centre of the 
				left-most displayed tile of the scrolling layer in the correct
				position
*/
void ScrollingLayer::setMapOffsets(int16 offsetX, int16 offsetY)
{
	mapOffsetX_ = offsetX;
	mapOffsetY_ = offsetY;
}

/*
	Name		ScrollingLayer::tileIsBeingRendered
	Syntax		ScrollingLayer::tileIsBeingRendered(int tileNo)
	Param		int tileNo - Tile to check
	Return		Bool - if tile is currently in the rendered section of the layer
	Brief		Checks if a given tile is in the rendered section of the scrolling layer
*/
bool ScrollingLayer::tileIsBeingRendered(int tileNo)
{
	if ((tileNo >= mapPosition_) && (tileNo < (mapPosition_ + mapDisplayWidth_)))
		return true;
	else
		return false;
}