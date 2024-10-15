#pragma once

#include <AL/alc.h>

namespace Audio
{

class Manager
{
public:
	Manager();
	~Manager();

	static bool CheckOpenALErr();

	ALCdevice* device	{ };
	ALCcontext* ctx		{ };
};

}