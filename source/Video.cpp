/*
	Copyright	Kangaroo Magic 2012
	Created 	Elinor Townsend

	Name		Video
	Brief		The method definitions for the Video class
*/

#include <string.h>
#include <stdio.h>
#include "s3e.h"
#include "Video.hpp"

/*
	Name		Video::Video
	Syntax		Video()
	Brief		Video constructor initialises member variables
*/
Video::Video()
	: videoClip_(0), isInitialised_(false)
{

}

/*
	Name		Video::~Video
	Syntax		~Video()
	Brief		Video destructor
*/
Video::~Video()
{
}

/*
	Name		Video::initialise
	Syntax		Video::initialise(char* filename)
	Param		char* filename - The name of the file for the video clip
	Brief		Creates the video clip
*/
void Video::initialise(char* filename)
{
    videoClip_ = filename;

	bool supported = false;
	supported = s3eVideoIsCodecSupported(S3E_VIDEO_CODEC_MPEG4);
	supported = s3eVideoIsCodecSupported(S3E_VIDEO_CODEC_3GPP);
	supported = s3eVideoIsCodecSupported(S3E_VIDEO_CODEC_3GPP_VIDEO_H263);
	supported = s3eVideoIsCodecSupported(S3E_VIDEO_CODEC_3GPP_VIDEO_H264);
	supported = s3eVideoIsCodecSupported(S3E_VIDEO_CODEC_MPEG4_VIDEO_MPEG4);
	supported = s3eVideoIsCodecSupported(S3E_VIDEO_CODEC_MPEG4_VIDEO_H264);

	isInitialised_ = true;
}

/*
	Name		Video::deinitialise
	Syntax		Video::deinitialise()
	Brief		Deinitialises the sound effect
*/
void Video::deinitialise()
{
}

/*
	Name		Video::play
	Syntax		Video::play()
	Brief		Plays the video clip in full screen
*/
void Video::play()
{
	if (isInitialised_)
    {
		s3eVideoStatus state = (s3eVideoStatus)s3eVideoGetInt(S3E_VIDEO_STATUS);
		if (state == S3E_VIDEO_STOPPED)
		{
			s3eVideoPlay(videoClip_, 1, 0, 0, 1024, 768);
			s3eVideoError error = s3eVideoGetError();
			if (error == S3E_VIDEO_ERR_MEM)
				int monkey = 8;
		}

		
	}
}

/*
	Name		Video::stop
	Syntax		Video::stop()
	Brief		Stops the sound effect from playing
*/
void Video::stop()
{
	if (isInitialised_)
    {
		s3eVideoStatus state = (s3eVideoStatus)s3eVideoGetInt(S3E_VIDEO_STATUS);
		if (state == S3E_VIDEO_PLAYING || state == S3E_VIDEO_PAUSED)
		{
			s3eVideoStop();
		}
	}
}

/*
	Name		Video::pause
	Syntax		Video::pause()
	Brief		Pauses the sound effect
*/
void Video::pause()
{
	if (isInitialised_)
    {
		s3eVideoStatus state = (s3eVideoStatus)s3eVideoGetInt(S3E_VIDEO_STATUS);
		if (state == S3E_VIDEO_PLAYING)
		{
			s3eVideoPause();
		}
	}
}

/*
	Name		Video::resume
	Syntax		Video::resume()
	Brief		Resumes playing the sound effect
*/
void Video::resume()
{
	if (isInitialised_)
    {
		s3eVideoStatus state = (s3eVideoStatus)s3eVideoGetInt(S3E_VIDEO_STATUS);
		if (state == S3E_VIDEO_PAUSED)
		{
			s3eVideoResume();
		}
	}
}

/*
	Name		Video::isPlaying
	Syntax		Video::isPlaying()
	Brief		Checks if the video is currently playing
*/
bool Video::isPlaying()
{
	if (isInitialised_)
    {
		s3eVideoStatus state = (s3eVideoStatus)s3eVideoGetInt(S3E_VIDEO_STATUS);
		if (state == S3E_VIDEO_PLAYING)
		{
			return true;
		}
	}
	return false;
}