/*
	Copyright	Kangaroo Magic 2011
	Created		Jonathan Jones
	Name		BuildPieceSilhouette
	Brief		A silhouette to place a build piece on top of

*/
#ifndef BUILD_PIECE_SILHOUETTE_HPP
#define	BUILD_PIECE_SILHOUETTE_HPP

// Includes
#include "BuildPiece.hpp"

/*
	Name	BuildPieceSilhouette
	Brief	Inherits from build piece, as it practically is, but has extra variables and functions to state whether the silhouette has its corresponding build piece placed on it 
*/
class BuildPieceSilhouette : public BuildPiece
{
public:
	BuildPieceSilhouette(char* nameOfFile, int16 x, int16 y, int16 width, int16 height, BuildPiece* connectedBuildPiece);
	~BuildPieceSilhouette();
	bool hasBuildPiece();							// Returns if the silhouette has the its corresponding build piece						
	void setHasBuildPiece(bool buildPieceState);	// Changes the state that represents if the correct build piece is set on the silhouette
	BuildPiece* getConnectedBuildPiece();			// Return the pointer to the build piece that is linked to the silhouette
private:
	bool hasBuildPiece_;							// A bool representing if the silhouette has the build piece placed directly on it
	BuildPiece* connectedBuildPiece_;				// A pointer to the build piece connected to the silhouette
};
#endif // BUILD_PIECE_SILHOUETTE_HPP