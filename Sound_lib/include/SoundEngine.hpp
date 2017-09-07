#pragma once
#include <iostream>
#include <string>
#include <stdexcept>
#include <pthread.h>
#include <AL/alut.h>
#include <alc.h>

class Sound {
public:

    struct RIFF_Header {
    char chunkID[4];
    long chunkSize;//size not including chunkSize or chunkID
    char format[4];
    };

    struct WAVE_Format {
    char subChunkID[4];
    long subChunkSize;
    short audioFormat;
    short numChannels;
    long sampleRate;
    long byteRate;
    short blockAlign;
    short bitsPerSample;
    };

    struct WAVE_Data {
    char subChunkID[4]; //should contain the word data
    long subChunk2Size; //Stores the size of the data block
    };

    Sound();
    Sound(const char *File);
    ~Sound();

    void initialize(const char* File);
    bool loadWavFile(std::string filename, ALuint* buffer, ALsizei* size, ALsizei* frequency, ALenum* format);
    void play(int sleep, bool loop);

private:
    ALCdevice*  _device;
    ALCcontext* _context;
    ALuint      _buffer;
    ALuint       _source;
    ALint       _state;
    ALsizei     _size;
    ALsizei     _frequency;
    ALenum      _format;
    bool        _loop = true;
    pthread_t   _thread[5];

    int         _rc;
    void        *_status;
};
