#include <al.h>
#include "../include/SoundEngine.hpp"

void *worker(void *argc){
    std::cout << "playing from thread" << std::endl;
    return  argc;
}

static void reportError (std::string err)
{
    std::cout << stderr << "OPENAL ERROR: " << alGetError() << std::endl << " : " << err << std::endl;
    exit (EXIT_FAILURE);
}
bool isBigEndian()
{
    int a=1;
    return !((char*)&a)[0];
}
int convertToInt(char* buffer,int len)
{
    int a=0;
    if(!isBigEndian())
        for(int i=0;i<len;i++)
            ((char*)&a)[i]=buffer[i];
    else
        for(int i=0;i<len;i++)
            ((char*)&a)[3-i]=buffer[i];
    return a;
}

Sound::Sound() {
}

Sound::~Sound() {
    //alutExit();
    alDeleteSources(1, &_source);
    alDeleteBuffers(1, &_buffer);
}

void Sound::initialize(const char* File) {
    ALCdevice*  _device;
    ALCcontext* _context;
    alGetError();
    _device = alcOpenDevice(NULL);
    if(_device == NULL){
        reportError("Failed to open OPENAL device");
    }
    _context = alcCreateContext(_device, NULL);
    if(_context == NULL){
        reportError("Failed to create context");
    }
    alcMakeContextCurrent(_context);

    int             _channel;
    int             _sampleRate;
    int             _bps;
    int             _size;
    unsigned int    _format;
    char           *_data;

    try{
        _data = loadWAV(File, _channel, _sampleRate, _bps, _size);
    }catch (std::exception & e){
        std::cout << "Failed to load file" << e.what() <<std::endl;
    }

    alGenBuffers(1, &_buffer);
    if (_channel == 1){
        if(_bps == 8){
            _format = AL_FORMAT_MONO8;
        } else{
            _format = AL_FORMAT_MONO16;
        }
    } else{
        if(_bps == 8){
            _format = AL_FORMAT_STEREO8;
        } else{
            _format = AL_FORMAT_STEREO16;
        }
    }
    alBufferData(_buffer, _format, _data, _size, _sampleRate);

    alGenSources(1, &_source);
    std::cout << "channel: " << _channel << std::endl;
    std::cout << "samplerate: " << _sampleRate << std::endl;
    std::cout << "bps: " << _bps << std::endl;
    std::cout << "size: " << _size << std::endl;
    std::cout << "format: " << _format << std::endl;
    std::cout << "data: " << &_data << std::endl;

}

char* Sound::loadWAV(const char* fn,int& chan,int& samplerate,int& bps,int& size){
    char buffer[4];
    std::ifstream in(fn, std::ios::binary);
    in.read(buffer, 4);
    if (std::strncmp(buffer, "RIFF", 4) != 0){
        std::cout << "Not a valid WAV file" << std::endl;
        exit(1);
    }
    in.read(buffer, 4);
    in.read(buffer, 4); // WAVE
    in.read(buffer, 4); // fmt
    in.read(buffer, 4); // 16
    in.read(buffer, 2); // 1
    in.read(buffer, 2);
    chan = convertToInt(buffer, 2);
    in.read(buffer, 4);
    samplerate = convertToInt(buffer, 4);
    in.read(buffer, 4);
    in.read(buffer, 2);
    in.read(buffer, 2);
    bps = convertToInt(buffer, 2);
    in.read(buffer, 4); //data
    in.read(buffer, 4);
    size = convertToInt(buffer, 4);
    char* data = new char[size];
    in.read(data, size);

    return data;

}

void Sound::play(float volume, bool loop) {
    _rc = pthread_create(&_thread[2], NULL, worker, NULL);
    alSourcei(_source, AL_BUFFER, _buffer);
    alSourcef(_source, AL_GAIN, volume);
    float f[] = {1,0,0,0,1,0};
    alSource3f(_source,AL_POSITION,0,0,0);
    alListenerfv(AL_ORIENTATION, f);
    if(loop == true)
        alSourcei(_source, AL_LOOPING, AL_TRUE);
    alSourcePlay(_source);
}
