/*
	Copyright	Kangaroo Magic 2011
	Created 	Jonathan Jones
	
	Name		Circular button
	Brief		Definition of circular button class
*/

#ifndef CIRCULAR_BUTTON_HPP
#define CIRCULAR_BUTTON_HPP

#include "s3eTypes.h"
#include "Button.hpp"
#include "Quad.hpp"
#include "Material.hpp"
#include <string>

class CIwTexture;

class CircularButton : public Button
{
public:
	CircularButton(std::string name, int16 x, int16 y, int16 z, int16 radius, bool drawUVsInReverse);
	~CircularButton();
	void render();
	bool collisionDetection(int16 touchX, int16 touchY) const;
protected:
	int16 radius_;
	Quad  buttonQuad_;
	Material* buttonMaterial_;
	CIwTexture* buttonTexture_;
	bool drawUVsInReverse_;
};

#endif // CIRCULAR_BUTTON_HPP