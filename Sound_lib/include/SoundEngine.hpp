#pragma once
#include <iostream>
#include <string>
#include <stdexcept>
#include <pthread.h>
#include <AL/alut.h>

class Sound {
public:
    Sound();
    Sound(const char *File);
    ~Sound();

    void initialize(std::string file_path);
    void play(int sleep, bool loop);

private:
    ALuint      _buffer;
    ALuint       _source;
    bool        _loop = true;
    pthread_t   _thread[5];

    int         _rc;
    void        *_status;
};
