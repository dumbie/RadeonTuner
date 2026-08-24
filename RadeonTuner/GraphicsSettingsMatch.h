#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::GraphicsSettings_Match(GraphicsSettings settingsProfile, GraphicsSettings settingsAdl)
	{
		try
		{
			if (settingsProfile.AnisotropicOverride.Current.has_value() && settingsAdl.AnisotropicOverride.Current.has_value())
			{
				if (settingsProfile.AnisotropicOverride.Current.value() != settingsAdl.AnisotropicOverride.Current.value()) { return false; }
			}

			if (settingsProfile.AntiAliasingEnhancedQuality.Current.has_value() && settingsAdl.AntiAliasingEnhancedQuality.Current.has_value())
			{
				if (settingsProfile.AntiAliasingEnhancedQuality.Current.value() != settingsAdl.AntiAliasingEnhancedQuality.Current.value()) { return false; }
			}

			if (settingsProfile.AntiAliasingLevel.Current.has_value() && settingsAdl.AntiAliasingLevel.Current.has_value())
			{
				if (settingsProfile.AntiAliasingLevel.Current.value() != settingsAdl.AntiAliasingLevel.Current.value()) { return false; }
			}

			if (settingsProfile.AntiAliasingMethod.Current.has_value() && settingsAdl.AntiAliasingMethod.Current.has_value())
			{
				if (settingsProfile.AntiAliasingMethod.Current.value() != settingsAdl.AntiAliasingMethod.Current.value()) { return false; }
			}

			if (settingsProfile.AntiAliasingMorphological.Current.has_value() && settingsAdl.AntiAliasingMorphological.Current.has_value())
			{
				if (settingsProfile.AntiAliasingMorphological.Current.value() != settingsAdl.AntiAliasingMorphological.Current.value()) { return false; }
			}

			if (settingsProfile.AntiAliasingOverride.Current.has_value() && settingsAdl.AntiAliasingOverride.Current.has_value())
			{
				if (settingsProfile.AntiAliasingOverride.Current.value() != settingsAdl.AntiAliasingOverride.Current.value()) { return false; }
			}

			if (settingsProfile.BoostMinResolution.Current.has_value() && settingsAdl.BoostMinResolution.Current.has_value())
			{
				if (settingsProfile.BoostMinResolution.Current.value() != settingsAdl.BoostMinResolution.Current.value()) { return false; }
			}

			if (settingsProfile.BoostMode.Current.has_value() && settingsAdl.BoostMode.Current.has_value())
			{
				if (settingsProfile.BoostMode.Current.value() != settingsAdl.BoostMode.Current.value()) { return false; }
			}

			if (settingsProfile.ChillEnabled.Current.has_value() && settingsAdl.ChillEnabled.Current.has_value())
			{
				if (settingsProfile.ChillEnabled.Current.value() != settingsAdl.ChillEnabled.Current.value()) { return false; }
			}

			if (settingsProfile.ChillMaxFps.Current.has_value() && settingsAdl.ChillMaxFps.Current.has_value())
			{
				if (settingsProfile.ChillMaxFps.Current.value() != settingsAdl.ChillMaxFps.Current.value()) { return false; }
			}

			if (settingsProfile.ChillMinFps.Current.has_value() && settingsAdl.ChillMinFps.Current.has_value())
			{
				if (settingsProfile.ChillMinFps.Current.value() != settingsAdl.ChillMinFps.Current.value()) { return false; }
			}

			if (settingsProfile.DeLagEnabled.Current.has_value() && settingsAdl.DeLagEnabled.Current.has_value())
			{
				if (settingsProfile.DeLagEnabled.Current.value() != settingsAdl.DeLagEnabled.Current.value()) { return false; }
			}

			if (settingsProfile.EnhancedSync.Current.has_value() && settingsAdl.EnhancedSync.Current.has_value())
			{
				if (settingsProfile.EnhancedSync.Current.value() != settingsAdl.EnhancedSync.Current.value()) { return false; }
			}

			if (settingsProfile.FrameGenEnabled.Current.has_value() && settingsAdl.FrameGenEnabled.Current.has_value())
			{
				if (settingsProfile.FrameGenEnabled.Current.value() != settingsAdl.FrameGenEnabled.Current.value()) { return false; }
			}

			if (settingsProfile.FrameGenSearchMode.Current.has_value() && settingsAdl.FrameGenSearchMode.Current.has_value())
			{
				if (settingsProfile.FrameGenSearchMode.Current.value() != settingsAdl.FrameGenSearchMode.Current.value()) { return false; }
			}

			if (settingsProfile.FrameGenPerfMode.Current.has_value() && settingsAdl.FrameGenPerfMode.Current.has_value())
			{
				if (settingsProfile.FrameGenPerfMode.Current.value() != settingsAdl.FrameGenPerfMode.Current.value()) { return false; }
			}

			if (settingsProfile.FrameGenResponseMode.Current.has_value() && settingsAdl.FrameGenResponseMode.Current.has_value())
			{
				if (settingsProfile.FrameGenResponseMode.Current.value() != settingsAdl.FrameGenResponseMode.Current.value()) { return false; }
			}

			if (settingsProfile.FrameGenAlgorithm.Current.has_value() && settingsAdl.FrameGenAlgorithm.Current.has_value())
			{
				if (settingsProfile.FrameGenAlgorithm.Current.value() != settingsAdl.FrameGenAlgorithm.Current.value()) { return false; }
			}

			if (settingsProfile.FrtcEnabled.Current.has_value() && settingsAdl.FrtcEnabled.Current.has_value())
			{
				if (settingsProfile.FrtcEnabled.Current.value() != settingsAdl.FrtcEnabled.Current.value()) { return false; }
			}

			if (settingsProfile.FrtcFrameRateTarget.Current.has_value() && settingsAdl.FrtcFrameRateTarget.Current.has_value())
			{
				if (settingsProfile.FrtcFrameRateTarget.Current.value() != settingsAdl.FrtcFrameRateTarget.Current.value()) { return false; }
			}

			if (settingsProfile.FsrOtaIndex.Current.has_value() && settingsAdl.FsrOtaIndex.Current.has_value())
			{
				if (settingsProfile.FsrOtaIndex.Current.value() != settingsAdl.FsrOtaIndex.Current.value()) { return false; }
			}

			if (settingsProfile.FsrOverride.Current.has_value() && settingsAdl.FsrOverride.Current.has_value())
			{
				if (settingsProfile.FsrOverride.Current.value() != settingsAdl.FsrOverride.Current.value()) { return false; }
			}

			if (settingsProfile.FsrOvrDLLPath.Current.has_value() && settingsAdl.FsrOvrDLLPath.Current.has_value())
			{
				if (settingsProfile.FsrOvrDLLPath.Current.value() != settingsAdl.FsrOvrDLLPath.Current.value()) { return false; }
			}

			if (settingsProfile.FsrShowInformation.Current.has_value() && settingsAdl.FsrShowInformation.Current.has_value())
			{
				if (settingsProfile.FsrShowInformation.Current.value() != settingsAdl.FsrShowInformation.Current.value()) { return false; }
			}

			if (settingsProfile.MfgOverride.Current.has_value() && settingsAdl.MfgOverride.Current.has_value())
			{
				if (settingsProfile.MfgOverride.Current.value() != settingsAdl.MfgOverride.Current.value()) { return false; }
			}

			if (settingsProfile.MfgRatio.Current.has_value() && settingsAdl.MfgRatio.Current.has_value())
			{
				if (settingsProfile.MfgRatio.Current.value() != settingsAdl.MfgRatio.Current.value()) { return false; }
			}

			if (settingsProfile.MldOverride.Current.has_value() && settingsAdl.MldOverride.Current.has_value())
			{
				if (settingsProfile.MldOverride.Current.value() != settingsAdl.MldOverride.Current.value()) { return false; }
			}

			if (settingsProfile.MlfiOverride.Current.has_value() && settingsAdl.MlfiOverride.Current.has_value())
			{
				if (settingsProfile.MlfiOverride.Current.value() != settingsAdl.MlfiOverride.Current.value()) { return false; }
			}

			if (settingsProfile.NrcOverride.Current.has_value() && settingsAdl.NrcOverride.Current.has_value())
			{
				if (settingsProfile.NrcOverride.Current.value() != settingsAdl.NrcOverride.Current.value()) { return false; }
			}

			if (settingsProfile.OpenGL10BitPixelFormat.Current.has_value() && settingsAdl.OpenGL10BitPixelFormat.Current.has_value())
			{
				if (settingsProfile.OpenGL10BitPixelFormat.Current.value() != settingsAdl.OpenGL10BitPixelFormat.Current.value()) { return false; }
			}

			if (settingsProfile.OpenGLTripleBuffering.Current.has_value() && settingsAdl.OpenGLTripleBuffering.Current.has_value())
			{
				if (settingsProfile.OpenGLTripleBuffering.Current.value() != settingsAdl.OpenGLTripleBuffering.Current.value()) { return false; }
			}

			if (settingsProfile.Ris2DesktopEnabled.Current.has_value() && settingsAdl.Ris2DesktopEnabled.Current.has_value())
			{
				if (settingsProfile.Ris2DesktopEnabled.Current.value() != settingsAdl.Ris2DesktopEnabled.Current.value()) { return false; }
			}

			if (settingsProfile.Ris2Enabled.Current.has_value() && settingsAdl.Ris2Enabled.Current.has_value())
			{
				if (settingsProfile.Ris2Enabled.Current.value() != settingsAdl.Ris2Enabled.Current.value()) { return false; }
			}

			if (settingsProfile.Ris2SharpeningDegree.Current.has_value() && settingsAdl.Ris2SharpeningDegree.Current.has_value())
			{
				if (settingsProfile.Ris2SharpeningDegree.Current.value() != settingsAdl.Ris2SharpeningDegree.Current.value()) { return false; }
			}

			if (settingsProfile.RisEnabled.Current.has_value() && settingsAdl.RisEnabled.Current.has_value())
			{
				if (settingsProfile.RisEnabled.Current.value() != settingsAdl.RisEnabled.Current.value()) { return false; }
			}

			if (settingsProfile.RisSharpeningDegree.Current.has_value() && settingsAdl.RisSharpeningDegree.Current.has_value())
			{
				if (settingsProfile.RisSharpeningDegree.Current.value() != settingsAdl.RisSharpeningDegree.Current.value()) { return false; }
			}

			if (settingsProfile.SurfaceFormatOptimization.Current.has_value() && settingsAdl.SurfaceFormatOptimization.Current.has_value())
			{
				if (settingsProfile.SurfaceFormatOptimization.Current.value() != settingsAdl.SurfaceFormatOptimization.Current.value()) { return false; }
			}

			if (settingsProfile.TessellationMode.Current.has_value() && settingsAdl.TessellationMode.Current.has_value())
			{
				if (settingsProfile.TessellationMode.Current.value() != settingsAdl.TessellationMode.Current.value()) { return false; }
			}

			if (settingsProfile.TessellationLevel.Current.has_value() && settingsAdl.TessellationLevel.Current.has_value())
			{
				if (settingsProfile.TessellationLevel.Current.value() != settingsAdl.TessellationLevel.Current.value()) { return false; }
			}

			if (settingsProfile.TextureFilteringQuality.Current.has_value() && settingsAdl.TextureFilteringQuality.Current.has_value())
			{
				if (settingsProfile.TextureFilteringQuality.Current.value() != settingsAdl.TextureFilteringQuality.Current.value()) { return false; }
			}

			if (settingsProfile.VerticalSync.Current.has_value() && settingsAdl.VerticalSync.Current.has_value())
			{
				if (settingsProfile.VerticalSync.Current.value() != settingsAdl.VerticalSync.Current.value()) { return false; }
			}
		}
		catch (...) {}
		return true;
	}
}