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
    if (!alutInit(NULL, NULL)){
        std::cout << alGetError() << std::endl;
    };

    // Load pcm data into buffer
    if (!alutCreateBufferFromFile(File))
        reportError();
    else {
        std::cout << "create buffer worked" << std::endl;
        _buffer = alutCreateBufferFromFile(File);
    }
    alGenSources(1, &_source);
}
void Sound::play(int sleep, bool loop) {
    _rc = pthread_create(&_thread[2], NULL, worker, NULL);
    alSourcei(_source, AL_BUFFER, _buffer);
    if(loop == true)
        alSourcei(_source, AL_LOOPING, AL_TRUE);
    //_rc = pthread_join(_thread[1], &_status);
    alSourcePlay(_source);
}