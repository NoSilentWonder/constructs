// Input.cpp

#include "s3ePointer.h"
#include "Input.hpp"

// Set global instance pointer
Input* Input::instance_ = 0;

/*
	Name	Input::instance
	Syntax	Input::instance()
	Returns A pointer to the singleton instance of input
	Brief	Returns a pointer to singleton input object
*/
Input* Input::instance()
{
	// If instance has not been set
	if (!instance_)
	{
		// Create a pointer to a input object and set it to instance
		instance_ = new Input();
	}

	// Return pointer to singleton input object
	return instance_;
}
 
/*
	Name	HandleMultiTouchButtonCB
	Syntax	HandleMultiTouchButtonCB(s3ePointerTouchEvent* event, Input* instance)
	Param	s3ePointerTouchEvent* event - A pointer to a struct containing the touch's information
			Input* instance				- A pointer to the singleton class which handles all input events
	Brief	For multitouch devices the system will call this callback when the user touches the screen. 
			This callback is called once for each screen touch
	Notes	CB stands for callback
*/
void HandleMultiTouchButtonCB(s3ePointerTouchEvent* event, Input* instance)
{
	// Check to see if the touch already exists
	Touch* touch = instance->findTouch(event->m_TouchID);
    if (touch != NULL)
    {
		// Yes it does, so update the touch information
        touch->active_ = event->m_Pressed != 0; 
        touch->x_ = event->m_x;
        touch->y_ = event->m_y;
    }
}

/*
	Name	HandleMultiTouchMotionCB
	Syntax	HandleMultiTouchMotionCB(s3ePointerTouchEvent* event, Input* instance)
	Param	s3ePointerTouchEvent* event - A pointer to a struct containing the touch's information
			Input* instance				- A pointer to the singleton class which handles all input events
	Brief	For multitouch devices the system will call this callback when the user moves their finger on the screen. 
			This callback is called once for each screen touch
	Notes	CB stands for callback
*/
void HandleMultiTouchMotionCB(s3ePointerTouchMotionEvent* event, Input* instance)
{
	// Check to see if the touch already exists
	Touch* touch = instance->findTouch(event->m_TouchID);
    if (touch != NULL)
    {
		// Updates the touches positional information
        touch->x_ = event->m_x;
        touch->y_ = event->m_y;
    }
}

/*
	Name	HandleSingleTouchButtonCB
	Syntax	HandleSingleTouchButtonCB(s3ePointerTouchEvent* event, Input* instance)
	Param	s3ePointerTouchEvent* event - A pointer to a struct containing the touch's information
			Input* instance				- A pointer to the singleton class which handles all input events
	Brief	The system will call this callback when the user touches the screen
	Notes	CB stands for callback
*/
void HandleSingleTouchButtonCB(s3ePointerEvent* event, Input* instance)
{
	Touch* touch = instance->getTouch(0);
    touch->active_ = event->m_Pressed != 0;
    touch->x_ = event->m_x;
    touch->y_ = event->m_y;
}

/*
	Name	HandleSingleTouchMotionCB
	Syntax	HandleSingleTouchMotionCB(s3ePointerTouchEvent* event, Input* instance)
	Param	s3ePointerTouchEvent* event - A pointer to a struct containing the touch's information
			Input* instance				- A pointer to the singleton class which handles all input events
	Brief	The system will call this callback when the user moves their finger on the screen
	Notes	CB stands for callback
*/
void HandleSingleTouchMotionCB(s3ePointerMotionEvent* event, Input* instance)
{
	Touch* touch = instance->getTouch(0);
    touch->x_ = event->m_x;
    touch->y_ = event->m_y;
}


/*
	Name		Input::Input
	Syntax		Input::Input()
	Brief		Input constructor initialises member variables
*/
Input::Input()
{
}

/*
	Name		Input::~Input
	Syntax		Input::~Input()
	Brief		Input destructor
*/
Input::~Input()
{
}

