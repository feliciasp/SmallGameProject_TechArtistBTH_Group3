#include "SoundClass.h"

SoundClass::SoundClass()
{
	m_DirectSound = 0;
	m_PrimaryBuffer = 0;

	m_GameAmbientSoundBuffer = 0;
	m_MenuAmbientSoundBuffer = 0;
	m_LimboAmbientSoundBuffer = 0;
	m_BossBattleSoundBuffer = 0;
	m_WinSoundBuffer = 0;

	m_PlayerAttackSoundBuffer1 = 0;
	m_PlayerAttackSoundBuffer2 = 0;
	m_PlayerHitSoundBuffer = 0;
	m_PlayerHurtSoundBuffer = 0;
	m_PlayerStepSoundBuffer = 0;
	m_JumpSoundBuffer = 0;
	m_FireballSoundBuffer = 0;
	m_FrostboltSoundBuffer = 0;
	m_PickupRingSoundBuffer = 0;
	m_PickupXpSoundBuffer = 0;
	m_ShieldBubbleSoundBuffer = 0;
	m_BossLaughSoundBuffer = 0;
	m_PortalEntrySoundBuffer = 0;
	m_PlayerClimbSoundBuffer = 0;
	m_PlayerDodgeSoundBuffer = 0;
	m_CooldownOverSoundBuffer = 0;
	m_BossDeathSoundBuffer = 0;
	m_BossHurtSoundBuffer = 0;
	m_MonsterAttackSoundBuffer = 0;

	m_MenuButtonSoundBuffer = 0;
	m_MenuSelectSoundBuffer = 0;

	m_LimboWeaponBuySoundBuffer = 0;
	m_LimboUpSoundBuffer = 0;
	m_LimboDownSoundBuffer = 0;
	m_LimboConfirmSoundBuffer = 0;
	m_LimboCancelSoundBuffer = 0;

	isAttackBuffer1Playing = false;
	isAttackBuffer2Playing = false;
	isJumpBufferPlaying = false;
}

SoundClass::SoundClass(const SoundClass &)
{
}

SoundClass::~SoundClass()
{
}

