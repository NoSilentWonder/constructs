/*
	Copyright	Kangaroo Magic 2011
	Created 	Jonathan Jones
	Modified	Karl Inglott

	Name		EscapePodBuildingPuzzle.hpp
	Brief		Includes all the objects that make up the escape pod building puzzle 
*/

#ifndef ESCAPE_POD_BUILDING_PUZZLE_HPP
#define ESCAPE_POD_BUILDING_PUZZLE_HPP

// Includes
#include <Vector>
#include "Puzzle.hpp"

// Forward decelarations
class BuildPiece;
class BuildPieceSilhouette;

/*
	Name		EscapePodBuildingPuzzle.hpp
	Brief		Includes all the objects that make up the escape pod building puzzle 
*/
class EscapePodBuildingPuzzle : public Puzzle
{
public:
	EscapePodBuildingPuzzle();
	~EscapePodBuildingPuzzle();

	void initialise();
	void deinitialise();
	void update();
	void render();

	void movePuzzle(int deltaX);
	int16 getCenterX();

	void touchUpdate(int touchX, int touchY);
	bool movingABuildPiece();	
	void noTouchEventsActive();					
private:
	std::vector<BuildPiece*> escapePodParts_;
	std::vector<BuildPieceSilhouette*> escapePodPartsSilhouettes_;

	const int START_X;
	const int START_Y;
	const int LEFT_THRUSTER_X;
	const int LEFT_THRUSTER_Y;
	const int LEFT_THRUSTER_WIDTH;
	const int LEFT_THRUSTER_HEIGHT;
	const int LEFT_THRUSTER_SILHOUETTE_X;
	const int LEFT_THRUSTER_SILHOUETTE_Y;
	const int LEFT_THRUSTER_SILHOUETTE_WIDTH;
	const int LEFT_THRUSTER_SILHOUETTE_HEIGHT;
	const int RIGHT_THRUSTER_X;
	const int RIGHT_THRUSTER_Y;
	const int RIGHT_THRUSTER_WIDTH;
	const int RIGHT_THRUSTER_HEIGHT;
	const int RIGHT_THRUSTER_SILHOUETTE_X;
	const int RIGHT_THRUSTER_SILHOUETTE_Y;
	const int RIGHT_THRUSTER_SILHOUETTE_WIDTH;
	const int RIGHT_THRUSTER_SILHOUETTE_HEIGHT;
	const int POD_BOTTOM_RIGHT_X;
	const int POD_BOTTOM_RIGHT_Y;
	const int POD_BOTTOM_RIGHT_WIDTH;
	const int POD_BOTTOM_RIGHT_HEIGHT;
	const int POD_BOTTOM_RIGHT_SILHOUETTE_X;
	const int POD_BOTTOM_RIGHT_SILHOUETTE_Y;
	const int POD_BOTTOM_RIGHT_SILHOUETTE_WIDTH;
	const int POD_BOTTOM_RIGHT_SILHOUETTE_HEIGHT;
	const int POD_BOTTOM_LEFT_X;
	const int POD_BOTTOM_LEFT_Y;
	const int POD_BOTTOM_LEFT_WIDTH;
	const int POD_BOTTOM_LEFT_HEIGHT;
	const int POD_BOTTOM_LEFT_SILHOUETTE_X;
	const int POD_BOTTOM_LEFT_SILHOUETTE_Y;
	const int POD_BOTTOM_LEFT_SILHOUETTE_WIDTH;
	const int POD_BOTTOM_LEFT_SILHOUETTE_HEIGHT;
	const int POD_TOP_RIGHT_X;
	const int POD_TOP_RIGHT_Y;
	const int POD_TOP_RIGHT_WIDTH;
	const int POD_TOP_RIGHT_HEIGHT;
	const int POD_TOP_RIGHT_SILHOUETTE_X;
	const int POD_TOP_RIGHT_SILHOUETTE_Y;
	const int POD_TOP_RIGHT_SILHOUETTE_WIDTH;
	const int POD_TOP_RIGHT_SILHOUETTE_HEIGHT;
	const int POD_TOP_LEFT_X;
	const int POD_TOP_LEFT_Y;
	const int POD_TOP_LEFT_WIDTH;
	const int POD_TOP_LEFT_HEIGHT;
	const int POD_TOP_LEFT_SILHOUETTE_X;
	const int POD_TOP_LEFT_SILHOUETTE_Y;
	const int POD_TOP_LEFT_SILHOUETTE_WIDTH;
	const int POD_TOP_LEFT_SILHOUETTE_HEIGHT;
	const int POD_WINDOW_X;
	const int POD_WINDOW_Y;
	const int POD_WINDOW_WIDTH;
	const int POD_WINDOW_HEIGHT;
	const int POD_WINDOW_SILHOUETTE_X;
	const int POD_WINDOW_SILHOUETTE_Y;
	const int POD_WINDOW_SILHOUETTE_WIDTH;
	const int POD_WINDOW_SILHOUETTE_HEIGHT;

	bool movingABuildPiece_;
	BuildPiece* buildPieceBeingMoved_;
};

#endif	// ESCAPE_POD_BUILDING_PUZZLE_HPP