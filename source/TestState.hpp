/*
	Copyright	Kangaroo Magic 2011
	Created 	Elinor Townsend
	
	Name		TestState
	Brief		Declaration of TestState class inherited from State
*/

#ifndef _TESTSTATE_H
#define _TESTSTATE_H

#include "State.hpp"
#include "ScrollingLayer.hpp"

/*
	Name		TestState class
	Brief		The TestState class contains the logic methods for 
				a test state of the Constucts of Friendship game
*/
class TestState : public State
{
public:
	TestState();
	~TestState();
    virtual State* getNextState(Condition condition);
	virtual void initialise();
	virtual void deinitialise();
	virtual void update();
	virtual void independentUpdate(float deltaTime);
	virtual void render();
private:
	ScrollingLayer background_;
	ScrollingLayer midground_;
	ScrollingLayer foreground_;
};

#endif // _TESTSTATE_H