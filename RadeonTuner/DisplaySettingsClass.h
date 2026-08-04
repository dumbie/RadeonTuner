#pragma once
#include "pch.h"

struct DisplaySettings
{
	//Settings
	std::optional<std::wstring> DeviceId;
	std::optional<std::wstring> Application;
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
	SettingFloat GammaRed;
	SettingFloat GammaGreen;
	SettingFloat GammaBlue;
	SettingInt ColorTemperatureControl;
	SettingInt ColorTemperatureKelvin;
	SettingInt CVDCControl;
	SettingInt CVDCProtanopia;
	SettingInt CVDCDeuteranopia;
	SettingInt CVDCTritanopia;
	SettingInt HDCPEnabled;

	//Custom
	SettingInt EyefinityAutomatic;

	//Variables (No export)
	bool UsingProfile = false;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(DisplaySettings, DeviceId, Application, ColorEnhancement.Current, Brightness.Current, Contrast.Current, Saturation.Current, Hue.Current, GammaRed.Current, GammaGreen.Current, GammaBlue.Current, ColorTemperatureControl.Current, ColorTemperatureKelvin.Current, CVDCControl.Current, CVDCProtanopia.Current, CVDCDeuteranopia.Current, CVDCTritanopia.Current)
};