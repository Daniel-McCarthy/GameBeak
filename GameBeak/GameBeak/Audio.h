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
	sf::SoundBuffer buffer;
};

