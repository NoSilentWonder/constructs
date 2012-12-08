/*
	Copyright	Kangaroo Magic 2011
	Created 	Jonathan Jones
	
	Name		Level
	Brief		Definition of Level class virtual methods
*/

#ifndef LEVEL_HPP
#define LEVEL_HPP

// Includes 
//#include "Alien.hpp"
//#include "Robot.hpp"
//#include "Input.hpp"
class Alien;
class Robot;
class Input;

/*
	Name	Level
	Brief	Base class for all levels
*/
class Level
{
public:
	Level(Alien* alien, Robot* robot, Input* input): alien_(alien)
												   , robot_(robot)
												   , input_(input)
												   , screenWidth_(0)
												   , screenHeight_(0)
												   , moveToNextLevel_(false)  {}
	virtual ~Level() {}
	virtual void initialise() = 0;
	virtual void deinitialise() = 0;
	virtual void update() = 0;
	virtual void independentUpdate(float deltaTime) = 0; 
	virtual void render() = 0;

	Alien* alien() const { return alien_; }
	Robot* robot() const { return robot_; }
	Input* input() const { return input_; }
	int screenWidth() const { return screenWidth_; }
	int screenHeight() const { return screenHeight_; }
	void setScreenHeight(int screenHeight) { screenHeight_ = screenHeight; }
	void setScreenWidth( int screenWidth ) { screenWidth_ = screenWidth; }
	bool moveToNextLevel() const { return moveToNextLevel_; }
	void playerExitingLevel() { moveToNextLevel_ = true; }
	virtual int getNextLevel() = 0;
	void playerMovedLevel() { moveToNextLevel_ = false; }

private:
	Alien* alien_;														// Pointer to the alien object
	Robot* robot_;														// Pointer to the robot object
	Input* input_;
	int screenWidth_;
	int screenHeight_;
	bool moveToNextLevel_;
};

#endif // LEVEL_HPP