/*
	Name		Input::initialise
	Syntax		Input::initialise()
	Return		bool - Returns true if initialised all
	Brief		Initialise all data associated with input and register the callbacks
*/
bool Input::initialise()
{
	// Check to see if the device that we are running on supports the pointer
    available_ = s3ePointerGetInt(S3E_POINTER_AVAILABLE) ? true : false;
	
	if (!available_)
	{
		return false;	// No pointer support
	}

	// Clear out the touches array
	for (int t = 0; t < MAX_TOUCHES; t++)
	{
		touches_[t].active_ = false;
		touches_[t].id_ = 0;
	}

	// Determine if the device supports multi-touch
    isMultiTouch_ = s3ePointerGetInt(S3E_POINTER_MULTI_TOUCH_AVAILABLE) ? true : false;

	// For multi-touch devices we handle touch and motion events using different callbacks
    if (isMultiTouch_)
    {
        s3ePointerRegister(S3E_POINTER_TOUCH_EVENT, (s3eCallback)HandleMultiTouchButtonCB, instance_);
        s3ePointerRegister(S3E_POINTER_TOUCH_MOTION_EVENT, (s3eCallback)HandleMultiTouchMotionCB, instance_);
    }
    else	// Not multi touch 
    {
        s3ePointerRegister(S3E_POINTER_BUTTON_EVENT, (s3eCallback)HandleSingleTouchButtonCB, instance_);
        s3ePointerRegister(S3E_POINTER_MOTION_EVENT, (s3eCallback)HandleSingleTouchMotionCB, instance_);
    }

	return true; // Pointer support
}

/*
	Name		Input::deinitialise
	Syntax		Input::deinitialise()
	Brief		Deinitialise all data and unregister the callbacks 
*/
void Input::deinitialise()
{
	if (available_)
	{
		// Unregister the pointer system callbacks
		if (isMultiTouch_)
		{
			s3ePointerUnRegister(S3E_POINTER_TOUCH_EVENT, (s3eCallback)HandleMultiTouchButtonCB);
			s3ePointerUnRegister(S3E_POINTER_TOUCH_MOTION_EVENT, (s3eCallback)HandleMultiTouchMotionCB);
		}
		else	// Not multi touch 
		{
			s3ePointerUnRegister(S3E_POINTER_BUTTON_EVENT, (s3eCallback)HandleSingleTouchButtonCB);
			s3ePointerUnRegister(S3E_POINTER_MOTION_EVENT, (s3eCallback)HandleSingleTouchMotionCB);
		}
	}
}

/*
	Name		Input::update
	Syntax		Input::update()
	Brief		Update the pointer state, e.g if the pointer is up(not pressed) or down(pressed)
*/
void Input::update()
{
	// Update the pointer if it is available
	if (available_)
	{
		// Updates the pointer state 
		s3ePointerUpdate();
	}
}

/*
	Name		Input::getTouchByID
	Syntax		Input::getTouchByID(int id)
	Param		int id - The id of the touch to find
	Return		A pointer to the touch that has the same id
	Brief		Returns a pointer to a touch with the same id that is passed to the function
*/
Touch* Input::getTouchByID(int id)
{
	// Find touch by its ID and return it
	for (int t = 0; t < MAX_TOUCHES; t++)
	{
		if (touches_[t].active_ && touches_[t].id_ == id)
		{
			return &touches_[t];
		}
	}

	// If no touch is found then return null
	return NULL;
}

/*
	Name		Input::findTouch
	Syntax		Input::findTouch(int id)
	Param		int id - The id of the touch to find
	Return		A pointer to the touch that has the same id
	Brief		Returns a pointer to a touch with the same id that is passed to the function
*/
Touch* Input::findTouch(int id)
{
	// If the input object has not been created 
	if (!available_)
	{
		return NULL;
	}

    // Attempt to find the touch by its ID and then return it
	// If the touch does not exist then it is recorded in the touches list as it has been found by the callback
	for (int t = 0; t < MAX_TOUCHES; t++)
	{
		if (touches_[t].id_ == id)
		{
			return &touches_[t];
		}

		if (!touches_[t].active_)
		{
            touches_[t].id_ = id;
			return &touches_[t];
		}
	}

	// If no touch is found then return null
	return NULL;
}

/*
	Name		Input::getTouchCount
	Syntax		Input::getTouchCount() const
	Return		The number of touches currently active
	Brief		Returns the number of active touches
*/
int	Input::getTouchCount() const
{
	// If the input object has not been created 
	if (!available_)
	{
		return 0;
	}

	// Return the total number of active touches
	int count = 0;

	for (int t = 0; t < MAX_TOUCHES; t++)
	{
		if (touches_[t].active_)
		{
            count++;
		}
	}

	return count;
}