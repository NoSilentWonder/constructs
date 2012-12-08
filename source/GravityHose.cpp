/*
	Copyright	Kangaroo Magic 2011
	Created 	Jonathan Jones
	
	Name		GravityHose.hpp
	Brief		Contains everything associated with the gravity hose object 
*/

#include "GravityHose.hpp"
#include "Sprite.hpp"

GravityHose::GravityHose()
: beingHeld_(false)
//, gravityHose_()
//, 
{
	
}

GravityHose::~GravityHose()
{
}

void GravityHose::setState(bool held)
{
	beingHeld_ = held;
}

bool GravityHose::getState()
{
	return beingHeld_;
}

void GravityHose::render()
{
}