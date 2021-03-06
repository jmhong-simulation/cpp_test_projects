#include "fmod.h" 
#include <iostream>

using namespace std;

/*
TODO:
- pause/resume
- multiple sounds
*/

int main()
{
	cout << "FMOD c conext example" << endl;

	//create the sound system. If fails, sound is set to impossible
	FMOD_SYSTEM  *fmodsystem = NULL;
	FMOD_CHANNEL *channel = NULL;
	FMOD_SOUND   *sound = NULL;
	FMOD_RESULT result;

	const char * currentSound = "jaguar.wav";
	
	result = FMOD_System_Create(&fmodsystem);
	if (result != FMOD_OK) return -1;
	
	result = FMOD_System_Init(fmodsystem, 2, FMOD_INIT_NORMAL, 0);
	if (result != FMOD_OK) return -1;

	//sets initial sound volume (mute)
	FMOD_Channel_SetVolume(channel, 0.0f);

	result = FMOD_Sound_Release(sound); // release if there existing sound
	result = FMOD_System_CreateStream(fmodsystem, currentSound, FMOD_DEFAULT, 0, &sound);
	if (result != FMOD_OK) return -1;

	bool pause = false;
	result = FMOD_System_PlaySound(fmodsystem, sound, nullptr, pause, &channel);
	if (result != FMOD_OK) return -1;

	FMOD_Channel_SetMode(channel, FMOD_LOOP_OFF);

	while (true)
	{
		FMOD_BOOL is_playing;
		FMOD_Channel_IsPlaying(channel, &is_playing);

		if (!is_playing) break;
	}

	result = FMOD_Sound_Release(sound);

	/*
	FMOD_BOOL p;
	FMOD_Channel_GetPaused(channel, &p);
	FMOD_Channel_SetPaused(channel, pause);
	*/
}
