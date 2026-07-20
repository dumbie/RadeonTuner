#pragma once
#include "pch.h"

struct GraphicsSettings
{
	//Settings
	SettingInt DeLagEnabled;
	SettingInt MfgRatio;
	SettingInt FsrOverride;
	SettingInt MlfiOverride;
	SettingInt MfgOverride;
	SettingInt MldOverride;
	SettingInt NrcOverride;
	SettingString FsrOvrDLLPath;
	SettingInt FsrOtaIndex;
	SettingInt ChillEnabled;
	SettingInt ChillMinFps;
	SettingInt ChillMaxFps;
	SettingInt FrtcEnabled;
	SettingInt FrtcFrameRateTarget;
	SettingInt BoostEnabled;
	SettingInt BoostMinResolution;
	SettingInt RisEnabled;
	SettingInt RisSharpeningDegree;
	SettingInt Ris2Enabled;
	SettingInt Ris2DesktopEnabled;
	SettingInt Ris2SharpeningDegree;
	SettingInt VerticalSync;
	SettingInt EnhancedSync;
	SettingInt OpenGLTripleBuffering;
	SettingInt AntiAliasingOverride;
	SettingInt AntiAliasingMethod;
	SettingInt AntiAliasingLevel;
	SettingInt AntiAliasingEnhancedQuality;
	SettingInt AntiAliasingMorphological;
	SettingInt AnisotropicOverride;
	SettingInt TextureFilteringQuality;
	SettingInt SurfaceFormatOptimization;
	SettingInt OpenGL10BitPixelFormat;
	SettingInt TessellationMode;
	SettingInt TessellationLevel;
	SettingInt FrameGenEnabled;
	SettingInt FrameGenSearchMode;
	SettingInt FrameGenPerfMode;
	SettingInt FrameGenResponseMode;
	SettingInt FrameGenAlgorithm;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(GraphicsSettings, DeLagEnabled.Current, MfgRatio.Current, FsrOverride.Current, MlfiOverride.Current, MfgOverride.Current, MldOverride.Current, NrcOverride.Current, FsrOvrDLLPath.Current, FsrOtaIndex.Current, ChillEnabled.Current, ChillMinFps.Current, ChillMaxFps.Current, FrtcEnabled.Current, FrtcFrameRateTarget.Current, BoostEnabled.Current, BoostMinResolution.Current, RisEnabled.Current, RisSharpeningDegree.Current, Ris2Enabled.Current, Ris2DesktopEnabled.Current, Ris2SharpeningDegree.Current, VerticalSync.Current, EnhancedSync.Current, OpenGLTripleBuffering.Current, AntiAliasingOverride.Current, AntiAliasingMethod.Current, AntiAliasingLevel.Current, AntiAliasingEnhancedQuality.Current, AntiAliasingMorphological.Current, AnisotropicOverride.Current, TextureFilteringQuality.Current, SurfaceFormatOptimization.Current, OpenGL10BitPixelFormat.Current, TessellationMode.Current, TessellationLevel.Current, FrameGenEnabled.Current, FrameGenSearchMode.Current, FrameGenPerfMode.Current, FrameGenResponseMode.Current, FrameGenAlgorithm.Current)
};