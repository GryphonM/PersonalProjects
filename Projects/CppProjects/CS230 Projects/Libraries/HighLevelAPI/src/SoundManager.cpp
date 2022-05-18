//------------------------------------------------------------------------------
//
// File Name:	SoundManager.cpp
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	CS230 8.1.3 Assignment: Libraries
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------
#include "stdafx.h"
#include "SoundManager.h"

using namespace Beta;

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Constructor - initializes FMOD.
SoundManager::SoundManager() : BetaObject("SoundManager"), musicVolume(1), effectsVolume(1),
	audioFilePath("Audio/"), bankFilePath("Banks/"), eventPrefix("event:/"), numSounds(0),
	numBanks(0), musicChannel(nullptr), effectsChannelGroup(nullptr), system(nullptr), studioSystem(nullptr)
{
	FMOD::Studio::System::create(&studioSystem);
	studioSystem->initialize(64, FMOD_STUDIO_INIT_NORMAL, 0, nullptr);
	studioSystem->getLowLevelSystem(&system);
	system->createChannelGroup("SoundEffects", &effectsChannelGroup);
}

// Destructor
SoundManager::~SoundManager()
{
	studioSystem->release();
}

// Update the FMOD system.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void SoundManager::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);
	studioSystem->update();
}

// Shutdown the sound manager.
void SoundManager::Shutdown(void)
{
	for (size_t i = 0; i < numSounds; i++)
		soundList[i]->release();
	numSounds = 0;
	for (size_t i = 0; i < numBanks; i++)
		bankList[i]->unload();
	numBanks = 0;
}

// Creates a non-looping FMOD sound.
// Params:
//	 filename = Name of the sound file (WAV).
void SoundManager::AddEffect(const std::string& filename)
{
	AddSound(filename, FMOD_DEFAULT);
}

// Creates an FMOD stream for a music file.
// Params:
//	 filename = Name of the music file (MP3).
void SoundManager::AddMusic(const std::string& filename)
{
	AddSound(filename, FMOD_DEFAULT | FMOD_LOOP_NORMAL | FMOD_CREATESTREAM);
}

// Creates an FMOD sound bank
// Params:
//   filename = Name of the FMOD bank file.
void SoundManager::AddBank(const std::string& filename)
{
	std::string fullPath = EngineCore::GetInstance().GetFilePath() + audioFilePath + bankFilePath + filename;
	FMOD::Studio::Bank* bank;
	studioSystem->loadBankFile(fullPath.c_str(), FMOD_DEFAULT, &bank);
	numBanks++;
}

// Plays a sound with the specified name.
// Params:
//	 name = The name of the sound to be played.
// Return:
//   The channel that was used to play the given sound.
FMOD::Channel* SoundManager::PlaySound(const std::string& name_)
{
	char* soundName = new char[100];
	FMOD_MODE soundMode;

	for (int i = 0; i < numSounds; i++)
	{
		soundList[i]->getName(soundName, 100);
		if (strcmp(soundName, name_.c_str()) == 0)
		{
			soundList[i]->getMode(&soundMode);
			if (soundMode & FMOD_CREATESTREAM)
				return PlayMusic(soundList[i]);
			else
				return PlayEffect(soundList[i]);
		}
	}

	return nullptr;
}

// Starts an audio event with the given name.
// The event must be in one of the loaded banks.
// Params:
//	 name = The name of the event that will be started.
FMOD::Studio::EventInstance* SoundManager::PlayEvent(const std::string& name_)
{
	std::string fullName = eventPrefix + name_;
	FMOD::Studio::EventDescription* eventDesc;
	FMOD::Studio::EventInstance* eventInst;
	studioSystem->getEvent(fullName.c_str(), &eventDesc);
	eventDesc->createInstance(&eventInst);
	eventInst->start();
	eventInst->release();
	return eventInst;
}

// Set the volume of the music channel.
// Params:
//	 volume = New value for the music volume (0.0 to 1.0).
void SoundManager::SetMusicVolume(float volume)
{
	musicVolume = volume;
	if (musicChannel != nullptr)
		musicChannel->setVolume(volume);
}

// Set the volume of the sound effects channel group.
// Params:
//	 volume = New value for the FX volume (0.0 to 1.0).
void SoundManager::SetEffectsVolume(float volume)
{
	effectsVolume = volume;
	if (effectsChannelGroup != nullptr)
		effectsChannelGroup->setVolume(volume);
}

// Get the volume of the music channel.
// Return:
//	 volume = Current value for the music volume.
float SoundManager::GetMusicVolume() const
{
	return musicVolume;
}

// Get the volume of the sound effects channel group.
// Return:
//	 volume = Current value for the FX volume.
float SoundManager::GetEffectsVolume() const
{
	return effectsVolume;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Different behaviors for SFX vs BGM
FMOD::Channel* SoundManager::PlayEffect(FMOD::Sound* sound) const
{
	FMOD::Channel* channel;
	system->playSound(sound, effectsChannelGroup, false, &channel);
	return channel;
}
FMOD::Channel* SoundManager::PlayMusic(FMOD::Sound* sound)
{
	if (musicChannel != nullptr)
	{
		musicChannel->stop();
	}

	system->playSound(sound, nullptr, false, &musicChannel);
	return musicChannel;
}

// Add FX/BGM helper
void SoundManager::AddSound(const std::string& filename, FMOD_MODE mode)
{
	std::string fullPath = EngineCore::GetInstance().GetFilePath() + audioFilePath + filename;
	FMOD::Sound* newSound;
	system->createSound(fullPath.c_str(), mode, nullptr, &newSound);
	soundList[numSounds] = newSound;
	numSounds++;
}