bool SoundClass::initialize(HWND hwnd)
{
	bool result;
	bool soundAvailable = true;

	//Initalize DirectSound and primary sound buffer
	result = initializeDirectSound(hwnd);
	if (!result)
	{
		//MessageBox(NULL, L"Error init DirectSound",
		//	L"Error", MB_OK | MB_ICONERROR);
		//return false;
		soundAvailable = false;
	}
	if (soundAvailable)
	{
		//Initialize .wav files in secondary sound buffers
		//*******LOAD AMBIENT********//
		result = loadWaveFile("game_ambiance_loop.wav", &m_GameAmbientSoundBuffer);
		if (!result)
		{
			MessageBox(NULL, L"Error loading audio",
				L"Error", MB_OK | MB_ICONERROR);
			return false;
		}
		result = loadWaveFile("meny_ambiance_loop.wav", &m_MenuAmbientSoundBuffer);
		if (!result)
		{
			MessageBox(NULL, L"Error loading audio",
				L"Error", MB_OK | MB_ICONERROR);
			return false;
		}
		result = loadWaveFile("limbo_ambiance_loop.wav", &m_LimboAmbientSoundBuffer);
		if (!result)
		{
			MessageBox(NULL, L"Error loading audio",
				L"Error", MB_OK | MB_ICONERROR);
			return false;
		}
		result = loadWaveFile("boss_battle_loop.wav", &m_BossBattleSoundBuffer);
		if (!result)
		{
			MessageBox(NULL, L"Error loading audio",
				L"Error", MB_OK | MB_ICONERROR);
			return false;
		}
		result = loadWaveFile("win_loop.wav", &m_WinSoundBuffer);
		if (!result)
		{
			MessageBox(NULL, L"Error loading win",
				L"Error", MB_OK | MB_ICONERROR);
			return false;
		}
		
		//*******LOAD GAME********//
		result = loadWaveFile("miss1.wav", &m_PlayerAttackSoundBuffer1);
		if (!result)
		{
			MessageBox(NULL, L"Error loading audio",
				L"Error", MB_OK | MB_ICONERROR);
			return false;
		}
		result = loadWaveFile("miss2.wav", &m_PlayerAttackSoundBuffer2);
		if (!result)
		{
			MessageBox(NULL, L"Error loading audio",
				L"Error", MB_OK | MB_ICONERROR);
			return false;
		}
		result = loadWaveFile("monsterHit.wav", &m_PlayerHitSoundBuffer);
		if (!result)
		{
			MessageBox(NULL, L"Error loading audio",
				L"Error", MB_OK | MB_ICONERROR);
			return false;
		}
		result = loadWaveFile("hurtPlayer.wav", &m_PlayerHurtSoundBuffer);
		if (!result)
		{
			MessageBox(NULL, L"Error loading audio",
				L"Error", MB_OK | MB_ICONERROR);
			return false;
		}
		result = loadWaveFile("step2.wav", &m_PlayerStepSoundBuffer);
		if (!result)
		{
			MessageBox(NULL, L"Error loading step",
				L"Error", MB_OK | MB_ICONERROR);
			return false;
		}
		result = loadWaveFile("player_jump.wav", &m_JumpSoundBuffer);
		if (!result)
		{
			MessageBox(NULL, L"Error loading audio",
				L"Error", MB_OK | MB_ICONERROR);
			return false;
		}
		result = loadWaveFile("fireball.wav", &m_FireballSoundBuffer);
		if (!result)
		{
			MessageBox(NULL, L"Error loading audio",
				L"Error", MB_OK | MB_ICONERROR);
			return false;
		}
		result = loadWaveFile("frostbolt.wav", &m_FrostboltSoundBuffer);
		if (!result)
		{
			MessageBox(NULL, L"Error loading audio",
				L"Error", MB_OK | MB_ICONERROR);
			return false;
		}
		result = loadWaveFile("ringPickup.wav", &m_PickupRingSoundBuffer);
		if (!result)
		{
			MessageBox(NULL, L"Error loading audio",
				L"Error", MB_OK | MB_ICONERROR);
			return false;
		}
		result = loadWaveFile("xpPickup.wav", &m_PickupXpSoundBuffer);
		if (!result)
		{
			MessageBox(NULL, L"Error loading audio",
				L"Error", MB_OK | MB_ICONERROR);
			return false;
		}
		result = loadWaveFile("shieldBubble.wav", &m_ShieldBubbleSoundBuffer);
		if (!result)
		{
			MessageBox(NULL, L"Error loading SB",
				L"Error", MB_OK | MB_ICONERROR);
			return false;
		}
		result = loadWaveFile("bossLaugh.wav", &m_BossLaughSoundBuffer);
		if (!result)
		{
			MessageBox(NULL, L"Error loading BossLaugh",
				L"Error", MB_OK | MB_ICONERROR);
			return false;
		}
		result = loadWaveFile("portalEntry.wav", &m_PortalEntrySoundBuffer);
		if (!result)
		{
			MessageBox(NULL, L"Error loading portalEntry",
				L"Error", MB_OK | MB_ICONERROR);
			return false;
		}
		result = loadWaveFile("climb1.wav", &m_PlayerClimbSoundBuffer);
		if (!result)
		{
			MessageBox(NULL, L"Error loading climb1",
				L"Error", MB_OK | MB_ICONERROR);
			return false;
		}
		result = loadWaveFile("dodgePlayer.wav", &m_PlayerDodgeSoundBuffer);
		if (!result)
		{
			MessageBox(NULL, L"Error loading doge",
				L"Error", MB_OK | MB_ICONERROR);
			return false;
		}
		result = loadWaveFile("cooldownOver.wav", &m_CooldownOverSoundBuffer);
		if (!result)
		{
			MessageBox(NULL, L"Error loading CD Over",
				L"Error", MB_OK | MB_ICONERROR);
			return false;
		}
		result = loadWaveFile("bossDeath.wav", &m_BossDeathSoundBuffer);
		if (!result)
		{
			MessageBox(NULL, L"Error loading CD Over",
				L"Error", MB_OK | MB_ICONERROR);
			return false;
		}
		result = loadWaveFile("bossHurt.wav", &m_BossHurtSoundBuffer);
		if (!result)
		{
			MessageBox(NULL, L"Error loading CD Over",
				L"Error", MB_OK | MB_ICONERROR);
			return false;
		}
		result = loadWaveFile("monsterAttack.wav", &m_MonsterAttackSoundBuffer);
		if (!result)
		{
			MessageBox(NULL, L"Error loading monster attack",
				L"Error", MB_OK | MB_ICONERROR);
			return false;
		}

		//*******LOAD MENU********//
		result = loadWaveFile("meny_button.wav", &m_MenuButtonSoundBuffer);
		if (!result)
		{
			MessageBox(NULL, L"Error loading audio",
				L"Error", MB_OK | MB_ICONERROR);
			return false;
		}
		result = loadWaveFile("menySelect.wav", &m_MenuSelectSoundBuffer);
		if (!result)
		{
			MessageBox(NULL, L"Error loading menySelect",
				L"Error", MB_OK | MB_ICONERROR);
			return false;
		}

		//*******LOAD LIMBO********//
		result = loadWaveFile("weaponBought.wav", &m_LimboWeaponBuySoundBuffer);
		if (!result)
		{
			MessageBox(NULL, L"Error loading WB",
				L"Error", MB_OK | MB_ICONERROR);
			return false;
		}
		result = loadWaveFile("limbo_move_up.wav", &m_LimboUpSoundBuffer);
		if (!result)
		{
			MessageBox(NULL, L"Error loading MU",
				L"Error", MB_OK | MB_ICONERROR);
			return false;
		}
		result = loadWaveFile("limbo_move_down.wav", &m_LimboDownSoundBuffer);
		if (!result)
		{
			MessageBox(NULL, L"Error loading MD",
				L"Error", MB_OK | MB_ICONERROR);
			return false;
		}
		result = loadWaveFile("limbo_confirm.wav", &m_LimboConfirmSoundBuffer);
		if (!result)
		{
			MessageBox(NULL, L"Error loading CON",
				L"Error", MB_OK | MB_ICONERROR);
			return false;
		}
		result = loadWaveFile("limbo_cancel.wav", &m_LimboCancelSoundBuffer);
		if (!result)
		{
			MessageBox(NULL, L"Error loading CAN",
				L"Error", MB_OK | MB_ICONERROR);
			return false;
		}
	}

	return soundAvailable;
}

