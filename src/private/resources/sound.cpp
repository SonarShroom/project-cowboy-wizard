#include "sound.h"

#include <AL/al.h>

namespace Resources
{

Sound::~Sound()
{
	alDeleteBuffers(1, &bufferID);
}

}