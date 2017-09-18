#pragma once

#include "../../Game_Engine/include/main.hpp"
#include <vector>

#define SOUND_CHANNELS 2
#define SOUND_CHUNKSIZE 4096

class Sound : public Exceptions
{

	public:
		Sound();
		~Sound();

		void    playSound(eSound & sound, eSound & playerSound, eGamestate & gameState);
		void	playMusic();
		void	changeVolume();

		void	setSFXVolume(int sfxVol);
		void	setMusicVolume(int muscVol);

		int &	getSFXVolume();
		int &	getMusicVolume();
		std::vector<Mix_Chunk *> & getWaveVector();

	private:

		std::vector<Mix_Chunk *>   _waveVector;
		int							_SFXVolume;
		int							_musicVolume;

};
