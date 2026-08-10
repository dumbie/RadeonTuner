#pragma once
#include "pch.h"

struct MultimediaSettings
{
	//Settings
	std::optional<std::wstring> DeviceId;
	std::optional<std::wstring> Application;
	AdlSettingInt VideoUpscaling;
	AdlSettingInt VideoSharpening;
	AdlSettingInt VideoBrightness;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(MultimediaSettings, DeviceId, Application, VideoUpscaling.Current, VideoSharpening.Current, VideoBrightness.Current)
};