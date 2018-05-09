#pragma once

#ifndef SOUNDCLASS_H
#define SOUNDCLASS_H

//Linking needed libraries
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")

#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>
#include <stdio.h>

class SoundClass
{
public:
	SoundClass();
	SoundClass(const SoundClass&);
	~SoundClass();

	bool initialize(HWND hwnd);
	void shutdown();

	bool playAmbient(int gameState);
	bool playSFX(int gameState, int soundToPlay); 

private:
	//Struct to hold info of .wav files
	struct WaveHeaderType
	{
		char chunkID[4];
		unsigned long chunkSize;
		char format[4];
		char subChunkID[4];
		unsigned long subChunkSize;
		unsigned short audioFormat;
		unsigned short numChannels;
		unsigned long sampleRate;
		unsigned long bytesPerSecond;
		unsigned short blockAlign;
		unsigned short bitsPerSample;
		char dataChunkID[4];
		unsigned long dataSize;
	};

	bool initializeDirectSound(HWND hwnd);
	void shutdownDirectSound();

	bool loadWaveFile(char* filename, IDirectSoundBuffer8** secondaryBuffer);
	void shutdownWaveFile(IDirectSoundBuffer8** secondaryBuffer);

	bool playBackgroundSounds(IDirectSoundBuffer8* secondaryBuffer);
	bool playSoundEffect(IDirectSoundBuffer8* secondaryBuffer);

	IDirectSound8* m_DirectSound;

	//Primary buffer used for playing sounds
	IDirectSoundBuffer* m_PrimaryBuffer;

	//Secondary buffer used for loading in sounds
	//If more needs to be included, we need more secondary buffers to hold those

	//Ambient sound buffers
	IDirectSoundBuffer8* m_GameAmbientSoundBuffer;
	IDirectSoundBuffer8* m_MenuAmbientSoundBuffer;
	IDirectSoundBuffer8* m_LimboAmbientSoundBuffer;

	//SFX buffers
	IDirectSoundBuffer8* m_PlayerAttackSoundBuffer;
	IDirectSoundBuffer8* m_FireballSoundBuffer;
	IDirectSoundBuffer8* m_JumpSoundBuffer;
	IDirectSoundBuffer8* m_MenuButtonSoundBuffer;
};

#endif