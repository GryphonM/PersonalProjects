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
	studioSystem->initialize(1, FMOD_STUDIO_INIT_NORMAL, 0, nullptr);
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
	AddSound(filename, FMOD_DEFAULT | FMOD_LOOP_NORMAL);
}

// Creates an FMOD sound bank
// Params:
//   filename = Name of the FMOD bank file.
void SoundManager::AddBank(const std::string& filename)
{
	std::string fullPath = "Assets/" + audioFilePath + bankFilePath + filename;
	FMOD::Studio::Bank* bank;
	studioSystem->loadBankFile(fullPath, FMOD_DEFAULT, &bank);
	numBanks++;
}