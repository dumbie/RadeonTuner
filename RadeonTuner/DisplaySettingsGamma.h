#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	uint16_t MainPage::AdlGammaRampClamp(float clampValue)
	{
		if (clampValue <= 0.0F) { return 0; }
		if (clampValue >= 65535.0F) { return 65535; }
		return (uint16_t)clampValue;
	}

	AdlGammaRamp MainPage::AdlGammaRampBuild(float redGain, float greenGain, float blueGain)
	{
		AdlGammaRamp gammaRamp{};
		try
		{
			uint16_t red[256];
			uint16_t green[256];
			uint16_t blue[256];
			for (int i = 0; i < 256; i++)
			{
				//Set color channels
				float colorBase = i * 257;
				red[i] = AdlGammaRampClamp(colorBase * redGain);
				green[i] = AdlGammaRampClamp(colorBase * greenGain);
				blue[i] = AdlGammaRampClamp(colorBase * blueGain);

				//Pack color channels
				int colorIndex = 3 + i * 2;
				gammaRamp.rgb[colorIndex++] = (uint32_t(green[i]) << 16) | uint32_t(red[i]);
				gammaRamp.rgb[colorIndex++] = uint32_t(blue[i]);
			}
		}
		catch (...) {}
		//Return result
		return gammaRamp;
	}

	void MainPage::AdlGammaRampGet(AdlGammaRamp gammaRamp, float& redGain, float& greenGain, float& blueGain)
	{
		try
		{
			//Get color channels
			int colorIndex = 3 + 128 * 2;
			uint32_t redGreen = gammaRamp.rgb[colorIndex];
			uint32_t blue = gammaRamp.rgb[colorIndex + 1];

			//Unpack color channels
			float colorScale = 2.0F / 65535.0F;
			redGain = (redGreen & 65535) * colorScale;
			greenGain = (redGreen >> 16) * colorScale;
			blueGain = (blue & 65535) * colorScale;

			//Round color channels
			redGain = std::round(redGain * 100.0F) / 100.0F;
			greenGain = std::round(greenGain * 100.0F) / 100.0F;
			blueGain = std::round(blueGain * 100.0F) / 100.0F;
		}
		catch (...) {}
	}
}