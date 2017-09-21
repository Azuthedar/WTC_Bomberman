#include "../include/SoundEngine.hpp"

Sound::Sound()
{
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
		std::cerr << "SDL Failed to initialize" << std::endl;
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, SOUND_CHANNELS, SOUND_CHUNKSIZE) < 0)
		std::cerr << "MIXER failed to initialize" << std::endl;
	this->_waveVector.push_back(Mix_LoadWAV("Sound_lib/Sounds/music.wav")); // DEFAULT
	this->_waveVector.push_back(Mix_LoadWAV("Sound_lib/Sounds/Default1.wav")); // DEFAULT 1
	this->_waveVector.push_back(Mix_LoadWAV("Sound_lib/Sounds/Default2.wav")); // DEFAULT 2
	this->_waveVector.push_back(Mix_LoadWAV("Sound_lib/Sounds/Default3.wav")); // DEFAULT 3
	this->_waveVector.push_back(Mix_LoadWAV("Sound_lib/Sounds/footstep.wav")); // FOOTSTEP
	this->_waveVector.push_back(Mix_LoadWAV("Sound_lib/Sounds/death.wav")); // DEATH
	this->_waveVector.push_back(Mix_LoadWAV("Sound_lib/Sounds/explosion1.wav")); // EXPLOSION
	this->_waveVector.push_back(Mix_LoadWAV("Sound_lib/Sounds/powerup.wav")); // POWERUP
	this->_waveVector.push_back(Mix_LoadWAV("Sound_lib/Sounds/completed.wav")); // LVL_COMPLETE
	this->_waveVector.push_back(Mix_LoadWAV("Sound_lib/Sounds/placement.wav")); // BOMBPLACE
	this->_waveVector.push_back(Mix_LoadWAV("Sound_lib/Sounds/gameOver.wav")); // GAMEOVER
	this->_waveVector.push_back(Mix_LoadWAV("Sound_lib/Sounds/GateUnlocked.wav")); // GATE UNLOCKED
	this->_waveVector.push_back(Mix_LoadWAV("Sound_lib/Sounds/gateFound.wav")); // GATE FOUND
	this->_waveVector.push_back(Mix_LoadWAV("Sound_lib/Sounds/Menu.wav")); // MAIN MENU
	this->_waveVector.push_back(Mix_LoadWAV("Sound_lib/Sounds/Victory.wav")); // VICTORY

	this->_SFXVolume = 100;
	this->_musicVolume = 100;

	for (size_t i = 0; i < this->_waveVector.size(); i++)
	{
		if (this->_waveVector[i] == NULL)
			std::cerr << i << " :File was not loaded" << std::endl; // CREATE EXCEPTION
	}
}

Sound::~Sound()
{
	return ;
}

void	Sound::playMusic()
{
	Mix_VolumeChunk(this->_waveVector[SND_DEFAULT], this->_musicVolume * 0.3f);
	if ( Mix_PlayChannel(-1, this->_waveVector[SND_DEFAULT], -1) == -1)
	{
		std::cerr << "FAILED TO PLAY SOUND: MUSIC" << std::endl; // CREATE EXCEPTION
	}
}

