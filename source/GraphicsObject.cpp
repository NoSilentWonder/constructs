/*
	Copyright	Kangaroo Magic 2011
	Created 	Andrew Hoque
	
	Name		GraphicsObject
	Brief		Definition of GraphicsObject methods
*/

#include "GraphicsObject.hpp"

GraphicsObject::GraphicsObject(const std::string fileName, const CIwSVec2 position, const CIwSVec2 size):
position_(position),
size_(CIwSVec2(size))
{
	initialise(fileName);
}

GraphicsObject::~GraphicsObject()
{
}

void GraphicsObject::initialise(const std::string fileName)
{
	image_ = Iw2DCreateImage(fileName.c_str());
}

void GraphicsObject::deinitialise()
{
	delete image_;
}

void GraphicsObject::setPosition(CIwSVec2 position)
{
	position_ = position;
}

const CIwSVec2& GraphicsObject::getPosition()
{
	return position_;
}

void GraphicsObject::setSize(CIwSVec2 size)
{
	size_ = size;
}

const CIwSVec2& GraphicsObject::getSize()
{
	return size_;
}

void GraphicsObject::render()
{
	Iw2DDrawImage(image_, position_, size_); 
}
