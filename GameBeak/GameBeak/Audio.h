#include <SFML\Audio.hpp>
#include "Memory.h"

#pragma once
class Audio
{
public:
	Audio();
	~Audio();
	void updateSound();

	sf::Sound sound;
	sf::Sound sound2;
	sf::SoundBuffer buffer;
	sf::SoundBuffer buffer2;
};

