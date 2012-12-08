/*
	Copyright	Kangaroo Magic 2011
	Created 	Jonathan Jones
	
	Name		Level1.hpp
	Brief		Contains everything in level 1
*/

#ifndef LEVEL_1_HPP
#define LEVEL_1_HPP

#include "Level.hpp"
#include "ScrollingLayer.hpp"
#include "RubblePuzzle.hpp"

class Alien;
class Robot;
class Input;
class Video;

class Level1 : public Level
{
public:
	Level1(Alien* alien, Robot* robot, Input* input);
	~Level1();
	void initialise();
	void deinitialise();
	void update();
	void independentUpdate(float deltaTime);
	void render();
	
	int getNextLevel();
	
private:
	
	float deadZone_;
	const float SCROLL_SPEED;
	ScrollingLayer sky_;
	ScrollingLayer distantBackground_;
	ScrollingLayer closeBackground_;
	ScrollingLayer midground_;
	ScrollingLayer playerStage_;
	ScrollingLayer foreground_;

	RubblePuzzle rubblePuzzle_;

	Video* gift_;
	Video* prebuild_;
	Video* ending_;

	bool giftPlayed_;
	bool prebuildPlayed_;
	bool endingPlayed_;

	int nextLevel_;
	bool playGift_;
};

#endif	// LEVEL_1_HPP