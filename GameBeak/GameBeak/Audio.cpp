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
		samples[i] = 30000 * sin(x*6.28318);
		x += 0.0099773242630385;
	}

	//if (buffer.loadFromSamples(samples, sampleRate, 1, sampleRate))
	{
		//sound.setBuffer(buffer);
	}

	//if (buffer2.loadFromSamples(samples, sampleRate, 1, sampleRate))
	{
		//sound2.setBuffer(buffer2);
	}

	///////////////

}


Audio::~Audio()
{
}

void Audio::updateSound()
{
	byte audioControl = beakMemory.readMemory(0xFF26); //FF26: Audio Control Register.
	if ((audioControl & 0x80) > 0) //Bit 7 is master enable/disable
	{
		//Sound 1
		//sound.pause();

		int chanOneEnvelope = beakMemory.readMemory(0xFF12);

		int chanOneFreq = ((beakMemory.readMemory(0xFF14) & 7) << 8) | (beakMemory.readMemory(0xFF13));

		/*
		if ((chanOneEnvelope & 4) > 0) //If third bit enabled, subtract, else add
		{

			chanOneFreq = ((chanOneFreq - 1) - ((chanOneFreq - 1) / (pow(2, chanOneEnvelope & 0x3))));
		}
		else
		{
			chanOneFreq = ((chanOneFreq - 1) + ((chanOneFreq - 1) / (pow(2, chanOneEnvelope & 0x3))));
		}
		*/

		//sound.setPitch((float)(chanOneFreq / 400));

		//sound.setVolume(.5);

		//sound.play();

		//Sound 2

		//sound2.pause();

		int chanTwoFreq = ((beakMemory.readMemory(0xFF19) & 7) << 8) | (beakMemory.readMemory(0xFF18));

		//sound2.setPitch((float)(chanTwoFreq / 400));

		//sound2.setVolume(.5);

		//sound2.play();
		
		
	}
	else
	{
		//sound.pause();
		//sound2.pause();
	}

}