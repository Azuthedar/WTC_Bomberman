#pragma once

#include <main.hpp>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

class Sound : public Exceptions
{

    public:
        Sound();
        ~Sound();

        void    playSound(eSound & sound);


    private:

        std::vector< Mix_Music *>    _musicVector;

};
