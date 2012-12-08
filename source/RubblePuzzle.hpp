// RubblePuzzle.hpp

#ifndef RUBBLE_PUZZLE_HPP
#define RUBBLE_PUZZLE_HPP

#include "Puzzle.hpp"
#include <vector>

class FlickableObject;
struct Touch;

class RubblePuzzle : public Puzzle
{
public:
	RubblePuzzle();
	~RubblePuzzle();
	void initialise();
	void deinitialise();
	void update();
	void touchUpdate(Touch* touch);
	void setSecondTouch(Touch* touch);
	void touchCountZero();
	void render();
	void movePuzzle(int deltaX);
	int16 getCenterX();
	bool getPieceBeingTouched();
private:
	std::vector<FlickableObject*> rocks_;
	Touch* firstTouch_;
	Touch* secondTouch_;
	bool firstTouchSet_;
};
#endif // RUBBLE_PUZZLE_HPP