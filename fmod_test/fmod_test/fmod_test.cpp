#include "fmod.h" 
#include <iostream>

/******** CLASS DEFINITION ********/

class Sound {
public:
	static bool on; //is sound on?
	static bool possible; //is it possible to play sound?
	static char * currentSound; //currently played sound
	//FMOD-specific stuff
	static FMOD_RESULT result;
	static FMOD_SYSTEM * fmodsystem;
	static FMOD_SOUND * sound;
	static FMOD_CHANNEL * channel;

public:
	static void initialise(void); //initialises sound

	//sound control
	static void setVolume(float v); //sets the actual playing sound's volume
	static void load(const char * filename); //loads a soundfile
	static void unload(void); //frees the sound object
	static void play(bool pause = false); //plays a sound (may be started paused; no argument for unpaused)

	//getters
	static bool getSound(void); //checks whether the sound is on

	//setters
	static void setPause(bool pause); //pause or unpause the sound
	static void setSound(bool sound); //set the sound on or off

	//toggles
	static void toggleSound(void); //toggles sound on and off
	static void togglePause(void); //toggle pause on/off
};

/******** CLASS VARIABLE DECLARATIONS ********/

bool Sound::on = true; //is sound on?
bool Sound::possible = true; //is it possible to play sound?
char * Sound::currentSound; //currently played sound
//FMOD-specific stuff
FMOD_RESULT Sound::result;
FMOD_SYSTEM * Sound::fmodsystem;
FMOD_SOUND * Sound::sound;
FMOD_CHANNEL * Sound::channel;

/******** METHODS' IMPLEMENTATIONS ********/

//initialises sound
void Sound::initialise(void) {
	//create the sound system. If fails, sound is set to impossible
	result = FMOD_System_Create(&fmodsystem);
	if (result != FMOD_OK) possible = false;
	//if initialise the sound system. If fails, sound is set to impossible
	if (possible) result = FMOD_System_Init(fmodsystem, 2, FMOD_INIT_NORMAL, 0);
	if (result != FMOD_OK) possible = false;
	//sets initial sound volume (mute)
	if (possible) FMOD_Channel_SetVolume(channel, 0.0f);
}

//sets the actual playing sound's volume
void Sound::setVolume(float v) {
	if (possible && on && v >= 0.0f && v <= 1.0f) {
		FMOD_Channel_SetVolume(channel, v);
	}
}

//loads a soundfile
void Sound::load(const char * filename) {
	currentSound = (char *)filename;
	if (possible && on) {
		result = FMOD_Sound_Release(sound);
		result = FMOD_System_CreateStream(fmodsystem, currentSound, FMOD_DEFAULT, 0, &sound);
		if (result != FMOD_OK) possible = false;
	}
}

//frees the sound object
void Sound::unload(void) {
	if (possible) {
		result = FMOD_Sound_Release(sound);
	}
}

//https://stackoverflow.com/questions/19105190/fmod-channel-free-undefined-different-version-of-fmod
//plays a sound (no argument to leave pause as dafault)
void Sound::play(bool pause) {
	if (possible && on) {
		result = FMOD_System_PlaySound(fmodsystem, sound, nullptr, pause, &channel);
		FMOD_Channel_SetMode(channel, FMOD_LOOP_OFF);
	}
}

//toggles sound on and off
void Sound::toggleSound(void) {
	on = !on;
	if (on == true) { load(currentSound); play(); }
	if (on == false) { unload(); }
}

//pause or unpause the sound
void Sound::setPause(bool pause) {
	FMOD_Channel_SetPaused(channel, pause);
}

//turn sound on or off
void Sound::setSound(bool s) {
	on = s;
}

//toggle pause on and off
void Sound::togglePause(void) {
	FMOD_BOOL p;
	FMOD_Channel_GetPaused(channel, &p);
	FMOD_Channel_SetPaused(channel, !p);
}

//tells whether the sound is on or off
bool Sound::getSound(void) {
	return on;
}

int main()
{
	Sound::initialise();
	Sound::load("jaguar.wav");
	Sound::play();

	while (true) 
	{
	
		FMOD_BOOL is_playing;
		FMOD_Channel_IsPlaying(Sound::channel, &is_playing);

		if (!is_playing) break;
	}
}
