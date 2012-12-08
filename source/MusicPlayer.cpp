#include "MusicPlayer.hpp"

int32 AudioStopCallback(void* systemData, void* userData)
{
	//g_Status = STATE_STOPPED;
	return 0;
}

MusicPlayer::MusicPlayer()
{
	initialise();
}

MusicPlayer::~MusicPlayer()
{

}

void MusicPlayer::initialise()
{
	s3eAudioIsCodecSupported(S3E_AUDIO_CODEC_MP3);
	s3eAudioRegister(S3E_AUDIO_STOP, AudioStopCallback, NULL);
}

void MusicPlayer::deinitialise()
{

}

void MusicPlayer::play(const char* filename)
{
	s3eAudioPlay(filename, 0);
}

void MusicPlayer::stop()
{
	 s3eAudioStop();
}

void MusicPlayer::pause()
{
	s3eAudioPause();
}

void MusicPlayer::resume()
{
	s3eAudioResume();
}

void MusicPlayer::increaseVolume()
{
	int vol = s3eAudioGetInt(S3E_AUDIO_VOLUME);
	s3eAudioSetInt(S3E_AUDIO_VOLUME, vol+10);
}

void MusicPlayer::decreaseVolume()
{
	int vol = s3eAudioGetInt(S3E_AUDIO_VOLUME);
	s3eAudioSetInt(S3E_AUDIO_VOLUME, vol-10);
}