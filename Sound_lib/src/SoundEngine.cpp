#include "../include/SoundEngine.hpp"

Sound::Sound()
{
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
		std::cerr << "SDL Failed to initialize" << std::endl;
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, SOUND_CHANNELS, SOUND_CHUNKSIZE) < 0)
		std::cerr << "MIXER failed to initialize" << std::endl;
	this->_waveVector.push_back(Mix_LoadWAV("Sound_lib/Sounds/music.wav")); // DEFAULT
	this->_waveVector.push_back(Mix_LoadWAV("Sound_lib/Sounds/footstep.wav")); // FOOTSTEP
	this->_waveVector.push_back(Mix_LoadWAV("Sound_lib/Sounds/death.wav")); // DEATH
	this->_waveVector.push_back(Mix_LoadWAV("Sound_lib/Sounds/explosion1.wav")); // EXPLOSION
	this->_waveVector.push_back(Mix_LoadWAV("Sound_lib/Sounds/powerup.wav")); // POWERUP
	this->_waveVector.push_back(Mix_LoadWAV("Sound_lib/Sounds/completed.wav")); // LVL_COMPLETE
	this->_waveVector.push_back(Mix_LoadWAV("Sound_lib/Sounds/placement.wav")); // BOMBPLACE
	this->_waveVector.push_back(Mix_LoadWAV("Sound_lib/Sounds/gameOver.wav")); // GAMEOVER

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

void    Sound::playSound(eSound & sound, eSound & playerSound)
{
	static int i = 0;

	this->changeVolume();
	if (playerSound == SND_FOOTSTEP && i % 10 == 0)
	{
		i = 0;
		if ( Mix_PlayChannel(-1, this->_waveVector[SND_FOOTSTEP], 0) == -1)
			std::cerr << "FAILED TO PLAY SOUND: FOOTSTEP" << std::endl; // CREATE EXCEPTION
	}
	if (playerSound == SND_DEATH)
		if ( Mix_PlayChannel(-1, this->_waveVector[SND_DEATH], 0) == -1)
			std::cerr << "FAILED TO PLAY SOUND: DEATH" << std::endl; // CREATE EXCEPTION
	if (playerSound == SND_BOMBPLACE)
		if ( Mix_PlayChannel(-1, this->_waveVector[SND_BOMBPLACE], 0) == -1)
			std::cerr << "FAILED TO PLAY SOUND: BOMB PLACE" << std::endl; // CREATE EXCEPTION
	if (playerSound == SND_GAMEOVER || sound == SND_GAMEOVER)
		if ( Mix_PlayChannel(-1, this->_waveVector[SND_GAMEOVER], 0) == -1)
			std::cerr << "FAILED TO PLAY SOUND: GAME OVER" << std::endl; // CREATE EXCEPTION
	if (playerSound == SND_POWERUP)
		if ( Mix_PlayChannel(-1, this->_waveVector[SND_POWERUP], 0) == -1)
			std::cerr << "FAILED TO PLAY SOUND: FOOTSTEP" << std::endl; // CREATE EXCEPTION
	if (sound == SND_EXPLOSION)
		if ( Mix_PlayChannel(-1, this->_waveVector[SND_EXPLOSION], 0) == -1)
			std::cerr << "FAILED TO PLAY SOUND: EXPLOSION" << std::endl; // CREATE EXCEPTION
	if (sound == SND_LVLCOMPLETE)
		if ( Mix_PlayChannel(-1, this->_waveVector[SND_LVLCOMPLETE], 0) == -1)
			std::cerr << "FAILED TO PLAY SOUND: LVL COMPLETE" << std::endl; // CREATE EXCEPTION
	sound = SND_DEFAULT;
	playerSound = SND_DEFAULT;
	if (i > 1000)
		i = 0;
	i++;
}

void	Sound::changeVolume()
{
	Mix_VolumeChunk(this->_waveVector[SND_FOOTSTEP], this->_SFXVolume * 0.3f);
	Mix_VolumeChunk(this->_waveVector[SND_DEATH], this->_SFXVolume * 0.8f);
	Mix_VolumeChunk(this->_waveVector[SND_EXPLOSION], this->_SFXVolume * 0.8f);
	Mix_VolumeChunk(this->_waveVector[SND_POWERUP], this->_SFXVolume * 0.6f);
	Mix_VolumeChunk(this->_waveVector[SND_LVLCOMPLETE], this->_SFXVolume);
	Mix_VolumeChunk(this->_waveVector[SND_BOMBPLACE], this->_SFXVolume * 0.6f);
	Mix_VolumeChunk(this->_waveVector[SND_GAMEOVER], this->_SFXVolume * 1.1);
}


void	Sound::setSFXVolume(int sfxVol)		{this->_SFXVolume = sfxVol;}
void	Sound::setMusicVolume(int muscVol)	{this->_musicVolume = muscVol;}

int &	Sound::getSFXVolume()				{return (this->_SFXVolume);}
int &	Sound::getMusicVolume()				{return (this->_musicVolume);}
std::vector<Mix_Chunk *> & Sound::getWaveVector()		{return (this->_waveVector);}