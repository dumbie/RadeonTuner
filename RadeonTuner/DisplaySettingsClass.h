#pragma once
#include "pch.h"

struct DisplaySettings
{
	//Settings
	std::optional<std::string> DeviceId;
	SettingInt HdrEnabled;
	SettingInt HdrMediaProfile;
	SettingInt FreeSyncEnabled;
	SettingInt VsrEnabled;
	SettingInt GpuScalingEnabled;
	SettingInt IntegerScalingEnabled;
	SettingInt ScalingMode;
	SettingInt VariBrightEnabled;
	SettingInt VariBrightLevel;
	SettingInt ColorDepth;
	SettingInt PixelFormat;
	SettingInt ColorEnhancement;
	SettingInt Brightness;
	SettingInt Contrast;
	SettingInt Saturation;
	SettingInt Hue;
	SettingInt ColorTemperatureControl;
	SettingInt ColorTemperatureKelvin;
	SettingInt CVDCControl;
	SettingInt CVDCProtanopia;
	SettingInt CVDCDeuteranopia;
	SettingInt CVDCTritanopia;
	SettingInt HDCPEnabled;

	//Status (No export)

	NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(DisplaySettings, DeviceId, Brightness.Current, Contrast.Current, Saturation.Current, Hue.Current, ColorTemperatureControl.Current, ColorTemperatureKelvin.Current, CVDCControl.Current, CVDCProtanopia.Current, CVDCDeuteranopia.Current, CVDCTritanopia.Current)
};