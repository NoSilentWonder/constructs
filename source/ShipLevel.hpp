/*
	Copyright	Kangaroo Magic 2011
	Created 	Jonathan Jones
	
	Name		ShipLevel
	Brief		Definition of ShipLevel class methods
*/

#ifndef SHIP_LEVEL_HPP
#define SHIP_LEVEL_HPP

// Includes
#include <vector>
#include "Level.hpp"
#include "RobotBuildingPuzzle.hpp"
#include "CircularButton.hpp"
#include "Sprite.hpp"

// Forward declerations
class Alien;
class Robot;
class Input;
class BuildPiece;
class SoundEffect;
class Video;

/*
	Name	ShipLevel
	Brief	Contains all the objects associated with the ship level and its methods
*/
class ShipLevel : public Level
{
public:
	ShipLevel(Alien* alien, Robot* robot, Input* input);	// Give initial values to member variables using an init list
	~ShipLevel();											// Deinitialise ship level
	void initialise();										// Initialise ship level elements
	void deinitialise();									// Deinitialise elements in the ship level
	void update();											//
	void independentUpdate(float deltaTime);				// Update any items that rely on delta time
	void render();											// Draw the objects in the scene
	int getNextLevel();
private:
	float deadZone_;

	RobotBuildingPuzzle robotBuildingPuzzle_;

	CircularButton* nextLevelButton_;

	int nextLevel_;

	bool setRobotX;
	Sprite background_;
	SoundEffect* ambientSound_;

	Video* activates_;
	bool activatesPlaying_;
	bool activatesPlayed_;
};

#endif // SHIP_LEVEL_HPP