void SoundClass::shutdown()
{
	shutdownWaveFile(&m_GameAmbientSoundBuffer);
	shutdownWaveFile(&m_MenuAmbientSoundBuffer);
	shutdownWaveFile(&m_LimboAmbientSoundBuffer);
	shutdownWaveFile(&m_BossBattleSoundBuffer);
	shutdownWaveFile(&m_WinSoundBuffer);

	shutdownWaveFile(&m_PlayerAttackSoundBuffer1);
	shutdownWaveFile(&m_PlayerAttackSoundBuffer2);
	shutdownWaveFile(&m_PlayerHitSoundBuffer);
	shutdownWaveFile(&m_PlayerHurtSoundBuffer);
	shutdownWaveFile(&m_PlayerStepSoundBuffer);
	shutdownWaveFile(&m_JumpSoundBuffer);
	shutdownWaveFile(&m_FireballSoundBuffer);
	shutdownWaveFile(&m_FrostboltSoundBuffer);
	shutdownWaveFile(&m_PickupRingSoundBuffer);
	shutdownWaveFile(&m_PickupXpSoundBuffer);
	shutdownWaveFile(&m_ShieldBubbleSoundBuffer);
	shutdownWaveFile(&m_BossLaughSoundBuffer);
	shutdownWaveFile(&m_PortalEntrySoundBuffer);
	shutdownWaveFile(&m_PlayerClimbSoundBuffer);
	shutdownWaveFile(&m_PlayerDodgeSoundBuffer);
	shutdownWaveFile(&m_CooldownOverSoundBuffer);
	shutdownWaveFile(&m_BossDeathSoundBuffer);
	shutdownWaveFile(&m_BossHurtSoundBuffer);
	shutdownWaveFile(&m_MonsterAttackSoundBuffer);

	shutdownWaveFile(&m_MenuButtonSoundBuffer);
	shutdownWaveFile(&m_MenuSelectSoundBuffer);

	shutdownWaveFile(&m_LimboWeaponBuySoundBuffer);
	shutdownWaveFile(&m_LimboUpSoundBuffer);
	shutdownWaveFile(&m_LimboDownSoundBuffer);
	shutdownWaveFile(&m_LimboConfirmSoundBuffer);
	shutdownWaveFile(&m_LimboCancelSoundBuffer);

	shutdownDirectSound();
}

