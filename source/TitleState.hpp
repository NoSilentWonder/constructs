/*
	Copyright	Kangaroo Magic 2011
	Created 	Elinor Townsend
	
	Name		TitleState
	Brief		Declaration of TitleState class inherited from State
*/

#ifndef _TITLESTATE_H
#define _TITLESTATE_H

#include "State.hpp"
#include "IwGx.h"

class GraphicsObject;


/*
	Name		TitleState class
	Brief		The TitleState class contains the logic methods for 
				the title state of the Constucts of Friendship game
*/
class TitleState : public State
{
public:
	TitleState();
	~TitleState();
    virtual State* getNextState(Condition condition);
	virtual void initialise();
	virtual void deinitialise();
	virtual void update();
	virtual void independentUpdate(float deltaTime);
	virtual void render();
private:
	GraphicsObject* splashScreen_;
};

#endif // _TITLESTATE_H