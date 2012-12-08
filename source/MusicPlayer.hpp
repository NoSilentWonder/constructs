#ifndef AUDIOOBJECT_H
#define AUDIOOBJECT_H

#include "s3e.h"

class MusicPlayer
{
public:

	MusicPlayer			();
	~MusicPlayer		();

	void initialise		();
	void deinitialise	();

	void play			(const char* filename);
	void stop			();
	void pause			();
	void resume			();

	void increaseVolume	();
	void decreaseVolume	();
};

#endif