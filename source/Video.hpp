/*
	Copyright	Kangaroo Magic 2012
	Created 	Elinor Townsend
		
	Name		Video
	Brief		Declaration of Video Class which creates a single video clip
*/

#ifndef _VIDEO_H_
#define _VIDEO_H_

/*
	Name		Video class
	Brief		The Video class creates a  video clip and provides methods for controlling it
*/
class Video
{
public:
	Video();
	~Video();

	void initialise(char* filename);
	void deinitialise();

	void play();
	void stop();
	void pause();
	void resume();
	bool isPlaying();

private:
	char* videoClip_;
	
	bool isInitialised_;
};

#endif // _VIDEO_H_