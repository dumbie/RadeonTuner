#pragma once
#include "pch.h"

struct DisplaySettings
{
	//Settings
	std::optional<std::wstring> DeviceId;
	std::optional<std::wstring> Application;
	AdlSettingInt HdrEnabled;
	AdlSettingInt FreeSyncMode;
	AdlSettingInt VsrEnabled;
	AdlSettingInt GpuScalingEnabled;
	AdlSettingInt IntegerScalingEnabled;
	AdlSettingInt ScalingMode;
	AdlSettingInt VariBrightEnabled;
	AdlSettingInt VariBrightLevel;
	AdlSettingInt ColorDepth;
	AdlSettingInt PixelFormat;
	AdlSettingInt ColorEnhancement;
	AdlSettingInt Brightness;
	AdlSettingInt Contrast;
	AdlSettingInt Saturation;
	AdlSettingInt Hue;
	AdlSettingFloat GammaRed;
	AdlSettingFloat GammaGreen;
	AdlSettingFloat GammaBlue;
	AdlSettingInt ColorTemperatureControl;
	AdlSettingInt ColorTemperatureKelvin;
	AdlSettingInt CVDCControl;
	AdlSettingInt CVDCProtanopia;
	AdlSettingInt CVDCDeuteranopia;
	AdlSettingInt CVDCTritanopia;
	AdlSettingInt HDCPEnabled;

	//Custom
	AdlSettingInt EyefinityAutomatic;

	//Variables (No export)
	bool UsingProfile = false;

	//Functions (No export)
	bool Global()
	{
		return Application.has_value() && Application.value() == L"Global";
	}

	NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(DisplaySettings, DeviceId, Application, HdrEnabled.Current, FreeSyncMode.Current, VsrEnabled.Current, GpuScalingEnabled.Current, IntegerScalingEnabled.Current, ScalingMode.Current, VariBrightEnabled.Current, VariBrightLevel.Current, ColorDepth.Current, PixelFormat.Current, ColorEnhancement.Current, Brightness.Current, Contrast.Current, Saturation.Current, Hue.Current, GammaRed.Current, GammaGreen.Current, GammaBlue.Current, ColorTemperatureControl.Current, ColorTemperatureKelvin.Current, CVDCControl.Current, CVDCProtanopia.Current, CVDCDeuteranopia.Current, CVDCTritanopia.Current, HDCPEnabled.Current, EyefinityAutomatic.Current)
};