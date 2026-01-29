#pragma once
#include "pch.h"

struct DisplaySettings
{
	std::optional<std::string> DeviceId;
	std::optional<bool> FreeSync;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(DisplaySettings, DeviceId, FreeSync)
};