bool SoundClass::playAmbient(int gameState)
{
	bool result;
	if (gameState == 0) //MENU
	{
		m_GameAmbientSoundBuffer->Stop();
		m_LimboAmbientSoundBuffer->Stop();
		m_BossBattleSoundBuffer->Stop();
		m_WinSoundBuffer->Stop();
		playBackgroundSounds(m_MenuAmbientSoundBuffer);
	}
	else if (gameState == 1) //GAME
	{
		m_MenuAmbientSoundBuffer->Stop();
		m_LimboAmbientSoundBuffer->Stop();
		m_BossBattleSoundBuffer->Stop();
		m_WinSoundBuffer->Stop();
		playBackgroundSounds(m_GameAmbientSoundBuffer);
	}
	else if (gameState == 2) //LIMBO
	{
		m_GameAmbientSoundBuffer->Stop();
		m_MenuAmbientSoundBuffer->Stop();
		m_BossBattleSoundBuffer->Stop();
		m_WinSoundBuffer->Stop();
		playBackgroundSounds(m_LimboAmbientSoundBuffer);
	}
	else if (gameState == 3) //WIN
	{
		m_GameAmbientSoundBuffer->Stop();
		m_MenuAmbientSoundBuffer->Stop();
		m_LimboAmbientSoundBuffer->Stop();
		m_BossBattleSoundBuffer->Stop();
		playBackgroundSounds(m_WinSoundBuffer);
	}
	else if (gameState == 4) //BOSS BATTLE
	{
		m_GameAmbientSoundBuffer->Stop();
		m_MenuAmbientSoundBuffer->Stop();
		m_LimboAmbientSoundBuffer->Stop();
		m_WinSoundBuffer->Stop();
		playBackgroundSounds(m_BossBattleSoundBuffer);
	}

	return true;
}

