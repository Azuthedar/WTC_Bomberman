#pragma once
#include <iostream>
#include <string>
#include <stdexcept>
#include <pthread.h>
#include <AL/alut.h>
#include <alc.h>

class Sound {
public:
    Sound();
    Sound(const char *File);
    ~Sound();

    void initialize(const char* File);
    void play(int sleep, bool loop);

private:
    ALCdevice*  _device;
    ALCcontext* _context;
    ALuint      _buffer;
    ALuint       _source;
    bool        _loop = true;
    pthread_t   _thread[5];

    int         _rc;
    void        *_status;
};
