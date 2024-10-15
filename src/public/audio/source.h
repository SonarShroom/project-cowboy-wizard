#pragma once

#include "sound.h"

namespace Audio
{

class Source
{
public:
	Source();
	~Source();

	unsigned int id;
	Resources::Sound* sound { };
};

}