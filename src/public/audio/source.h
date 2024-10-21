#pragma once

#include "sound.h"

namespace Audio
{

class Source
{
public:
	static constexpr char name[] = "Audio Source";

	Source();
	~Source();

	inline Resources::Sound* GetSound() { return sound; }
	void SetSound(Resources::Sound* newSound);

	void Play();

	unsigned int id { };

private:
	Resources::Sound* sound { };
};

}