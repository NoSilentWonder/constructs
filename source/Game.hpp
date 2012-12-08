/*
	Copyright	Kangaroo Magic 2011
	Created 	Elinor Townsend
		
	Name		Game
	Brief		Declaration of Game Class which manages the game loop
	Details		Game Class is a Singleton - the singleton instance is accessed using Game::instance()
*/

#ifndef _GAME_H_
#define _GAME_H_

#include "Condition.hpp"

class State;
class Input;

/*
	Name		Game class
	Brief		The Game class handles the main game loop and holds any objects 
				accessed by all game states. It maintains the current game state 
				and processes calls to the update and render methods of this state
*/
class Game
{
public:
	Game();
	~Game();

	static Game* instance();

	void initialise();
	void deinitialise();
	void run();
	Condition getCondition() const { return condition_; };
	void setCondition(Condition condition);					// Sets the condition_ variable
	void changeCondition(Condition condition);				// Changes the condition_ variable and calls changeState
	Input* getInput() const { return input_; };
private:
	void update();
	void independentUpdate(float deltaTime);
	void render();
	void changeState();
	int getUpdateFrame();

	static Game* instance_;
	State* currentState_;
	Condition condition_;
	const int UPS;
	const int MAX_UPDATES;

	Input* input_;
};

#endif // _GAME_H_