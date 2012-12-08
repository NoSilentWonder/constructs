/* 
	Copyright	Kangaroo Magic 2011
	Created		Jonathan Jones, based on tutorial by Mat Hopwood aka DrMop 

	Name		Input
	Brief		Handles input from device
	Details		Includes functionality to check for touch events from device
*/

#ifndef _INPUT_HPP_
#define _INPUT_HPP_

#include "Touch.hpp"
/* 
	Name		Touch
	Brief		A struct which stores the information about a touch event
	Notes		Follows s3ePointerTouchEvent layout
*/
/*
struct Touch
{
public:
	int x_, y_;		// X and Y position on the screen of the touch
	bool active_;	// Whether the touch is active 
	int id_;		// See s3ePointerTouchEvent for details on how this is set
};
*/
/* 
	Name		Input
	Brief		A singleton class which handles all input related functionality
*/
class Input
{
public:
	Input();
	~Input();

	static Input* instance();									// Method that returns the pointer to singleton input object
	bool	initialise();										// Initalises the input object
	void	deinitialise();										// Deinitalises the input object
	void	update();											// Checks for any updates, e.g if there is a new touch or a touch has been released
	bool	isAvailiable() const { return available_; }			// Return if the the input object has been created
	bool	isMultiTouch() const { return isMultiTouch_; }		// Return if the device has multi touch capabilities
	Touch*  getTouchByID(int id);								// Return the pointer to the touch that has the same id as the one passed 
	Touch*  getTouch(int index) { return &touches_[index]; }	// Return the pointer to the touch that from the array relative to its position in the array
	Touch*	findTouch(int id);									// Return the pointer to the touch that has the same id as the one passed, if it doesn't exist create it
	int		getTouchCount() const;								// Return the number of touches 
private:

	static Input* instance_;									// Stores a pointer to the instance of the singleton input object  
	enum { MAX_TOUCHES = 4};									// The maximum amount of touches allowed
	bool available_;											// Represents if the input class has been created 
	bool isMultiTouch_;											// Represents if the device is multi touch or not 
	Touch touches_[MAX_TOUCHES];								// An array to store the touches in
};


#endif // _INPUT_HPP_