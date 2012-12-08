// RubblePuzzle.cpp

#include "RubblePuzzle.hpp"
#include "FlickableObject.hpp"
#include "Touch.hpp"

RubblePuzzle::RubblePuzzle()
: rocks_(0)
, firstTouch_(0)
, secondTouch_(0)
, firstTouchSet_(false)
{
}

RubblePuzzle::~RubblePuzzle()
{
}

void RubblePuzzle::initialise()
{
	rocks_.push_back(new FlickableObject("obj/Interactive/Wreckage2.png", 625, 620, 300, 300));
	rocks_.push_back(new FlickableObject("obj/Interactive/Wreckage3.png", 600, 700, 300, 300));
	rocks_.push_back(new FlickableObject("obj/Interactive/Wreckage1.png", 552, 649, 300, 300));
	rocks_.push_back(new FlickableObject("obj/Interactive/Wreckage5.png", 630, 580, 200, 200));
	rocks_.push_back(new FlickableObject("obj/Interactive/Wreckage7.png", 500, 600, 300, 300));
	rocks_.push_back(new FlickableObject("obj/Interactive/Wreckage10.png", 800, 650, 200, 200));
	rocks_.push_back(new FlickableObject("obj/Interactive/Wreckage4.png", 925, 520, 300, 300));
	rocks_.push_back(new FlickableObject("obj/Interactive/Wreckage9.png", 800, 570, 200, 200));
	rocks_.push_back(new FlickableObject("obj/Interactive/Wreckage3.png", 912, 600, 300, 300));
	rocks_.push_back(new FlickableObject("obj/Interactive/Wreckage8.png", 1030, 580, 400, 400));
	rocks_.push_back(new FlickableObject("obj/Interactive/Wreckage11.png", 980, 540, 300, 300));
	rocks_.push_back(new FlickableObject("obj/Interactive/Wreckage3.png", 950, 650, 128, 128));
	rocks_.push_back(new FlickableObject("obj/Interactive/Wreckage6.png", 1212, 680, 128, 128));
	rocks_.push_back(new FlickableObject("obj/Interactive/Wreckage4.png", 1512, 580, 128, 128));
	rocks_.push_back(new FlickableObject("obj/Interactive/Wreckage13.png", 1700, 650, 128, 128));
	rocks_.push_back(new FlickableObject("obj/Interactive/Wreckage5.png", 2000, 600, 128, 128));
	rocks_.push_back(new FlickableObject("obj/Interactive/Wreckage7.png", 2200, 550, 128, 128));
	rocks_.push_back(new FlickableObject("obj/Interactive/Wreckage8.png", 2360, 650, 128, 128));
	rocks_.push_back(new FlickableObject("obj/Interactive/Wreckage2.png", 2512, 600, 128, 128));
	rocks_.push_back(new FlickableObject("obj/Interactive/Wreckage1.png", 2570, 670, 128, 128));
	rocks_.push_back(new FlickableObject("obj/Interactive/Wreckage3.png", 2750, 630, 128, 128));
	rocks_.push_back(new FlickableObject("obj/Interactive/Wreckage6.png", 2892, 700, 128, 128));
	rocks_.push_back(new FlickableObject("obj/Interactive/Wreckage4.png", 3012, 670, 128, 128));
	rocks_.push_back(new FlickableObject("obj/Interactive/Wreckage13.png", 3200, 650, 128, 128));
	rocks_.push_back(new FlickableObject("obj/Interactive/Wreckage5.png", 3220, 600, 128, 128));
	rocks_.push_back(new FlickableObject("obj/Interactive/Wreckage7.png", 3270, 550, 128, 128));
	rocks_.push_back(new FlickableObject("obj/Interactive/Wreckage8.png", 3290, 700, 128, 128));

	/*
	rocks_.push_back(new FlickableObject("textures/Rock.png", 300, 300, 128, 128));
	rocks_.push_back(new FlickableObject("textures/Rock.png", 2000, 500, 128, 128));
	rocks_.push_back(new FlickableObject("textures/Rock.png", 3000, 530, 128, 128));
	rocks_.push_back(new FlickableObject("textures/Rock.png", 3500, 560, 128, 128));
	rocks_.push_back(new FlickableObject("textures/Rock.png", 4000, 500, 128, 128));
	rocks_.push_back(new FlickableObject("textures/Rock.png", 4500, 500, 128, 128));
	rocks_.push_back(new FlickableObject("textures/Rock.png", 5000, 500, 128, 128));
	rocks_.push_back(new FlickableObject("textures/Rock.png", 5600, 500, 128, 128));
	*/
	firstTouch_ = new Touch;
	secondTouch_ = new Touch;
}