bool SoundClass::playSFX(int gameState, int soundToPlay)
{
	if (gameState == 0) //Menu SFX
	{
		if (soundToPlay == 0) //Menu scroll
		{
			playSoundEffect(m_MenuButtonSoundBuffer);
		}
		if (soundToPlay == 1) //Start game (new and loaded)
		{
			playSoundEffect(m_MenuSelectSoundBuffer);
		}
	}
	if (gameState == 1) //Game SFX
	{
		if (soundToPlay == 0) //Player attack and miss!
		{
			if (!isAttackBuffer1Playing && isJumpBufferPlaying || !isAttackBuffer1Playing && !isJumpBufferPlaying)
			{
				playSoundEffect(m_PlayerAttackSoundBuffer1);
				isAttackBuffer1Playing = true;
			}
			else if (!isAttackBuffer2Playing && isJumpBufferPlaying || !isAttackBuffer2Playing && !isJumpBufferPlaying)
			{
				playSoundEffect(m_PlayerAttackSoundBuffer2);
				isAttackBuffer2Playing = true;
			}
		}
		if (soundToPlay == 1) //Player jump
		{
			playSoundEffect(m_JumpSoundBuffer);
			isJumpBufferPlaying = true;
		}
		if (soundToPlay == 2) //Fireball
		{
			playSoundEffect(m_FireballSoundBuffer);
		}
		if (soundToPlay == 3) //Frostbolt
		{
			playSoundEffect(m_FrostboltSoundBuffer);
		}
		if (soundToPlay == 4) //Player attack and hit!
		{
			playSoundEffect(m_PlayerHitSoundBuffer);
		}
		if (soundToPlay == 5) //Player hurt!
		{
			playSoundEffect(m_PlayerHurtSoundBuffer);
		}
		if (soundToPlay == 6) //Player step
		{
			playSoundEffect(m_PlayerStepSoundBuffer);
		}
		if (soundToPlay == 7) //Pickup ring
		{
			playSoundEffect(m_PickupRingSoundBuffer);
		}
		if (soundToPlay == 8) //Pickup ring
		{
			playSoundEffect(m_PickupXpSoundBuffer);
		}
		if (soundToPlay == 9) //Shield bubble activated
		{
			playSoundEffect(m_ShieldBubbleSoundBuffer);
		}
		if (soundToPlay == 10) //Boss rains FIREY DEATH AND DESTRUCTION upon the tiny player
		{
			playSoundEffect(m_BossLaughSoundBuffer);
		}
		if (soundToPlay == 11) //Player enters portal
		{
			playSoundEffect(m_PortalEntrySoundBuffer);
		}
		if (soundToPlay == 12) //Player climbs ladder
		{
			playSoundEffect(m_PlayerClimbSoundBuffer);
		}
		if (soundToPlay == 13) //Player dodges
		{
			playSoundEffect(m_PlayerDodgeSoundBuffer);
		}
		if (soundToPlay == 14) //Cooldown over (powers back)
		{
			playSoundEffect(m_CooldownOverSoundBuffer);
		}
		if (soundToPlay == 15) //Boss death
		{
			playSoundEffect(m_BossDeathSoundBuffer);
		}
		if (soundToPlay == 16) //Boss hurt
		{
			playSoundEffect(m_BossHurtSoundBuffer);
		}
		if (soundToPlay == 17) //Skeleton attacking
		{
			playSoundEffect(m_MonsterAttackSoundBuffer);
		}
	}

	if (gameState == 2) //Limbo SFX
	{
		if (soundToPlay == 0) //Weapon buying
		{
			playSoundEffect(m_LimboWeaponBuySoundBuffer);
		}
		if (soundToPlay == 1) //Add HP / speed
		{
			playSoundEffect(m_LimboUpSoundBuffer);
		}
		if (soundToPlay == 2) //Decrease HP / speed
		{
			playSoundEffect(m_LimboDownSoundBuffer);
		}
		if (soundToPlay == 3) //Confirm
		{
			playSoundEffect(m_LimboConfirmSoundBuffer);
		}
		if (soundToPlay == 4) //Cancel
		{
			playSoundEffect(m_LimboCancelSoundBuffer);
		}
	}
	return true;
}

