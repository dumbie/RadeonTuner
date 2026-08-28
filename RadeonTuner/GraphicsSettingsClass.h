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
	AdlSettingInt RisDesktopEnabled;
	AdlSettingInt RisSharpeningDegree;
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

	//Version
	AdlSettingVersion RisVersion;

	//Custom
	AdlSettingInt FsrShowInformation;

	//Functions (No export)
	bool Global()
	{
		return Application.has_value() && Application.value() == L"Global";
	}

	void SetCurrentToDefault()
	{
		DeLagEnabled.Current = DeLagEnabled.Default;
		MfgRatio.Current = MfgRatio.Default;
		FsrOverride.Current = FsrOverride.Default;
		MlfiOverride.Current = MlfiOverride.Default;
		MfgOverride.Current = MfgOverride.Default;
		MldOverride.Current = MldOverride.Default;
		NrcOverride.Current = NrcOverride.Default;
		FsrOvrDLLPath.Current = FsrOvrDLLPath.Default;
		FsrOtaIndex.Current = FsrOtaIndex.Default;
		FsrShowInformation.Current = FsrShowInformation.Default;
		ChillEnabled.Current = ChillEnabled.Default;
		ChillMinFps.Current = ChillMinFps.Default;
		ChillMaxFps.Current = ChillMaxFps.Default;
		FrtcEnabled.Current = FrtcEnabled.Default;
		FrtcFrameRateTarget.Current = FrtcFrameRateTarget.Default;
		BoostMode.Current = BoostMode.Default;
		BoostMinResolution.Current = BoostMinResolution.Default;
		RisEnabled.Current = RisEnabled.Default;
		RisDesktopEnabled.Current = RisDesktopEnabled.Default;
		RisSharpeningDegree.Current = RisSharpeningDegree.Default;
		VerticalSync.Current = VerticalSync.Default;
		EnhancedSync.Current = EnhancedSync.Default;
		OpenGLTripleBuffering.Current = OpenGLTripleBuffering.Default;
		AntiAliasingOverride.Current = AntiAliasingOverride.Default;
		AntiAliasingMethod.Current = AntiAliasingMethod.Default;
		AntiAliasingLevel.Current = AntiAliasingLevel.Default;
		AntiAliasingEnhancedQuality.Current = AntiAliasingEnhancedQuality.Default;
		AntiAliasingMorphological.Current = AntiAliasingMorphological.Default;
		AnisotropicOverride.Current = AnisotropicOverride.Default;
		TextureFilteringQuality.Current = TextureFilteringQuality.Default;
		SurfaceFormatOptimization.Current = SurfaceFormatOptimization.Default;
		OpenGL10BitPixelFormat.Current = OpenGL10BitPixelFormat.Default;
		TessellationMode.Current = TessellationMode.Default;
		TessellationLevel.Current = TessellationLevel.Default;
		FrameGenEnabled.Current = FrameGenEnabled.Default;
		FrameGenSearchMode.Current = FrameGenSearchMode.Default;
		FrameGenPerfMode.Current = FrameGenPerfMode.Default;
		FrameGenResponseMode.Current = FrameGenResponseMode.Default;
		FrameGenAlgorithm.Current = FrameGenAlgorithm.Default;
	}

	NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(GraphicsSettings, DeviceId, Application, DeLagEnabled.Current, MfgRatio.Current, FsrOverride.Current, MlfiOverride.Current, MfgOverride.Current, MldOverride.Current, NrcOverride.Current, FsrOvrDLLPath.Current, FsrOtaIndex.Current, FsrShowInformation.Current, ChillEnabled.Current, ChillMinFps.Current, ChillMaxFps.Current, FrtcEnabled.Current, FrtcFrameRateTarget.Current, BoostMode.Current, BoostMinResolution.Current, RisEnabled.Current, RisDesktopEnabled.Current, RisSharpeningDegree.Current, RisVersion.Version, VerticalSync.Current, EnhancedSync.Current, OpenGLTripleBuffering.Current, AntiAliasingOverride.Current, AntiAliasingMethod.Current, AntiAliasingLevel.Current, AntiAliasingEnhancedQuality.Current, AntiAliasingMorphological.Current, AnisotropicOverride.Current, TextureFilteringQuality.Current, SurfaceFormatOptimization.Current, OpenGL10BitPixelFormat.Current, TessellationMode.Current, TessellationLevel.Current, FrameGenEnabled.Current, FrameGenSearchMode.Current, FrameGenPerfMode.Current, FrameGenResponseMode.Current, FrameGenAlgorithm.Current)
};