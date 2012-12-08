/*
	Copyright	Kangaroo Magic 2011
	Created 	Elinor Townsend
	
	Name		Quad
	Brief		Declaration of Quad class
*/

#ifndef _QUAD_H
#define _QUAD_H

#include "IwGx.h"

/*
	Name		Quad class
	Brief		The Quad class creates a quad of vertices that can be streamed
				and methods to manipulate these vertices
*/
class Quad
{
public:

	Quad();
	Quad(int16 x, int16 y, int16 z, int16 width, int16 height, int16 angle);
	~Quad();
	
	void render();
	void renderPerspective();
	void moveTo(const int16 x, const int16 y);
	void setDimensions(const int16 width, const int16 height);
	void moveDeltaX(const int16 x);
	void moveDeltaY(const int16 y);
	void setZ(const int16 z);	
	void setRotation(const int16 angle);
	void scale(const int16 scale);  // scale quad by factor of s

	int16 getX() const { return x_; };
	int16 getY() const { return y_; };
	int16 getZ() const { return z_; };
	int16 getWidth() const { return width_; };
	int16 getHeight() const { return height_; };

private:
	void calculateVertices();

private:
	int16 x_;
	int16 y_;
	int16 z_; // Used for z-ordering and scaling
	int16 width_;
	int16 height_;
	int16 angle_;
	CIwSVec2 vertices_[4];
};

#endif // _QUAD_H