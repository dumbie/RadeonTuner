#pragma once
#include "pch.h"

struct GraphicsSettings
{
	//Settings
	std::optional<std::wstring> DeviceId;
	std::optional<std::wstring> Application;
	AdlSettingInt DeLagEnabled;
	AdlSettingInt MfgRatio;
	AdlSettingInt FsrOverride;
	AdlSettingInt MlfiOverride;
	AdlSettingInt MfgOverride;
	AdlSettingInt MldOverride;
	AdlSettingInt NrcOverride;
	AdlSettingString FsrOvrDLLPath;
	AdlSettingInt FsrOtaIndex;
	AdlSettingInt ChillEnabled;
	AdlSettingInt ChillMinFps;
	AdlSettingInt ChillMaxFps;
	AdlSettingInt FrtcEnabled;
	AdlSettingInt FrtcFrameRateTarget;
	AdlSettingInt BoostMode;
	AdlSettingInt BoostMinResolution;
	AdlSettingInt RisEnabled;
	AdlSettingInt RisSharpeningDegree;
	AdlSettingInt Ris2Enabled;
	AdlSettingInt Ris2DesktopEnabled;
	AdlSettingInt Ris2SharpeningDegree;
	AdlSettingInt VerticalSync;
	AdlSettingInt EnhancedSync;
	AdlSettingInt OpenGLTripleBuffering;
	AdlSettingInt AntiAliasingOverride;
	AdlSettingInt AntiAliasingMethod;
	AdlSettingInt AntiAliasingLevel;
	AdlSettingInt AntiAliasingEnhancedQuality;
	AdlSettingInt AntiAliasingMorphological;
	AdlSettingInt AnisotropicOverride;
	AdlSettingInt TextureFilteringQuality;
	AdlSettingInt SurfaceFormatOptimization;
	AdlSettingInt OpenGL10BitPixelFormat;
	AdlSettingInt TessellationMode;
	AdlSettingInt TessellationLevel;
	AdlSettingInt FrameGenEnabled;
	AdlSettingInt FrameGenSearchMode;
	AdlSettingInt FrameGenPerfMode;
	AdlSettingInt FrameGenResponseMode;
	AdlSettingInt FrameGenAlgorithm;

	//Variables (No export)
	bool UsingProfile = false;

	//Functions (No export)
	bool Global()
	{
		return Application.has_value() && Application.value() == L"Global";
	}

	NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(GraphicsSettings, DeviceId, Application, DeLagEnabled.Current, MfgRatio.Current, FsrOverride.Current, MlfiOverride.Current, MfgOverride.Current, MldOverride.Current, NrcOverride.Current, FsrOvrDLLPath.Current, FsrOtaIndex.Current, ChillEnabled.Current, ChillMinFps.Current, ChillMaxFps.Current, FrtcEnabled.Current, FrtcFrameRateTarget.Current, BoostMode.Current, BoostMinResolution.Current, RisEnabled.Current, RisSharpeningDegree.Current, Ris2Enabled.Current, Ris2DesktopEnabled.Current, Ris2SharpeningDegree.Current, VerticalSync.Current, EnhancedSync.Current, OpenGLTripleBuffering.Current, AntiAliasingOverride.Current, AntiAliasingMethod.Current, AntiAliasingLevel.Current, AntiAliasingEnhancedQuality.Current, AntiAliasingMorphological.Current, AnisotropicOverride.Current, TextureFilteringQuality.Current, SurfaceFormatOptimization.Current, OpenGL10BitPixelFormat.Current, TessellationMode.Current, TessellationLevel.Current, FrameGenEnabled.Current, FrameGenSearchMode.Current, FrameGenPerfMode.Current, FrameGenResponseMode.Current, FrameGenAlgorithm.Current)
};