#pragma once
#include "pch.h"

struct DisplaySettings
{
	std::optional<std::string> DeviceId;
	std::optional<int> ColorTemperature;
	std::optional<int> Brightness;
	std::optional<int> Contrast;
	std::optional<int> Saturation;
	std::optional<int> Hue;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(DisplaySettings, DeviceId, ColorTemperature, Brightness, Contrast, Saturation, Hue)
};