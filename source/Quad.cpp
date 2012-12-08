/*
	Copyright	Kangaroo Magic 2011
	Created 	Elinor Townsend
	
	Name		Quad
	Brief		The method definitions for Quad class
*/

#include "Quad.hpp"

/*
	Name		Quad::Quad
	Syntax		Quad()
	Brief		Quad constructor initialises member variables
*/
Quad::Quad()
	: x_(0), y_(0), z_(0), width_(10), height_(10), angle_(0)
{
	calculateVertices();
}

/*
	Name		Quad::Quad
	Syntax		Quad(int16 x, int16 y, int16 z, int16 width, int16 height, int16 angle)
	Param		int16 x - x-value of the centre of the quad
	Param		int16 y - y-value of the centre of the quad
	Param		int16 z - z-ordering value
	Param		int16 width - Width of quad
	Param		int16 height - Height of quad
	Param		int16 angle - The angle the quad is rotated to
	Brief		Quad constructor initialises member variables
*/
Quad::Quad(int16 x, int16 y, int16 z, int16 width, int16 height, int16 angle)
{
	x_ = x;
	y_ = y;
	z_ = z;
	width_ = width;
	height_ = height;
	angle_ = angle;
	calculateVertices();
}

/*
	Name		Quad::~Quad
	Syntax		~Quad()
	Brief		Quad destructor
*/
Quad::~Quad()
{
}

/*
	Name		Quad::render
	Syntax		Quad::render()
	Brief		Renders the quad of vertices
*/
void Quad::render()
{
	// Clear the vertex colour stream
    IwGxSetColStream(NULL);

    // Set Vertex Stream
    IwGxSetVertStreamScreenSpace(vertices_, 4);

    // Draw the textured primitives
    IwGxDrawPrims(IW_GX_QUAD_STRIP, NULL, 4);
}

/*
	Name		Quad::renderPerspective
	Syntax		Quad::renderPerspective()
	Brief		Renders the quad of vertices with scaling based on 
				the quad's z-position
*/
void Quad::renderPerspective()
{
	CIwSVec2 vertices[4];

	// Created scaled verts based on z-position

	// Clear the vertex colour stream
    IwGxSetColStream(NULL);

    // Set Vertex Stream
    IwGxSetVertStreamScreenSpace(vertices, 4);

    // Draw the textured primitives
    IwGxDrawPrims(IW_GX_QUAD_STRIP, NULL, 4);
}

/*
	Name		Quad::moveTo
	Syntax		Quad::moveTo(const int16 x, const int16 y)
	Param		int16 x - X-position to move quad to
	Param		int16 y - Y-position to move quad to
	Brief		Sets the x- and y-position of the quad
*/
void Quad::moveTo(const int16 x, const int16 y)
{
	x_ = x;
	y_ = y;
	calculateVertices();
}

/*
	Name		Quad::setDimensions
	Syntax		Quad::setDimensions(const int16 width, const int16 height)
	Param		int16 width - Width to set for the quad
	Param		int16 height - Height to set for the quad
	Brief		Sets the dimensions of the quad
*/
void Quad::setDimensions(const int16 width, const int16 height)
{
	width_ = width;
	height_ = height;
	calculateVertices();
}

/*
	Name		Quad::moveDeltaX
	Syntax		Quad::moveDeltaX(const int16 x)
	Param		int16 x - Value to change the x-position of the quad by
	Brief		Increases the quad's x-position by x
*/
void Quad::moveDeltaX(const int16 x)
{
	x_ += x;
	calculateVertices();
}

/*
	Name		Quad::moveDeltaY
	Syntax		Quad::moveDeltaY(const int16 y)
	Param		int16 y - Value to change the y-position of the quad by
	Brief		Increases the quad's y-position by y
*/
void Quad::moveDeltaY(const int16 y)
{
	y_ += y;
	calculateVertices();
}

/*
	Name		Quad::setZ
	Syntax		Quad::setZ(const int16 z)
	Param		int16 z - Value to set the z-position of the quad to
	Brief		Sets the z-position of the quad
*/
void Quad::setZ(const int16 z)
{
	z_ += z;
}

/*
	Name		Quad::setRotation
	Syntax		Quad::setRotation(const int16 angle)
	Param		int16 angle - Angle to set the quad to
	Brief		Sets the angle of rotation of the quad
*/
void Quad::setRotation(const int16 angle)
{
	angle_ += angle;
	calculateVertices();
}

/*
	Name		Quad::scale
	Syntax		Quad::scale(const int16 scale)
	Param		int16 scale - Factor to scale the quad by
	Brief		Scales the dimensions of the quad
*/
void Quad::scale(const int16 scale)
{
	int16 widthPercent = scale / 100 * width_;
	int16 heightPercent = scale / 100 * height_;

	width_ += widthPercent; 
	height_ += heightPercent;

	if(width_ < 0)
		width_ = 0;
	if(height_ < 0)
		height_ = 0;

	calculateVertices();
}

/*
	Name		Quad::calculateVertices
	Syntax		Quad::calculateVertices()
	Brief		Calculates the coordinates for the vertices of the 
				quad based on position, dimensions and rotation
*/
void Quad::calculateVertices()
{
	double half_w = width_ * 0.5;
	double half_h = height_ * 0.5;

	double cosine = cos(PI * angle_ / 180);
	double sine	 = sin(PI * angle_ / 180);

	// Top left
	vertices_[0].x 	 = static_cast<int16>(cosine * -half_w + sine *  half_h) + x_;
	vertices_[0].y 	 = static_cast<int16>(cosine * -half_h + sine * -half_w) + y_;
	
	// Bottom left
	vertices_[1].x 	 = static_cast<int16>(cosine * -half_w + sine * -half_h) + x_;
	vertices_[1].y 	 = static_cast<int16>(cosine *  half_h + sine * -half_w) + y_;
	
	// Top right
	vertices_[2].x 	 = static_cast<int16>(cosine *  half_w + sine *  half_h) + x_;
	vertices_[2].y 	 = static_cast<int16>(cosine * -half_h + sine *  half_w) + y_;
	
	// bottom right
	vertices_[3].x   = static_cast<int16>(cosine *  half_w + sine * -half_h) + x_;
	vertices_[3].y   = static_cast<int16>(cosine *  half_h + sine *  half_w) + y_;
	
	
}