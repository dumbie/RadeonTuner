#pragma once
#include "pch.h"

struct GraphicsSettings
{
	//Settings
	std::optional<int> DeLagEnabled;
	std::optional<int> MfgRatio;
	std::optional<int> FsrOverride;
	std::optional<int> MlfiOverride;
	std::optional<int> MfgOverride;
	std::optional<int> MldOverride;
	std::optional<int> NrcOverride;
	std::optional<std::wstring> FsrOvrDLLPath;
	std::optional<int> FsrOtaIndex;
	std::optional<int> ChillEnabled;
	std::optional<int> ChillMinFps;
	std::optional<int> ChillMaxFps;
	std::optional<int> FRTCEnabled;
	std::optional<int> FRTCFrameRateTarget;
	std::optional<int> BoostEnabled;
	std::optional<int> BoostMinResolution;
	std::optional<int> RisEnable;
	std::optional<int> RisSharpeningDegree;
	std::optional<int> Ris2Enable;
	std::optional<int> Ris2Desktop;
	std::optional<int> Ris2SharpeningDegree;
	std::optional<int> VSyncControl;
	std::optional<int> TurboSync;
	std::optional<int> EnableTripleBuffering;
	std::optional<int> AntiAlias;
	std::optional<int> AntiAliasMethod;
	std::optional<int> AntiAliasSamples;
	std::optional<int> EQAA;
	std::optional<int> MLF;
	std::optional<int> AnisoDegree;
	std::optional<int> TFQ;
	std::optional<int> SurfaceFormatReplacements;
	std::optional<int> OpenGL10BitPixelFormat;
	std::optional<int> TessellationMode;
	std::optional<int> TessellationLevel;
	std::optional<int> FrameGenEnabled;
	std::optional<int> FrameGenSearchMode;
	std::optional<int> FrameGenPerfMode;
	std::optional<int> FrameGenResponseMode;
	std::optional<int> FrameGenAlgorithm;

	//Defaults (No export)

	//Support (No export)

	//Interface (No export)

	NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(GraphicsSettings, DeLagEnabled, MfgRatio, FsrOverride, MlfiOverride, MfgOverride, MldOverride, NrcOverride, FsrOvrDLLPath, FsrOtaIndex, ChillEnabled, ChillMinFps, ChillMaxFps, FRTCEnabled, FRTCFrameRateTarget, BoostEnabled, BoostMinResolution, RisEnable, RisSharpeningDegree, Ris2Enable, Ris2Desktop, Ris2SharpeningDegree, VSyncControl, TurboSync, EnableTripleBuffering, AntiAlias, AntiAliasMethod, AntiAliasSamples, EQAA, MLF, AnisoDegree, TFQ, SurfaceFormatReplacements, OpenGL10BitPixelFormat, TessellationMode, TessellationLevel, FrameGenEnabled, FrameGenSearchMode, FrameGenPerfMode, FrameGenResponseMode, FrameGenAlgorithm)
};