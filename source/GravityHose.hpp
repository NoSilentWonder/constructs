/*
	Copyright	Kangaroo Magic 2011
	Created 	Jonathan Jones
	
	Name		GravityHose.hpp
	Brief		Contains everything associated with the gravity hose object 
*/

#ifndef GRAVITY_HOSE_HPP
#define GRAVITY_HOSE_HPP

class Sprite;

/*
	Name	GravityHose
	Brief	Contains everything associated with the gravity hose object
*/
class GravityHose
{
public:
	GravityHose();
	~GravityHose();
	
	void setState(bool held);
	bool getState();
	void render();
private:
	bool beingHeld_;
	//Sprite* gravityHose_;
};

#endif	// GRAVITY_HOSE_HPP