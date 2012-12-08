/*
	Copyright	Kangaroo Magic 2011
	Created 	Jonathan Jones

	Name		RobotBuildingPuzzle.hpp
	Brief		Includes all the objects that make up the robot building puzzle 
*/

#ifndef ROBOT_BUILDING_PUZZLE_HPP
#define ROBOT_BUILDING_PUZZLE_HPP

// Includes
#include <Vector>
#include "Puzzle.hpp"

// Forward decelarations
class BuildPiece;
class BuildPieceSilhouette;

/*
	Name		RobotBuildingPuzzle
	Brief		Includes all the objects that make up the robot building puzzle 
*/
class RobotBuildingPuzzle : public Puzzle		// Inherits from puzzle 
{
public:
	RobotBuildingPuzzle();
	~RobotBuildingPuzzle();

	void initialise();							// Initialise objects in puzzle
	void deinitialise();						// Deinitialise objects in the puzzle
	void update();								// Update all the objects of the puzzle 
	void touchUpdate(int touchX, int touchY);	// Update that handles touch events
	void render();								// Renders all the robot parts

	bool movingABuildPiece();					// Returns true if buildPiece is being moved

	void noTouchEventsActive();					// Resets variables when no touch events are active

	void movePuzzle(int deltaX);				// Move all parts of the puzzle by delta X

	int16 getCenterX();							// Return the centre X coord of a silhouette piece

private:
	std::vector<BuildPiece*> robotParts_;					// A vector which stores all the componenets that make up the robot
	std::vector<BuildPieceSilhouette*> robotSilhouette_;	// A vector which stores all the robot parts silhouettes

	bool movingABuildPiece_;								// Bool which describes if the player is moving a robot part
	BuildPiece* buildPieceBeingMoved_;						// Pointer to build piece being moved

	const int START_X;
	const int ROBOT_HEAD_WIDTH;
	const int ROBOT_HEAD_HEIGHT;
	const int ROBOT_HEAD_X;
	const int ROBOT_HEAD_Y;
	const int ROBOT_HEAD_SILHOUETTE_WIDTH;
	const int ROBOT_HEAD_SILHOUETTE_HEIGHT;
	const int ROBOT_HEAD_SILHOUETTE_X;
	const int ROBOT_HEAD_SILHOUETTE_Y;
	const int ROBOT_TORSO_WIDTH;
	const int ROBOT_TORSO_HEIGHT;
	const int ROBOT_TORSO_X;
	const int ROBOT_TORSO_Y;
	const int ROBOT_TORSO_SILHOUETTE_WIDTH;
	const int ROBOT_TORSO_SILHOUETTE_HEIGHT;
	const int ROBOT_TORSO_SILHOUETTE_X;
	const int ROBOT_TORSO_SILHOUETTE_Y;
	const int ROBOT_LEGS_WIDTH;
	const int ROBOT_LEGS_HEIGHT;
	const int ROBOT_LEGS_X;
	const int ROBOT_LEGS_Y;
	const int ROBOT_LEGS_SILHOUETTE_WIDTH;
	const int ROBOT_LEGS_SILHOUETTE_HEIGHT;
	const int ROBOT_LEGS_SILHOUETTE_X;
	const int ROBOT_LEGS_SILHOUETTE_Y;
	const int ROBOT_POWER_CELL_WIDTH;
	const int ROBOT_POWER_CELL_HEIGHT;
	const int ROBOT_POWER_CELL_X;
	const int ROBOT_POWER_CELL_Y;
	const int ROBOT_POWER_CELL_SILHOUETTE_WIDTH;
	const int ROBOT_POWER_CELL_SILHOUETTE_HEIGHT;
	const int ROBOT_POWER_CELL_SILHOUETTE_X;
	const int ROBOT_POWER_CELL_SILHOUETTE_Y;
	const int ROBOT_LEFT_UPPER_ARM_WIDTH;
	const int ROBOT_LEFT_UPPER_ARM_HEIGHT;
	const int ROBOT_LEFT_UPPER_ARM_X;
	const int ROBOT_LEFT_UPPER_ARM_Y;
	const int ROBOT_LEFT_UPPER_ARM_SILHOUETTE_WIDTH;
	const int ROBOT_LEFT_UPPER_ARM_SILHOUETTE_HEIGHT;
	const int ROBOT_LEFT_UPPER_ARM_SILHOUETTE_X;
	const int ROBOT_LEFT_UPPER_ARM_SILHOUETTE_Y;
	const int ROBOT_RIGHT_UPPER_ARM_WIDTH;
	const int ROBOT_RIGHT_UPPER_ARM_HEIGHT;
	const int ROBOT_RIGHT_UPPER_ARM_X;
	const int ROBOT_RIGHT_UPPER_ARM_Y;
	const int ROBOT_RIGHT_UPPER_ARM_SILHOUETTE_WIDTH;
	const int ROBOT_RIGHT_UPPER_ARM_SILHOUETTE_HEIGHT;
	const int ROBOT_RIGHT_UPPER_ARM_SILHOUETTE_X;
	const int ROBOT_RIGHT_UPPER_ARM_SILHOUETTE_Y;
	const int ROBOT_LEFT_LOWER_ARM_WIDTH;
	const int ROBOT_LEFT_LOWER_ARM_HEIGHT;
	const int ROBOT_LEFT_LOWER_ARM_X;
	const int ROBOT_LEFT_LOWER_ARM_Y;
	const int ROBOT_LEFT_LOWER_ARM_SILHOUETTE_WIDTH;
	const int ROBOT_LEFT_LOWER_ARM_SILHOUETTE_HEIGHT;
	const int ROBOT_LEFT_LOWER_ARM_SILHOUETTE_X;
	const int ROBOT_LEFT_LOWER_ARM_SILHOUETTE_Y;
	const int ROBOT_RIGHT_LOWER_ARM_WIDTH;
	const int ROBOT_RIGHT_LOWER_ARM_HEIGHT;
	const int ROBOT_RIGHT_LOWER_ARM_X;
	const int ROBOT_RIGHT_LOWER_ARM_Y;
	const int ROBOT_RIGHT_LOWER_ARM_SILHOUETTE_WIDTH;
	const int ROBOT_RIGHT_LOWER_ARM_SILHOUETTE_HEIGHT;
	const int ROBOT_RIGHT_LOWER_ARM_SILHOUETTE_X;
	const int ROBOT_RIGHT_LOWER_ARM_SILHOUETTE_Y;
};

#endif 