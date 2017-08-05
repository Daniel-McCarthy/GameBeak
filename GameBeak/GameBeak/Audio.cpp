//#include "Audio.h"
#include "Main.h"
#include <Windows.h>

using namespace std;
/*
Sound Bank 1 (Tone & Sweep):
FF10 Sweep
FF11 Length
FF12 Volume
FF13 Low Frequency
FF14 High Frequency

Sound Bank 2 (Tone):
FF15 ENT
FF16 LEN
FF17 ENV
FF18 FRQ
FF19 KIK

Sound Bank 3 (Wave):
FF1A ENT
FF1B LEN
FF1C ENV
FF1D FRQ
FF1E KIK

Sound Bank 4 (Noise):
FF1F ENT
FF20 LEN
FF21 ENV
FF22 FRQ
FF23 KIK

FF24 Volume
FF25 L/R Channel
FF26 ON/OFF
*/


Audio::Audio()
{

	/////////////////

	const int sampleRate = 44100;
	double x = 0;
	short samples[sampleRate];

	for (int i = 0; i < sampleRate; i++) {
		samples[i] = 30000 * cos(x*6.28318);
		x += 0.0099773242630385;
	}

	if (buffer.loadFromSamples(samples, sampleRate, 1, sampleRate))
	{
		sound.setBuffer(buffer);
	}

	///////////////

}


Audio::~Audio()
{
}

void Audio::updateSound()
{
	sound.setPitch(1);
	//sound.setLoop(1);
	int chanTwoFreq = ((beakMemory.readMemory(0xFF19) & 7) << 8) | (beakMemory.readMemory(0xFF18));
	int chanOneFreq = ((beakMemory.readMemory(0xFF14) & 7) << 8) | (beakMemory.readMemory(0xFF13));
	sound.setPitch((float)(chanTwoFreq / 400));
	//sound.setPitch((float)(chanTwoFreq / 400));
	//sound.setPitch( (float)(131072/(2048 - chanTwoFreq) + .0001) );
	//sound.setPitch((float)(1 / ((2048 - chanTwoFreq) * 4) + .0001));
	sound.setVolume(.5);
	sound.play();
	//Beep();

}