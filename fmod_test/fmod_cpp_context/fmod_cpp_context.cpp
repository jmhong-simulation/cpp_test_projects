//#include "fmod.h"  // c-context
#include "fmod.hpp"
#include <iostream>

using namespace std;

int main()
{
	cout << "FMOD cpp conext example" << endl;

	FMOD::System     *system(nullptr);
	FMOD::Sound      *sound1(nullptr), *sound2(nullptr), *sound3(nullptr);
	FMOD::Channel    *channel1(nullptr), *channel2(nullptr);
	FMOD_RESULT       result;
	unsigned int      version;
	void             *extradriverdata(nullptr);

	result = FMOD::System_Create(&system);
	if (result != FMOD_OK) return -1;
	
	result = system->getVersion(&version);
	if (result != FMOD_OK) return -1;
	else printf("FMOD version %08x", version);

	result = system->init(32, FMOD_INIT_NORMAL, extradriverdata);
	if (result != FMOD_OK) return -1;

	result = system->createSound("swish.wav", FMOD_LOOP_NORMAL, 0, &sound1);
	if (result != FMOD_OK) return -1;

	result = system->createSound("wave.mp3", FMOD_DEFAULT, 0, &sound2);

	result = system->playSound(sound1, 0, false, &channel1);
	if (result != FMOD_OK) return -1;

	result = system->playSound(sound2, 0, false, &channel2);

	bool playing = false;

	while (true)
	{
		result = system->update();
		if (result != FMOD_OK) return -1;

		/*if (channel)
		{
			FMOD::Sound *currentsound = 0;

			result = channel->isPlaying(&playing);

			if (!playing) break;
		}*/

		int i;
		cin >> i;

		if (i == 0)
			channel1->setPaused(true);
		else if (i == 1)
			channel1->setPaused(false);

		if (i == 3)
			channel2->setPaused(true);
		else if (i == 4)
			channel2->setPaused(false);
	}
}
