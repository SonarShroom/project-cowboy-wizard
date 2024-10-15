#include "source.h"

#include <AL/al.h>

namespace Audio
{

Source::Source()
{
	alGenSources(1, &id);
}

Source::~Source()
{
	alDeleteSources(1, &id);
}



}