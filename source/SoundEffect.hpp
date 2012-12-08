/*
	Copyright	Kangaroo Magic 2012
	Created 	Elinor Townsend
		
	Name		SoundEffect
	Brief		Declaration of SoundEffect Class which creates a single sound effect
*/

#ifndef _SOUNDEFFECT_H_
#define _SOUNDEFFECT_H_

/*
	Name		SoundEffect class
	Brief		The SoundEffect class creates a sound effect and provides methods for controlling it
*/
class SoundEffect
{
public:
	SoundEffect();
	~SoundEffect();

	void initialise(char* filename);
	void deinitialise();

	void play(int repeat);
	void stop();
	void pause();
	void resume();
	void increaseVolume();
	void decreaseVolume();
	bool isPlaying() const { return isPlaying_; };
	void setVolume(int32 vol);

private:
	int16* soundBuffer_;
	int32 fileSize_;
	int channel_;
	char volumeString_[256];
	bool isInitialised_;
	bool isPlaying_;
	bool isLooping_;
	bool isPaused_;
};

#endif // _SOUNDEFFECT_H_