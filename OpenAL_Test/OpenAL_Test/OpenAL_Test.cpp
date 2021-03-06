#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>
#include <iostream>

/*
	It is very difficult to work without ALUT.
	Cannot build freealut using MSVC 2017.
	https://github.com/kcat/openal-soft/issues/117

	TODO: try alure
	https://github.com/kcat/alure
*/

using namespace std;

static void list_audio_devices(const ALCchar *devices)
{
	const ALCchar *device = devices, *next = devices + 1;
	size_t len = 0;

	fprintf(stdout, "Devices list:\n");
	fprintf(stdout, "----------\n");
	while (device && *device != '\0' && next && *next != '\0') {
		fprintf(stdout, "%s\n", device);
		len = strlen(device);
		device += (len + 1);
		next += (len + 2);
	}
	fprintf(stdout, "----------\n");
}


int main()
{
	ALCdevice *device;

	device = alcOpenDevice(NULL);
	if (!device)
	{
		cout << "al derice error" << endl;
	}

	ALboolean enumeration;

	enumeration = alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT");
	if (enumeration == AL_FALSE)
		cout << "enumeration not supported" << endl;
	else
		cout << "enumeration supported" << endl;

	list_audio_devices(alcGetString(NULL, ALC_DEVICE_SPECIFIER));

	ALCenum error;

	error = alGetError();
	if (error != AL_NO_ERROR)
	{
		cout << "Something wrong happened" << endl;
	}

	ALCcontext *context;

	context = alcCreateContext(device, NULL);
	if (!alcMakeContextCurrent(context))
		cout << "failed to make context current" << endl;

	ALfloat listenerOri[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };

	alListener3f(AL_POSITION, 0, 0, 1.0f);
	// check for errors
	alListener3f(AL_VELOCITY, 0, 0, 0);
	// check for errors
	alListenerfv(AL_ORIENTATION, listenerOri);
	// check for errors

	ALuint source;


	alGenSources((ALuint)1, &source);
	// check for errors

	alSourcef(source, AL_PITCH, 1);
	// check for errors
	alSourcef(source, AL_GAIN, 1);
	// check for errors
	alSource3f(source, AL_POSITION, 0, 0, 0);
	// check for errors
	alSource3f(source, AL_VELOCITY, 0, 0, 0);
	// check for errors
	alSourcei(source, AL_LOOPING, AL_FALSE);
	// check for errros

	ALuint buffer;

	alGenBuffers((ALuint)1, &buffer);
	// check for errors

	ALsizei size, freq;
	ALenum format;
	ALvoid *data;
	ALboolean loop = AL_FALSE;

	//alutLoadWAVFile("test.wav", &format, &data, &size, &freq, &loop);
	//// check for errors


}