void    Sound::playSound(eSound & sound, eSound & playerSound, eGamestate & gameState, bool & configUpdated, bool & transition)
{
	static int i = 0;
	static bool menuHasPlayed = false;
	this->changeVolume();
	if ((configUpdated && gameState == MENU) && menuHasPlayed == false)
	{
		if (Mix_Playing(0))
		{
			Mix_FadeOutChannel(0, 800);
		}
		else
		{
			Mix_PlayChannel(0, this->_waveVector[SND_MENU], -1);
			configUpdated = false;
			menuHasPlayed = true;
		}
	}
	else if ((configUpdated || transition) && gameState == GAME)
	{
		eSound random = static_cast<eSound>(std::rand() % 4);
		if (Mix_Playing(0))
		{
			Mix_FadeOutChannel(0, 800);
		}
		else
		{
			Mix_PlayChannel(0, this->_waveVector[random], -1);
			configUpdated = false;
			transition = false;
			menuHasPlayed = false;
		}
	}

	if (playerSound == SND_GAMEOVER || sound == SND_GAMEOVER)
	{
		if ( Mix_PlayChannel(1, this->_waveVector[SND_GAMEOVER], 0) == -1)
			std::cerr << "FAILED TO PLAY SOUND: GAME OVER" << std::endl; // CREATE EXCEPTION
	}
	else if (sound == SND_LVLCOMPLETE)
	{
		Mix_PlayChannel(1, this->_waveVector[SND_LVLCOMPLETE], 0);
	}
	else if (sound == SND_GATEUNLOCKED)
	{
		Mix_PlayChannel(1, this->_waveVector[SND_GATEUNLOCKED], 0);
	}
	else if (sound == SND_GATEFOUND)
	{
		Mix_PlayChannel(1, this->_waveVector[SND_GATEFOUND], 0);
	}
	else if (playerSound == SND_DEATH)
	{
		Mix_PlayChannel(-1, this->_waveVector[SND_DEATH], 0);
	}
	else if (sound == SND_EXPLOSION)
	{
		Mix_PlayChannel(-1, this->_waveVector[SND_EXPLOSION], 0);
	}
	else if (playerSound == SND_BOMBPLACE)
	{
		Mix_PlayChannel(-1, this->_waveVector[SND_BOMBPLACE], 0);
	}
	else if (playerSound == SND_POWERUP)
	{
		Mix_PlayChannel(-1, this->_waveVector[SND_POWERUP], 0);
	}
	else if (playerSound == SND_FOOTSTEP && i % 10 == 0)
	{
		i = 0;
		Mix_PlayChannel(-1, this->_waveVector[SND_FOOTSTEP], 0);
	}
	else if (sound == SND_VICTORY)
	{
		Mix_PlayChannel(1, this->_waveVector[SND_VICTORY], 0);
	}
	sound = SND_DEFAULT;
	playerSound = SND_DEFAULT;
	if (i > 1000)
		i = 0;
	i++;
}

void	Sound::changeVolume()
{
	Mix_VolumeChunk(this->_waveVector[SND_DEFAULT], this->_musicVolume * 0.5f);
	Mix_VolumeChunk(this->_waveVector[SND_DEFAULT1], this->_musicVolume * 0.5f);
	Mix_VolumeChunk(this->_waveVector[SND_DEFAULT2], this->_musicVolume * 0.5f);
	Mix_VolumeChunk(this->_waveVector[SND_DEFAULT3], this->_musicVolume * 0.5f);

	Mix_VolumeChunk(this->_waveVector[SND_FOOTSTEP], this->_SFXVolume * 0.4f);
	Mix_VolumeChunk(this->_waveVector[SND_DEATH], this->_SFXVolume * 0.8f);
	Mix_VolumeChunk(this->_waveVector[SND_EXPLOSION], this->_SFXVolume * 0.8f);
	Mix_VolumeChunk(this->_waveVector[SND_POWERUP], this->_SFXVolume * 0.6f);
	Mix_VolumeChunk(this->_waveVector[SND_LVLCOMPLETE], this->_SFXVolume);
	Mix_VolumeChunk(this->_waveVector[SND_BOMBPLACE], this->_SFXVolume * 0.6f);
	Mix_VolumeChunk(this->_waveVector[SND_GAMEOVER], this->_SFXVolume * 1.1f);
	Mix_VolumeChunk(this->_waveVector[SND_GATEUNLOCKED], this->_SFXVolume * 1.1f);
	Mix_VolumeChunk(this->_waveVector[SND_GATEFOUND], this->_SFXVolume * 0.9f);
	Mix_VolumeChunk(this->_waveVector[SND_MENU], this->_musicVolume * 0.6f);
	Mix_VolumeChunk(this->_waveVector[SND_VICTORY], this->_musicVolume * 1.2f);
}


void	Sound::setSFXVolume(int sfxVol)		{this->_SFXVolume = sfxVol;}
void	Sound::setMusicVolume(int muscVol)	{this->_musicVolume = muscVol;}

int &	Sound::getSFXVolume()				{return (this->_SFXVolume);}
int &	Sound::getMusicVolume()				{return (this->_musicVolume);}
std::vector<Mix_Chunk *> & Sound::getWaveVector()		{return (this->_waveVector);}
