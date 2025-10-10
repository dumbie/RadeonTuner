#pragma once
#include "MainPage.g.h"

namespace winrt::RadeonTuner::implementation
{
	struct MainPage : MainPageT<MainPage>
	{
		MainPage() {}

		std::wstring AdlInitialize();
		void AdlValuesPrepare();

		std::wstring AdlxInitialize();
		std::wstring AdlxGetDeviceIdentifier(IADLXGPU2Ptr ppGpuPtr);

		TuningFanSettings Generate_TuningFanSettings();
		TuningFanSettings Generate_TuningFanSettings(nlohmann::json jsonData);
		nlohmann::json Generate_TuningFanSettings(TuningFanSettings tuningFanSettings);

		void AdlxValuesLoadSelectApp();
		void AdlxValuesLoadSelectPower();
		void AdlxValuesLoadSelectGpu();
		void AdlxValuesLoadSelectDisplay();
		void AdlxValuesLoadFans();
		void AdlxValuesLoadGraphics();
		void AdlxValuesLoadMultimedia();
		void AdlxValuesLoadPower();
		void AdlxValuesLoadDisplay();
		void AdlxValuesLoadTuning();
		void AdlxValuesExport(std::string exportPath);
		void AdlxValuesImport();
		void AdlxValuesPrepare();
		bool AdlxApplyTuning(TuningFanSettings tuningFanSettings);
		bool AdlxResetTuning();
		void AdlxInfoLoad();
		void AdlxLoopMetrics();
		void AdlxLoopOverclock();
		void RegValuesLoad();
		void UpdateFanGraph();
		void ValidateFanSettings();
		void SettingCheck();
		void SettingLoad();
		void SelectIndexes();

		void page_Loaded(IInspectable const& sender, RoutedEventArgs const& e);
		void listbox_Main_SelectionChanged(IInspectable const& sender, Controls::SelectionChangedEventArgs const& e);
		void button_Tuning_Apply_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Tuning_Reset_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Tuning_Import_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Tuning_Export_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Website_Project_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Website_Donation_Click(IInspectable const& sender, RoutedEventArgs const& e);

		void combobox_VerticalRefresh_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void toggleswitch_RadeonChill_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void slider_RadeonChill_Min_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void slider_RadeonChill_Max_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void toggleswitch_RadeonEnhancedSync_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_FreeSync_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void combobox_Display_ColorDepth_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void combobox_Display_PixelFormat_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void slider_Fan_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void slider_Display_Contrast_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void slider_Display_Saturation_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void toggleswitch_RadeonSuperResolution_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void slider_RadeonSuperResolution_Sharpening_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void toggleswitch_RadeonAntiLag_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Reset_Shader_Cache_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_RadeonBoost_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void slider_RadeonBoost_MinRes_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void toggleswitch_RadeonFluidMotionFrames_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_RadeonImageSharpening_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void slider_RadeonImageSharpening_Sharpening_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void toggleswitch_Frtc_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void slider_Frtc_Max_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void combobox_AntiAliasingMode_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void combobox_AntiAliasingMethod_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void combobox_AntiAliasingLevel_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void toggleswitch_MorphologicAntiAliasing_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_AnisotropicTextureFiltering_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void combobox_AnisotropicTextureFilteringQuality_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void combobox_Tessellation_Mode_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void combobox_Tessellation_Level_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void toggleswitch_VSR_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_RadeonSharpenDesktop_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_GPUScaling_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_IntegerScaling_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void combobox_Display_ScalingMode_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void toggleswitch_HDCPSupport_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_VariBright_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void combobox_Display_VariBright_Level_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void slider_Display_ColorTemperature_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void slider_Display_Brightness_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void slider_Display_Hue_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void button_Reset_ColorTemperature_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void slider_VideoUpscale_Sharpening_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void toggleswitch_VideoUpscale_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_VideoSuperResolution_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_FreeSyncColorAccuracy_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void slider_Display_RelativeVoltageSwing_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void slider_Display_RelativePreEmphasis_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void toggleswitch_DynamicRefreshRateControl_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_SmartShiftEco_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void combobox_SmartShiftMaxMode_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void slider_SmartShiftMaxBias_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e);
		void toggleswitch_Window_Top_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Check_Update_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void combobox_GpuSelect_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void combobox_DisplaySelect_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void combobox_AppSelect_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void button_Fps_Overlayer_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_Fan_Zero_Rpm_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_ActiveOverclock_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Tuning_Keep_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_OpenGLTripleBuffering_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
	};
}

namespace winrt::RadeonTuner::factory_implementation
{
	struct MainPage : MainPageT<MainPage, implementation::MainPage>
	{
	};
}