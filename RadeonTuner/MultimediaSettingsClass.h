#pragma once
#include "pch.h"

struct MultimediaSettings
{
	//Settings
	SettingInt VideoUpscaling;
	SettingInt VideoSharpening;

	//Status (No export)

	NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(MultimediaSettings, VideoUpscaling.Current, VideoSharpening.Current)
};