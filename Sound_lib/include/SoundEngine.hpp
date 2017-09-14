#pragma once

#include <main.hpp>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#define SOUND_CHANNELS 2
#define SOUND_CHUNKSIZE 4096

class Sound : public Exceptions
{

	public:
		Sound();
		~Sound();

		void    playSound(eSound & sound, eSound & playerSound);


	private:

		std::vector< Mix_Chunk *>    _waveVector;

};
