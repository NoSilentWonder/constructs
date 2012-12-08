/*
	Copyright	Kangaroo Magic 2011
	Created 	Elinor Townsend
	
	Name		Condition
	Brief		Enumerated type of Condition used by game states for switching states
	Details		New conditions should be added to the end of the list
*/

#ifndef _CONDITION_H
#define _CONDITION_H

enum Condition
{
	CONDITION_GO_TO_TITLE,
	CONDITION_GO_TO_MENU,
	CONDITION_GO_TO_SETTINGS,
	CONDITION_GO_TO_PLAY,
};

#endif // _CONDITION_H