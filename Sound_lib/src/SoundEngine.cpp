#include "../include/SoundEngine.hpp"

Sound::Sound()
{
	if (SDL_Init(SDL_INIT_AUDIO) < 1)
		std::cerr << "SDL Failed to initialize" << std::endl;
	
}

Sound::~Sound()
{
	return ;
}

void    Sound::playSound(eSound & sound)
{
	static_cast<void>(sound);
}