#include "audio/manager.h"

#include <stdexcept>

#include <AL/al.h>
#include <spdlog/spdlog.h>

namespace Audio
{

Manager::Manager()
{
	if (alcIsExtensionPresent(nullptr, "ALC_ENUMERATE_ALL_EXT"))
	{
		spdlog::info("Existing audio devices:");
		auto* deviceList = alcGetString(nullptr, ALC_ALL_DEVICES_SPECIFIER);
		auto* beginDeviceNameChar = deviceList;
		auto* endDeviceNameChar = beginDeviceNameChar + 1;
		
		std::vector<std::string> deviceNames;
		while (*beginDeviceNameChar != 0 && *endDeviceNameChar != 0)
		{
			endDeviceNameChar++;
			if (*endDeviceNameChar == 0)
			{
				deviceNames.emplace_back(beginDeviceNameChar, endDeviceNameChar);
				beginDeviceNameChar = endDeviceNameChar + 1;
				endDeviceNameChar = beginDeviceNameChar + 1;
			}
		}

		for (const auto& name : deviceNames)
		{
			spdlog::info("\t{}", name.c_str());
		}
		auto* defaultDevice = alcGetString(nullptr, ALC_DEFAULT_ALL_DEVICES_SPECIFIER);
		spdlog::info("Default device: {}", defaultDevice);
	}
	else
	{
		spdlog::warn("Could not find OpenAL enumeration extension.");
	}
	spdlog::info("Opening default audio device.");
	device = alcOpenDevice(nullptr);
	if (!device)
	{
		CheckOpenALErr();
		throw std::runtime_error("Could not init audio device!");
	}
	ctx = alcCreateContext(device, nullptr);
	if (!ctx) {
		CheckOpenALErr();
		throw std::runtime_error("Could not init audio context!");
	}
	alcMakeContextCurrent(ctx);
}

Manager::~Manager()
{
	if (ctx)
	{
		alcMakeContextCurrent(nullptr);
		alcDestroyContext(ctx);
		alcCloseDevice(device);
	}
}

bool Manager::CheckOpenALErr()
{
	if (auto err = alGetError(); err != AL_NO_ERROR)
	{
		spdlog::error("OpenAL error: {}", err);
		return true;
	}
	return false;
}

}