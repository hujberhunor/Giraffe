#include <stdio.h>
#include <string.h>
#include <portaudio.h>
#include <sndfile.h>


/* DEFINES */
#define INPUT_CHANNELS 0
#define OUTPUT_CHANNELS 2

/* STRUCTS */
typedef struct
{
	SNDFILE* file;
	SF_INFO	info;
} pa_callback_data_t;

/* FUNCTIONS */
static int initialize_audio_data();
static PaError initialize_port_audio();
static void play_audio();
static PaError clean_up();

/* CALLBACKS 
static int pa_stream_callback(const void*, void*, unsigned long, const PaStreamCallbackTimeInfo*, PaStreamCallbackFlags, void*);

/* VARIABLES */
static pa_callback_data_t _audioData;
static PaStream* _stream = NULL;



static int initialize_audio_data(){
	_audioData.file = sf_open("../giraffe/Goran Bregović - Kalashnikov.wav", SFM_READ, &_audioData.info);
	return sf_error(_audioData.file);
}

static PaError initialize_port_audio()
{
	PaError error = SF_ERR_NO_ERROR;

	error = Pa_Initialize();
	if (error) { return error; }

	error = Pa_OpenDefaultStream(&_stream, INPUT_CHANNELS, OUTPUT_CHANNELS, paFloat32, _audioData.info.samplerate,
		paFramesPerBufferUnspecified, pa_stream_callback, &_audioData);
	if (error) { return error; }

	return paNoError;
}

int main() {

  return 0;
}