bool SoundClass::initializeDirectSound(HWND hwnd)
{
	HRESULT result;
	DSBUFFERDESC bufferDesc;
	WAVEFORMATEX waveFormat;

	result = DirectSoundCreate8(NULL, &m_DirectSound, NULL);
	if (FAILED(result))
	{
		//MessageBox(NULL, L"Error getting DirectSound pointer",
		//	L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	//Set cooperative level to priority so the format of the primary sound buffer can be modified
	result = m_DirectSound->SetCooperativeLevel(hwnd, DSSCL_PRIORITY);
	if (FAILED(result))
	{
		//MessageBox(NULL, L"Error setting priority",
		//	L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	//Setup primary buffer description
	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME;
	bufferDesc.dwBufferBytes = 0;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = NULL;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	//Get control of primary sound buffer on the default sound device
	result = m_DirectSound->CreateSoundBuffer(&bufferDesc, &m_PrimaryBuffer, NULL);
	if (FAILED(result))
	{
		//MessageBox(NULL, L"Error getting primary sound buffer",
		//	L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	//Setup format of primary sound buffer
	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.nSamplesPerSec = 44100;
	waveFormat.wBitsPerSample = 16;
	waveFormat.nChannels = 2;
	waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
	waveFormat.cbSize = 0;

	//Set primary sound buffer to be specified wave format
	result = m_PrimaryBuffer->SetFormat(&waveFormat);
	if (FAILED(result))
	{
		//MessageBox(NULL, L"Error setting wave format",
		//	L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	return true;
}

void SoundClass::shutdownDirectSound()
{
	if (m_PrimaryBuffer)
	{
		m_PrimaryBuffer->Release();
		m_PrimaryBuffer = 0;
	}

	if (m_DirectSound)
	{
		m_DirectSound->Release();
		m_DirectSound = 0;
	}
}

bool SoundClass::loadWaveFile(char * filename, IDirectSoundBuffer8 ** secondaryBuffer)
{
	int error;
	FILE* filePtr;
	unsigned int count;
	WaveHeaderType waveFileHeader;
	WAVEFORMATEX waveFormat;
	DSBUFFERDESC bufferDesc;
	HRESULT result;
	IDirectSoundBuffer* tempBuffer;
	unsigned char* waveData;
	unsigned char* bufferPtr;
	unsigned long bufferSize;

	//Open wave file in binary
	error = fopen_s(&filePtr, filename, "rb");
	if (error != 0)
	{
		//MessageBox(NULL, L"Error opening wave file",
		//	L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	//Read wave file header
	count = fread(&waveFileHeader, sizeof(waveFileHeader), 1, filePtr);
	if (count != 1)
	{
		//MessageBox(NULL, L"Error reading wave file header",
		//	L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	/*CHECKS IF LOADED FILE HAS CORRECT SETTINGS*/
	
	//Check if chunkID is RIFF format
	if ((waveFileHeader.chunkID[0] != 'R') ||
		(waveFileHeader.chunkID[1] != 'I') ||
		(waveFileHeader.chunkID[2] != 'F') ||
		(waveFileHeader.chunkID[3] != 'F'))
	{
		//MessageBox(NULL, L"Error chunkID is not RIFF format",
		//	L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	//Check if format is WAVE format
	if ((waveFileHeader.format[0] != 'W') ||
		(waveFileHeader.format[1] != 'A') ||
		(waveFileHeader.format[2] != 'V') ||
		(waveFileHeader.format[3] != 'E'))
	{
		//MessageBox(NULL, L"Error format is not WAVE format",
		//	L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	//Check if subChunkID is fmt format
	if ((waveFileHeader.subChunkID[0] != 'f') ||
		(waveFileHeader.subChunkID[1] != 'm') || 
		(waveFileHeader.subChunkID[2] != 't') || 
		(waveFileHeader.subChunkID[3] != ' '))
	{
		//MessageBox(NULL, L"Error subChunkID is not fmt format",
		//	L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	//Check if audioFormat is WAVE_FORMAT_PCM
	if (waveFileHeader.audioFormat != WAVE_FORMAT_PCM)
	{
		//MessageBox(NULL, L"Error audioFormat is not WAVE_FORMAT_PCM",
		//	L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	//Check if file was recorded in stereo
	if (waveFileHeader.numChannels != 2)
	{
		//MessageBox(NULL, L"Error file not stereo",
		//	L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	//Check if file was recorded at a sample rate of 44.1 KHz
	if (waveFileHeader.sampleRate != 44100)
	{
		MessageBox(NULL, L"Error sampleRate not 44.1 KHz",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	//Check if file was recorded in 16 bit format
	if (waveFileHeader.bitsPerSample != 16)
	{
		//MessageBox(NULL, L"Error file not 16 bit format",
		//	L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	
	//Check for data chunk header
	if ((waveFileHeader.dataChunkID[0] != 'd') ||
		(waveFileHeader.dataChunkID[1] != 'a') ||
		(waveFileHeader.dataChunkID[2] != 't') ||
		(waveFileHeader.dataChunkID[3] != 'a'))
	{
		//MessageBox(NULL, L"Error data chunk header not found",
		//	L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	//Set wave format of file to be loaded
	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.nSamplesPerSec = 44100;
	waveFormat.wBitsPerSample = 16;
	waveFormat.nChannels = 2;
	waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
	waveFormat.cbSize = 0;

	//Set buffer description for secondary sound buffer
	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_CTRLVOLUME;
	bufferDesc.dwBufferBytes = waveFileHeader.dataSize;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = &waveFormat;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	//Create a temp sound buffer 
	result = m_DirectSound->CreateSoundBuffer(&bufferDesc, &tempBuffer, NULL);
	if (FAILED(result))
	{
		//MessageBox(NULL, L"Error creating temp sound buffer",
		//	L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	//Test the buffer format against the direct sound 8 interface and create the secondary buffer
	result = tempBuffer->QueryInterface(IID_IDirectSoundBuffer8, (void**)&*secondaryBuffer);
	if (FAILED(result))
	{
		//MessageBox(NULL, L"Error testing temp sound buffer",
		//	L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	tempBuffer->Release();
	tempBuffer = 0;

	//Move to beginnning of wave data which starts at the end of the data chunk header
	fseek(filePtr, sizeof(WaveHeaderType), SEEK_SET);

	//Temp buffer for file data
	waveData = new unsigned char[waveFileHeader.dataSize];
	if (!waveData)
	{
		//MessageBox(NULL, L"Error creating temp wave data buffer",
		//	L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	//Read wave file to buffer
	count = fread(waveData, 1, waveFileHeader.dataSize, filePtr);
	if (count != waveFileHeader.dataSize)
	{
		//MessageBox(NULL, L"Error reading to wave data buffer",
		//	L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	error = fclose(filePtr);
	if (error != 0)
	{
		//MessageBox(NULL, L"Error closing wave file",
		//	L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	//Lock secondary sound buffer to write wave data into it
	result = (*secondaryBuffer)->Lock(0, waveFileHeader.dataSize, (void**)&bufferPtr, (DWORD*)&bufferSize, NULL, 0, 0);
	if (FAILED(result))
	{
		//MessageBox(NULL, L"Error locking secondary sound buffer",
		//	L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	//Copy wave data into buffer
	memcpy(bufferPtr, waveData, waveFileHeader.dataSize);

	//Unlock secondary buffer after the data has been written to it
	result = (*secondaryBuffer)->Unlock((void*)bufferPtr, bufferSize, NULL, 0);
	if (FAILED(result))
	{
		//MessageBox(NULL, L"Error unlocking secondary sound buffer",
		//	L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	//Release wave data
	delete[] waveData;
	waveData = 0;

	return true;
}

void SoundClass::shutdownWaveFile(IDirectSoundBuffer8 ** secondaryBuffer)
{
	if (*secondaryBuffer)
	{
		(*secondaryBuffer)->Release();
		*secondaryBuffer = 0;
	}
}

bool SoundClass::playBackgroundSounds(IDirectSoundBuffer8* secondaryBuffer)
{
	HRESULT result;

	//Set position at the beginning of sound buffer
	result = secondaryBuffer->SetCurrentPosition(0);
	if (FAILED(result))
	{
		//MessageBox(NULL, L"Error setting start pos of secondary sound buffer",
		//	L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	//Set volume of sound buffer to 100%
	result = secondaryBuffer->SetVolume(DSBVOLUME_MAX);
	if (FAILED(result))
	{
		//MessageBox(NULL, L"Error setting volume of secondary sound buffer",
		//	L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	//Play contents of first secondary sound buffer on a loop
	result = secondaryBuffer->Play(0, 0, DSBPLAY_LOOPING);
	if (FAILED(result))
	{
		//MessageBox(NULL, L"Error playing from secondary sound buffer",
		//	L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	return true;
}

bool SoundClass::playSoundEffect(IDirectSoundBuffer8* secondaryBuffer)
{
	HRESULT result;

	//Set position at the beginning of sound buffer
	result = secondaryBuffer->SetCurrentPosition(0);
	if (FAILED(result))
	{
		//MessageBox(NULL, L"Error setting start pos of secondary sound buffer",
		//	L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	//Set volume of sound buffer to 100%
	result = secondaryBuffer->SetVolume(-500);
	if (FAILED(result))
	{
		//MessageBox(NULL, L"Error setting volume of secondary sound buffer",
		//	L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	//Play contents of secondary sound buffer, not looped
	result = secondaryBuffer->Play(0, 0, 0);
	if (FAILED(result))
	{
		//MessageBox(NULL, L"Error playing from secondary sound buffer",
		//	L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	if (isAttackBuffer1Playing)
	{
		isAttackBuffer1Playing = false;
	}
	if (isAttackBuffer2Playing)
	{
		isAttackBuffer2Playing = false;
	}
	if (isJumpBufferPlaying)
	{
		isJumpBufferPlaying = false;
	}

	return true;
}