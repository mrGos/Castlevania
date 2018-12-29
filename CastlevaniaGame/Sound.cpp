#include "Sound.h"

#if MEMORY_LEAK_DEBUG == 1
#include <vld.h>
#endif

WAVEFORMATEX Sound::bufferFormat_;
DSBUFFERDESC Sound::bufferDescription_;
LPDIRECTSOUND8 Sound::audioHandler_;
HWND Sound::windowsHandler_;

// -----------------------------------------------
// Name: T6_Sound::T6_Sound()
// Desc: Get the audio Name and Path, ready to load.
// -----------------------------------------------
Sound::Sound(const char* audioPath)
{
	loadAudio(audioPath);
}



Sound::~Sound(void)
{
	soundBuffer_->Stop();
}


// -----------------------------------------------
// Name: T6_Sound::initializeSoundClass()
// Desc: Initialize the basic PROPERTIESs for loading audio
// -----------------------------------------------
HRESULT Sound::initializeSoundClass(HWND windowsHandler)
{
	windowsHandler_ = windowsHandler;

	HRESULT result;
	result = DirectSoundCreate8(0, &audioHandler_, 0);
	result = result | audioHandler_->SetCooperativeLevel(windowsHandler_, DSSCL_PRIORITY);

	ZeroMemory(&bufferFormat_, sizeof(WAVEFORMATEX));
	ZeroMemory(&bufferDescription_, sizeof(DSBUFFERDESC));

	bufferFormat_.wFormatTag = AUDIO_FORMAT_TAG;
	bufferFormat_.nChannels = AUDIO_NUM_OF_CHANNEL;
	bufferFormat_.nSamplesPerSec = AUDIO_SAMPLE_SPEED;
	bufferFormat_.wBitsPerSample = AUDIO_BITS_PER_SAMPLE;
	bufferFormat_.nBlockAlign = AUDIO_BLOCK_ALIGN(bufferFormat_.wBitsPerSample,
		bufferFormat_.nChannels);
	bufferFormat_.nAvgBytesPerSec = AUDIO_AVERAGE_BPS(bufferFormat_.nSamplesPerSec,
		bufferFormat_.nBlockAlign);

	bufferDescription_.dwFlags = AUDIO_FLAGS;
	bufferDescription_.guid3DAlgorithm = AUDIO_GUID;
	bufferDescription_.dwSize = sizeof(DSBUFFERDESC);

	return result;
}


// -----------------------------------------------
// Name: T6_Sound::releaseSoundClass()
// Desc: Release the basic PROPERTIES after used (close game).
// -----------------------------------------------
HRESULT Sound::releaseSoundClass()
{
	if (audioHandler_ != 0)
		return audioHandler_->Release();

	return S_OK;
}


// -----------------------------------------------
// Name: T6_Sound::loadAudio()
// Desc: Load the Audio stored in audioPath.
// -----------------------------------------------
wchar_t* convert(const char* str)
{
	int n = strlen(str);
	wchar_t*s = new wchar_t[n+1];
	for (int i = 0;i < n;i++)
		s[i] = str[i];
	s[n] = 0;
	return s;
}
HRESULT Sound::loadAudio(const char* audioPath_)
{
	HRESULT result;
	CWaveFile audioObject;
	result = audioObject.Open((char*)audioPath_, 0, 1);

	if (!FAILED(result)) {

		bufferDescription_.dwBufferBytes = audioObject.GetSize();
		bufferDescription_.lpwfxFormat = audioObject.m_pwfx;

		result = audioHandler_->CreateSoundBuffer(&bufferDescription_, &soundBuffer_, 0);

		VOID* pointerToLockedBuffer = 0;
		DWORD lockedSize = 0;
		result = result | (soundBuffer_)->Lock(0, AUDIO_BUFFER_SIZE, &pointerToLockedBuffer,
			&lockedSize, 0, 0, DSBLOCK_ENTIREBUFFER);

		if (!FAILED(result)) {
			DWORD readedData = 0;
			audioObject.ResetFile();
			result = audioObject.Read((BYTE*)pointerToLockedBuffer, lockedSize, &readedData);
			if (!FAILED(result)) {
				(soundBuffer_)->Unlock(pointerToLockedBuffer, lockedSize, 0, 0);
			}
		}
	}

	audioObject.Close();
	return result;
}


// -----------------------------------------------
// T6_Sound::play()
// Desc: Play loaded audio, may choose loop or no.
// -----------------------------------------------
HRESULT Sound::play(bool isLoop, DWORD priority)
{
	return soundBuffer_->Play(0, priority, isLoop & DSBPLAY_LOOPING);
}


// -----------------------------------------------
// T6_Sound:stop()
// Desc: Stop the audio if it is playing.
// -----------------------------------------------
HRESULT Sound::stop()
{
	HRESULT result = soundBuffer_->Stop();
	soundBuffer_->SetCurrentPosition(0);
	return result;
}