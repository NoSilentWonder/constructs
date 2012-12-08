// Touch.hpp

#ifndef TOUCH_HPP
#define TOUCH_HPP

#include "s3eTypes.h"

struct Touch
{
public:
	int x_, y_;		// X and Y position on the screen of the touch
	bool active_;	// Whether the touch is active 
	int id_;		// See s3ePointerTouchEvent for details on how this is set
};

/*
class Touch
{
public:
	Touch(int16 x, int16 y, bool active, int id);
	~Touch();

	int16	getX();
	void	setX(int16 x);

	int16	getY();
	void	setY(int16 y);

	bool	getActive();
	void	setActive(bool active);

	int		getID();
	void	setID(int ID);

private:
	int16 x_, y_;	// X and Y position on the screen of the touch
	bool active_;	// Whether the touch is active 
	int id_;		// See s3ePointerTouchEvent for details on how this is set
};
*/
#endif // TOUCH_HPP