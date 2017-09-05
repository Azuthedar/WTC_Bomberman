#include <al.h>
#include "../include/SoundEngine.hpp"

void *worker(void *argc){
    std::cout << "playing from thread" << std::endl;
    return  argc;
}

static void reportError (void)
{
    fprintf (stderr, "ALUT error: %s\n",
             alutGetErrorString (alutGetError ()));
    exit (EXIT_FAILURE);
}

Sound::Sound() {
}

Sound::~Sound() {
    alutExit();
}

void Sound::initialize(const char* File) {

    // Initialize the environment
//    if (!alutInit(0, NULL)){
//        std::cout << "Failed to init alut" << std::endl;
//        std::cout << alGetError() << std::endl;
//    };

//    // Load pcm data into buffer
//    if (!alutCreateBufferFromFile(File)) {
//        std::cout << "Failed to create buffer from file" << std::endl;
//        reportError();
//    }
//    else {
//        std::cout << "create buffer worked" << std::endl;
//        _buffer = alutCreateBufferFromFile(File);
//    }
//    ALuint buffer = alutCreateBufferFromFile(File);
//    if (!buffer){
//        std::cout << "failed to create buffer" << std::endl;
//        reportError();
//    }
//    alGenSources(1, &_source);
    _device = alcOpenDevice(NULL);
    if(_device){
        std::cout << "device created" << std::endl;
        _context = alcCreateContext(_device,NULL);
        if(_context)
            std::cout << "context created" << std::endl;
        alcMakeContextCurrent(_context);
        std::cout << "made context current" << std::endl;

    }

}
void Sound::play(int sleep, bool loop) {
    _rc = pthread_create(&_thread[2], NULL, worker, NULL);
    alSourcei(_source, AL_BUFFER, _buffer);
    if(loop == true)
        alSourcei(_source, AL_LOOPING, AL_TRUE);
    alSourcePlay(_source);
}