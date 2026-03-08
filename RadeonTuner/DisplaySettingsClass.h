#pragma once
#include "pch.h"

struct DisplaySettings
{
	std::optional<std::string> DeviceId;
	std::optional<int> Brightness;
	std::optional<int> Contrast;
	std::optional<int> Saturation;
	std::optional<int> Hue;

	std::optional<bool> ColorTemperatureControl;
	std::optional<int> ColorTemperatureKelvin;

	std::optional<bool> CVDCControl;
	std::optional<int> CVDCProtanopia;
	std::optional<int> CVDCDeuteranopia;
	std::optional<int> CVDCTritanopia;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(DisplaySettings, DeviceId, Brightness, Contrast, Saturation, Hue, ColorTemperatureControl, ColorTemperatureKelvin, CVDCControl, CVDCProtanopia, CVDCDeuteranopia, CVDCTritanopia)
};