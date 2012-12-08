/*
	Copyright	Kangaroo Magic 2011
	Created 	Jonathan Jones
	
	Name		Button
	Brief		Definition of base class button
*/

#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "s3eTypes.h"

class Button
{
public:
	Button(int16 x, int16 y)
		: x_(x)
		, y_(y)
		{}
	virtual ~Button() {}
	virtual void render() = 0;
	
protected:
	int16 x_;
	int16 y_;
};

#endif // BUTTON_HPP