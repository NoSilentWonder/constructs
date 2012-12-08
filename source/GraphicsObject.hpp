/*
	Copyright	Kangaroo Magic 2011
	Created 	Andrew Hoque
	
	Name		GraphicsObject
	Brief		Declaration of GraphicsObject class
*/

#ifndef _GRAPHICSOBJECT_H
#define _GRAPHICSOBJECT_H

#include <string>
#include "Iw2D.h"

/*
	Name		GraphicsObject class
	Brief		The GraphicsObject class provides the client with a way
				of displaying graphical objects on screen and manipulating
				them
*/

class GraphicsObject
{
public:

	GraphicsObject	(const std::string fileName, const CIwSVec2 position, const CIwSVec2 size);
	~GraphicsObject	();

	void			render			();

	void			setPosition		(CIwSVec2 position);
	const CIwSVec2&	getPosition		();

	void			setSize			(CIwSVec2 size);
	const CIwSVec2&	getSize			();

public:

	void			initialise		(const std::string fileName);
	void			deinitialise	();

private:

	CIw2DImage*		image_;
	CIwSVec2		position_;
	CIwSVec2		size_;
};

#endif // _GRAPHICSOBJECT_H