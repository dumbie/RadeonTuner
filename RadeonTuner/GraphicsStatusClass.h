#pragma once
#include "pch.h"

struct GraphicsStatus
{
	int ProcessId = -1;
	std::wstring ProcessName = L"";
	std::wstring RenderApi = L"";
	bool FsrOverrideUpscaling = false;
	bool FsrOverrideFrameGeneration = false;
	bool FsrOverrideMultiFrameGeneration = false;
	bool FsrOverrideRayRegenerationDenoiser = false;
	bool FsrOverrideNeuralRadianceCaching = false;
	bool Boost = false;
	bool Chill = false;
	bool AntiLag = false;
	bool SuperResolution = false;
	bool ImageSharpening1 = false;
	bool ImageSharpening2 = false;
	bool FluidMotionFrames = false;
	bool FluidMotionFramesValidApi = false;
};