#pragma once

#include "resource.h"

#include <filesystem>

namespace Resources
{

class Sound : public Resource
{
public:
	static constexpr Type type = Type::SOUND;

	Sound(const std::filesystem::path path,
		const unsigned int channels,
		const std::vector<unsigned int>& pcmSamples,
		const unsigned int bufferID) :
			Resource(path.string(), Type::SOUND),
			channels(channels),
			pcmSamples(pcmSamples) { }

	~Sound();

	unsigned int channels { };
	std::vector<unsigned int> pcmSamples;
	unsigned int bufferID { };
};

}