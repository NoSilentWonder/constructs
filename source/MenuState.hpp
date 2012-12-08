/*
	Copyright	Kangaroo Magic 2011
	Created 	Elinor Townsend
	
	Name		MenuState
	Brief		Declaration of MenuState Class inherited from State
*/

#ifndef _MENUSTATE_H
#define _MENUSTATE_H

#include "State.hpp"

#include "CircularButton.hpp"
#include "Sprite.hpp"

class MusicPlayer;
class Video;

/*
	Name		MenuState class
	Brief		The MenuState class contains the logic methods for 
				the menu state of the Constucts of Friendship game
*/
class MenuState : public State
{
public:
    virtual State *getNextState(Condition condition);
	virtual void initialise();
	virtual void deinitialise();
	virtual void update();
	virtual void independentUpdate(float deltaTime);
	virtual void render();

private:
	Sprite background_;
	CircularButton* playButton_;
	bool changeState_;
	MusicPlayer* musicPlayer_;
	Video* intro_;
	bool introPlayed_;
};

#endif // _MENUSTATE_H