void RubblePuzzle::deinitialise()
{
	while(!rocks_.empty())
	{
		//if( rocks_.back() != 0)
		//{
			delete rocks_.back();
		//}
		rocks_.pop_back();
	}

	delete firstTouch_;
	firstTouch_ = 0;

	delete secondTouch_;
	secondTouch_ = 0;
}

void RubblePuzzle::update()
{
	for(std::vector<FlickableObject*>::iterator iter = rocks_.begin(); iter != rocks_.end(); iter++)
	{
		(*iter)->update();
	}
}

void RubblePuzzle::touchUpdate(Touch* touch)
{
	for(std::vector<FlickableObject*>::iterator iter = rocks_.begin(); iter != rocks_.end(); iter++)
	{
		if( (*iter)->collisionDetection(touch->x_, touch->y_) )
		{
			if( !(*iter)->beenTouched() && firstTouchSet_ == false)
			{
				firstTouch_->x_ = touch->x_;
				firstTouch_->y_ = touch->y_;
				firstTouch_->id_ = touch->id_;
				(*iter)->setTouched();
				firstTouchSet_ = true;
				break;
			}	// end beenTouched() if
		}	// end collision if
	}	// end flickable object for
	
	/*
	for(std::vector<FlickableObject*>::iterator iter = rocks_.begin(); iter != rocks_.end(); iter++)
	{
		if( (*iter)->beenTouched() && ( ((*iter)->getCentreY() > 1000 ) || ((*iter)->getCentreY() < -200 ) ))
		{
			rocks_.erase(iter);
		}	// end beenTouched() if
	}	// end flickable object for
	*/
}

void RubblePuzzle::setSecondTouch(Touch* touch)
{
	secondTouch_->x_ = touch->x_;
	secondTouch_->y_ = touch->y_;
}

void RubblePuzzle::touchCountZero()
{
	for(std::vector<FlickableObject*>::iterator iter = rocks_.begin(); iter != rocks_.end(); iter++)
	{
		if( (*iter)->beenTouched() && !(*iter)->getVelocitySet() )
		{
			(*iter)->setVelocity(firstTouch_->x_, firstTouch_->y_, secondTouch_->x_, secondTouch_->y_);
			firstTouchSet_ = false;
		}	// end beenTouched() and getVelocitySet() if
	}	// end flickable object for 
}

void RubblePuzzle::render()
{
	std::vector<FlickableObject*>::reverse_iterator iter;
	for(iter = rocks_.rbegin(); iter != rocks_.rend(); iter++)
	{
		(*iter)->render();
	}	// end flickable object for 
}

void RubblePuzzle::movePuzzle(int deltaX)
{
	for(std::vector<FlickableObject*>::iterator iter = rocks_.begin(); iter != rocks_.end(); iter++)
	{
		(*iter)->setCenterAt( (*iter)->getCentreX() + deltaX, (*iter)->getCentreY() );
	}	// end flickable object for 
}

int16 RubblePuzzle::getCenterX() 
{ 
	return rocks_[0]->getCentreX();
}

// Returns true if a rubble piece has been touched
bool RubblePuzzle::getPieceBeingTouched()
{
	return firstTouchSet_;
}