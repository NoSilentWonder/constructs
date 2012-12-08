/*
	Copyright	Kangaroo Magic 2011
	Created 	Jonathan Jones
	
	Name		ShipBuildingArea
	Brief		Definition of ShipBuildingArea class methods
*/

#ifndef SHIP_BUILDING_AREA_HPP
#define SHIP_BUILDING_AREA_HPP

// Includes
#include "Level.hpp"
//#include "MusicPlayer.hpp"
//#include "ScrollingLayer.hpp"
#include "LevelList.hpp"
#include "ScrollingLayer.hpp"
#include "EscapePodBuildingPuzzle.hpp"
#include "ScrollingLayer.hpp"


// Forward declerations
class Alien;
class Robot;
class Input;
class SoundEffect;
class Video;

/*
	Name	ShipBuildingArea
	Brief	Contains all the objects associated with the ship building area level and its methods
*/
class ShipBuildingArea : public Level
{
public:
	ShipBuildingArea(Alien* alien, Robot* robot, Input* input);	// Give initial values to member variables using an init list
	~ShipBuildingArea();										// Deinitialise elements in the level
	void initialise();											// Initialise level elements
	void deinitialise();										// Deinitialise elements in the ship level
	void update();												// 
	void independentUpdate(float deltaTime);					// Update any items that rely on delta time
	void render();												// Draw the objects in the scene
	int getNextLevel();
	void playerEnteringFromLevel1();
private:
	SoundEffect* ambientSound_;
	EscapePodBuildingPuzzle escapePodBuildingPuzzle_;

	const float SCROLL_SPEED;
	float deadZone_;
	ScrollingLayer sky_;
	ScrollingLayer distantBackground_;
	ScrollingLayer closeBackground_;
	ScrollingLayer midground_;
	ScrollingLayer playerStage_;
	ScrollingLayer foreground_;

	int nextLevel_;

	int16 offsetFromEscapePod;

	Video* ending_;

	bool secondPass_;

	bool endingPlayed_;
};

#endif // SHIP_BUILDING_AREA_HPP