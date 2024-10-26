#include "source.h"

#include <AL/al.h>

#include <audio/manager.h>

namespace Audio
{

Source::Source()
{
	alGenSources(1, &id);
	if (Manager::CheckOpenALErr())
	{
		throw std::runtime_error("Could not create OpenAL sound source!");
	}
}

Source::~Source()
{
	alDeleteSources(1, &id);
}

void Source::SetSound(Resources::Sound* newSound)
{
	alSourcei(id, AL_BUFFER, newSound ? newSound->bufferID : 0);
	if (!Manager::CheckOpenALErr())
	{
		sound = newSound;
	}
}

void Source::Play()
{
	alSourcePlay(id);
}

}