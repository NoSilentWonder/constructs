// Puzzle.hpp 

#ifndef PUZZLE_HPP
#define PUZZLE_HPP

#include "s3eTypes.h"

class Puzzle
{
public:
	Puzzle(): complete_(false) {}
	virtual ~Puzzle() {}

	virtual void initialise() = 0;
	virtual void deinitialise() = 0;
	virtual void update() = 0;
	//virtual void independentUpdate(float deltaTime) = 0; 
	virtual void render() = 0;
	void setComplete() { complete_ = true; } 
	bool isComplete() { return complete_; }
	virtual void movePuzzle(int deltaX) = 0;
	virtual int16 getCenterX() = 0;
private:
	bool complete_;
};

#endif // PUZZEL_HPP