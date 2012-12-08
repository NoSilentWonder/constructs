/*
	Copyright	Kangaroo Magic 2012
	Created 	Elinor Townsend

	Name		SoundEffect
	Brief		The method definitions for the SoundEffect class
*/

#include <string.h>
#include <stdio.h>
#include "s3e.h"
#include "SoundEffect.hpp"

/*
	Name		SoundEffect::SoundEffect
	Syntax		SoundEffect()
	Brief		SoundEffect constructor initialises member variables
*/
SoundEffect::SoundEffect()
	: soundBuffer_(0), fileSize_(0), channel_(0), isInitialised_(false), isPlaying_(false), 
	  isLooping_(false), isPaused_(false)
{

}

/*
	Name		SoundEffect::~SoundEffect
	Syntax		~SoundEffect()
	Brief		SoundEffect destructor
*/
SoundEffect::~SoundEffect()
{
}

/*
	Name		SoundEffect::initialise
	Syntax		SoundEffect::initialise(char* filename)
	Param		char* filename - The name of the file for the sound effect
	Brief		Creates the sound effect
*/
void SoundEffect::initialise(char* filename)
{
	// Read in sound data
    s3eFile *fileHandle = s3eFileOpen(filename, "rb");

    fileSize_ = s3eFileGetSize(fileHandle);
    soundBuffer_ = (int16*)s3eMallocBase(fileSize_);
    memset(soundBuffer_, 0, fileSize_);
    s3eFileRead(soundBuffer_, fileSize_, 1, fileHandle);
    s3eFileClose(fileHandle);

    // Setting default frequency at which all channels will play at, in Hz.
    s3eSoundSetInt(S3E_SOUND_DEFAULT_FREQ, S3E_SOUND_MAX_FREQ/2);

	isInitialised_ = true;
}

/*
	Name		SoundEffect::deinitialise
	Syntax		SoundEffect::deinitialise()
	Brief		Deinitialises the sound effect
*/
void SoundEffect::deinitialise()
{
}

/*
	Name		SoundEffect::play
	Syntax		SoundEffect::play(int repeat)
	Param		int repeat - repeat one of the following values:
							 *  0  = Play forever,
							 *  1  = Play once,
							 *  >1 = Play a certain number of times
	Brief		Plays the sound effect
*/
void SoundEffect::play(int repeat)
{
	if (isInitialised_ && !isPlaying_)
    {
		// Finds a free channel that we can use to play our file on.
		channel_ = s3eSoundGetFreeChannel();

		// Play the sound. Note that the 3rd paramater needs to be the number of samples to play, which
		// is the number of bytes divided by 2. A repeat count of 0 means 'play forever'.
		if (s3eSoundChannelPlay(channel_, soundBuffer_, fileSize_/2, repeat, 0) == S3E_RESULT_ERROR)
			sprintf(volumeString_, "Error in s3eSoundChannelPlay");
		else
			isPlaying_ = true;
	}
	if (!repeat)
	{
		isLooping_ = true;
	}
	else
		isLooping_ = false;
}

/*
	Name		SoundEffect::stop
	Syntax		SoundEffect::stop()
	Brief		Stops the sound effect from playing
*/
void SoundEffect::stop()
{
	if (isInitialised_ && isPlaying_)
    {
        if (s3eSoundChannelStop(channel_) == S3E_RESULT_ERROR)
            sprintf(volumeString_, "Error in s3eSoundChannelStop");
        else
            isPlaying_ = false;
    }
}

/*
	Name		SoundEffect::pause
	Syntax		SoundEffect::pause()
	Brief		Pauses the sound effect
*/
void SoundEffect::pause()
{
	if (isInitialised_ && !isPaused_)
    {
		if (s3eSoundChannelPause(channel_) == S3E_RESULT_ERROR)
			sprintf(volumeString_, "Error in s3eSoundChannelPause");
		else
			isPaused_ = true;
	}
}

/*
	Name		SoundEffect::resume
	Syntax		SoundEffect::resume()
	Brief		Resumes playing the sound effect
*/
void SoundEffect::resume()
{
	if (isInitialised_ && isPaused_)
    {
		if (s3eSoundChannelResume(channel_) == S3E_RESULT_ERROR)
			sprintf(volumeString_, "Error in s3eSoundChannelResume");
		else
			isPaused_ = false;
	}
}

/*
	Name		SoundEffect::increaseVolume
	Syntax		SoundEffect::increaseVolume()
	Brief		Increases the volume of the sound effect
*/
void SoundEffect::increaseVolume()
{
	int32 temp = s3eSoundGetInt(S3E_SOUND_VOLUME);

    temp += 10;

    if (temp > S3E_SOUND_MAX_VOLUME)
        temp = S3E_SOUND_MAX_VOLUME;

    s3eSoundSetInt(S3E_SOUND_VOLUME, temp);

    sprintf(volumeString_, "`x666666Volume level: %d", temp);
}

void SoundEffect::setVolume(int32 vol)
{
	s3eSoundSetInt(S3E_SOUND_VOLUME, vol);
}

/*
	Name		SoundEffect::decreaseVolume
	Syntax		SoundEffect::decreaseVolume()
	Brief		Decreases the volume of the sound effect
*/
void SoundEffect::decreaseVolume()
{
	int32 temp = s3eSoundGetInt(S3E_SOUND_VOLUME);

    temp -= 10;

    if (temp < 0)
        temp = 0;

    s3eSoundSetInt(S3E_SOUND_VOLUME, temp);

    sprintf(volumeString_, "`x666666Volume level: %d", temp);
}