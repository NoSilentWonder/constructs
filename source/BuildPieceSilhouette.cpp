// BuildPieceSilhouette.cpp

#include "BuildPieceSilhouette.hpp"

/*
	Name	BuildPieceSilhouette::BuildPieceSilhouette
	Syntax	BuildPieceSilhouette::BuildPieceSilhouette(CIwResGroup* group, const char* nameOfFile, int16 x, int16 y, int16 width, int16 height, BuildPiece* connectedBuildPiece)
	Params	CIwResGroup* group				- A pointer to the resource group which contains the texture information
			const char* nameOfFile			- The name of the file with the image to load and use as texture
			int16 x							- The x coordinate to place the silhouette at
			int16 y							- The y coordinate to place the silhouette at
			int16 width						- The width of the silhouette 
			int16 height					- The height of the silhouette
			BuildPiece* connectedBuildPiece	- A pointer to the build piece connected with this silhouette
	Brief	Sets up a build piece silhouette
*/

BuildPieceSilhouette::BuildPieceSilhouette(char* nameOfFile, int16 x, int16 y, int16 width, int16 height, BuildPiece* connectedBuildPiece)
: BuildPiece(nameOfFile, x, y, width, height)
, connectedBuildPiece_(connectedBuildPiece)
{
}

/*
	Name	BuildPieceSilhouette::~BuildPieceSilhouette
	Syntax	BuildPieceSilhouette::~BuildPieceSilhouette()
	Brief	Destroy anything associated with a build piece silhouette
*/
BuildPieceSilhouette::~BuildPieceSilhouette()
{
	// Set the connected build piece pointer to zero, there is no need to delete it as deletion is handled by the object itself when appropriate
	connectedBuildPiece_ = 0;
}

/*
	Name		BuildPieceSilhouette::hasBuildPiece
	Syntax		BuildPieceSilhouette::hasBuildPiece()
	Brief		Returns if the correct build piece is ontop of the silhouette
	Returns		true	- If the correct build piece is placed on top
				false	- If the build piece is not on top of the silhouette
*/
bool BuildPieceSilhouette::hasBuildPiece()
{
	return hasBuildPiece_;
}

/*
	Name		BuildPieceSilhouette::setHasBuildPiece
	Syntax		BuildPieceSilhouette::setHasBuildPiece(bool buildPieceState)
	Param		bool buildPieceState - A boolean to set has hasBuildPiece to
	Brief		Set the boolean which describes if the build piece is on the silhouette
*/
void BuildPieceSilhouette::setHasBuildPiece(bool buildPieceState)
{
	// Set build piece with passed bool
	hasBuildPiece_ = buildPieceState;
}

/*
	Name		BuildPieceSilhouette::getConnectedBuildPiece
	Syntax		BuildPieceSilhouette::getConnectedBuildPiece()
	Brief		Returns a pointer to the build piece linked with the silhouette
	Returns		A pointer to the build piece linked with the silhouette
*/
BuildPiece* BuildPieceSilhouette::getConnectedBuildPiece()
{
	return connectedBuildPiece_;
}