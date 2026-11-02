#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	DWORD MainPage::AdlGammaRampClamp(float clampValue)
	{
		if (clampValue <= 0.0F) { return 0; }
		if (clampValue >= 65535.0F) { return 65535; }
		return (DWORD)clampValue;
	}

	bool MainPage::AdlGammaRampMatch(const AdlGammaRamp& gammaRampBegin, const AdlGammaRamp& gammaRampEnd)
	{
		return std::equal(std::begin(gammaRampBegin.rgb), std::end(gammaRampBegin.rgb), std::begin(gammaRampEnd.rgb));
	}

	AdlGammaRamp MainPage::AdlGammaRampBuild(float redGamma, float greenGamma, float blueGamma)
	{
		AdlGammaRamp gammaRamp{};
		try
		{
			DWORD red[256];
			DWORD green[256];
			DWORD blue[256];
			for (UINT i = 0; i < 255; i++)
			{
				//Set color channels
				float colorBase = i * 257.0F;
				red[i] = AdlGammaRampClamp(colorBase * redGamma);
				green[i] = AdlGammaRampClamp(colorBase * greenGamma);
				blue[i] = AdlGammaRampClamp(colorBase * blueGamma);

				//Pack color channels
				int colorIndex = 3 + i * 2;
				gammaRamp.rgb[colorIndex++] = (DWORD(green[i]) << 16) | DWORD(red[i]);
				gammaRamp.rgb[colorIndex++] = DWORD(blue[i]);
			}
		}
		catch (...) {}
		//Return result
		return gammaRamp;
	}

	void MainPage::AdlGammaRampConvertToFloat(AdlGammaRamp gammaRamp, float& redGamma, float& greenGamma, float& blueGamma)
	{
		try
		{
			//Get color channels
			int colorIndex = 3 + 128 * 2;
			DWORD redGreen = gammaRamp.rgb[colorIndex];
			DWORD blue = gammaRamp.rgb[colorIndex + 1];

			//Unpack color channels
			redGamma = (redGreen & 65535) / 32768.0F;
			greenGamma = (redGreen >> 16) / 32768.0F;
			blueGamma = (blue & 65535) / 32768.0F;

			//Floor color channels
			redGamma = std::floor(redGamma * 100.0F) / 100.0F;
			greenGamma = std::floor(greenGamma * 100.0F) / 100.0F;
			blueGamma = std::floor(blueGamma * 100.0F) / 100.0F;
		}
		catch (...) {}
	}

	bool MainPage::AdlGammaApply(int gpuAdapterIndex, float redGamma, float greenGamma, float blueGamma)
	{
		try
		{
			//Fix Some applications and resolution changes seem to block or reset set gamma (ADL2 wraps around SetDeviceGammaRamp) find better alternative that always works.
			//Fix Applying other settings at the same time breaks applying gamma, wait before others are set before applying gamma.
			//Fix current gamma value is unreliable when you target 1.00 it can be set to 1.01, skip matching values.

			//Reset display settings
			//ChangeDisplaySettingsW(nullptr, CDS_RESET);

			//Set temporary gamma
			//Note: Gamma value sometimes gets stuck so setting other value first may help.
			AdlGammaRamp gammaRampDefault = AdlGammaRampBuild(redGamma - 0.02F, greenGamma - 0.02F, blueGamma - 0.02F);
			adl_Res0 = _ADL2_Adapter_Gamma_Set(adl_Context, gpuAdapterIndex, gammaRampDefault);

			//Set target gamma
			AdlGammaRamp gammaRampTarget = AdlGammaRampBuild(redGamma, greenGamma, blueGamma);
			adl_Res0 = _ADL2_Adapter_Gamma_Set(adl_Context, gpuAdapterIndex, gammaRampTarget);

			//Return result
			return adl_Res0 == ADL_OK;
		}
		catch (...) {}
		return false;
	}
}