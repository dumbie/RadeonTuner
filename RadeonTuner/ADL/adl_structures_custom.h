typedef struct ADLOD8SingleInitSettingWrap : ADLOD8SingleInitSetting
{
	bool IsSupported()
	{
		return minValue != maxValue;
	}
};

enum ADLCvdcType
{
	CVDC_ENABLED,
	CVDC_PROTANOPIA,
	CVDC_DEUTERANOPIA,
	CVDC_TRITANOPIA
};

enum OD8SettingsRegistryFlags
{
	GpuTuning = 1 << 0,
	MemoryTuning = 1 << 1,
	FanTuningOff = 1 << 5,
	FanTuningOn = 1 << 6,
	PowerTuning = 1 << 8,
	Default = 1 << 12
};

enum OD8_OPTIMZED_POWER_MODES
{
	Quiet = 0,
	Balanced = 1,
	Custom = 3,
	Rage = 4
};