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
	AdlSettingInt ColorTemperatureControl;
	AdlSettingInt ColorTemperatureKelvin;
	AdlSettingInt CVDCControl;
	AdlSettingInt CVDCProtanopia;
	AdlSettingInt CVDCDeuteranopia;
	AdlSettingInt CVDCTritanopia;
	AdlSettingInt HDCPEnabled;

	//Custom
	AdlSettingInt GammaControl{ .Current = false, .Default = false };
	AdlSettingFloat GammaBase{ .Current = 1.0F, .Default = 1.0F, .Minimum = 0.50F, .Maximum = 3.00F, .Step = 0.01F };
	AdlSettingFloat GammaRed{ .Current = 1.0F, .Default = 1.0F, .Minimum = 0.50F, .Maximum = 3.00F, .Step = 0.01F };
	AdlSettingFloat GammaGreen{ .Current = 1.0F, .Default = 1.0F, .Minimum = 0.50F, .Maximum = 3.00F, .Step = 0.01F };
	AdlSettingFloat GammaBlue{ .Current = 1.0F, .Default = 1.0F, .Minimum = 0.50F, .Maximum = 3.00F, .Step = 0.01F };
	AdlSettingInt EyefinityAutomatic{ .Current = false, .Default = false };

	//Variables (No export)
	bool UsingProfile = false;

	//Functions (No export)
	bool Global()
	{
		return Application.has_value() && Application.value() == L"Global";
	}

	void SetCurrentToDefault()
	{
		//Settings
		HdrEnabled.Current = HdrEnabled.Default;
		FreeSyncMode.Current = FreeSyncMode.Default;
		VsrEnabled.Current = VsrEnabled.Default;
		GpuScalingEnabled.Current = GpuScalingEnabled.Default;
		IntegerScalingEnabled.Current = IntegerScalingEnabled.Default;
		ScalingMode.Current = ScalingMode.Default;
		VariBrightEnabled.Current = VariBrightEnabled.Default;
		VariBrightLevel.Current = VariBrightLevel.Default;
		ColorDepth.Current = ColorDepth.Default;
		PixelFormat.Current = PixelFormat.Default;
		ColorEnhancement.Current = ColorEnhancement.Default;
		Brightness.Current = Brightness.Default;
		Contrast.Current = Contrast.Default;
		Saturation.Current = Saturation.Default;
		Hue.Current = Hue.Default;
		ColorTemperatureControl.Current = ColorTemperatureControl.Default;
		ColorTemperatureKelvin.Current = ColorTemperatureKelvin.Default;
		CVDCControl.Current = CVDCControl.Default;
		CVDCProtanopia.Current = CVDCProtanopia.Default;
		CVDCDeuteranopia.Current = CVDCDeuteranopia.Default;
		CVDCTritanopia.Current = CVDCTritanopia.Default;
		HDCPEnabled.Current = HDCPEnabled.Default;
		//Custom
		GammaControl.Current = GammaControl.Default;
		GammaBase.Current = GammaBase.Default;
		GammaRed.Current = GammaRed.Default;
		GammaGreen.Current = GammaGreen.Default;
		GammaBlue.Current = GammaBlue.Default;
		EyefinityAutomatic.Current = EyefinityAutomatic.Default;
	}

	NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(DisplaySettings, DeviceId, Application, HdrEnabled.Current, FreeSyncMode.Current, VsrEnabled.Current, GpuScalingEnabled.Current, IntegerScalingEnabled.Current, ScalingMode.Current, VariBrightEnabled.Current, VariBrightLevel.Current, ColorDepth.Current, PixelFormat.Current, ColorEnhancement.Current, Brightness.Current, Contrast.Current, Saturation.Current, Hue.Current, ColorTemperatureControl.Current, ColorTemperatureKelvin.Current, CVDCControl.Current, CVDCProtanopia.Current, CVDCDeuteranopia.Current, CVDCTritanopia.Current, HDCPEnabled.Current, GammaControl.Current, GammaBase.Current, GammaRed.Current, GammaGreen.Current, GammaBlue.Current, EyefinityAutomatic.Current)
};