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

		TuningFanSettings TuningFanSettings_Load(std::string loadPath);
		bool TuningFanSettings_Save(TuningFanSettings tuningFanSettings, std::string savePath);
		TuningFanSettings TuningFanSettings_Generate_FromAdlxGpuPtr(IADLXGPU2Ptr ppGpuPtr);
		TuningFanSettings TuningFanSettings_Generate_FromUI(bool keepActive);
		TuningFanSettings TuningFanSettings_Generate_FromJson(nlohmann::json jsonData);
		bool TuningFanSettings_Convert_ToUI(TuningFanSettings tuningFanSettings, bool disableUI);
		nlohmann::json TuningFanSettings_Convert_ToJson(TuningFanSettings tuningFanSettings);
		bool TuningFanSettings_Match(TuningFanSettings tuningFanSettings, TuningFanSettings tuningFanSettingsMatch);

		void AdlxValuesLoadSelectApp();
		void AdlxValuesLoadSelectPower();
		void AdlxValuesLoadSelectGpu();
		void AdlxValuesLoadSelectDisplay();
		void AdlxValuesLoadGraphics();
		void AdlxValuesLoadMultimedia();
		void AdlxValuesLoadPower();
		void AdlxValuesLoadDisplay();
		void AdlxValuesLoadTuning();
		void AdlxValuesExport();
		void AdlxValuesImport();
		void AdlxValuesPrepare();
		bool AdlxApplyTuning(IADLXGPU2Ptr ppGpuPtr, TuningFanSettings tuningFanSettings);
		bool AdlxResetTuning();
		void AdlxInfoLoad();
		void AdlxLoopMetrics();
		void AdlxLoopKeepActive();
		void RegValuesLoad();
		void UpdateFanGraph();
		void ValidateFanSettings();
		void SettingLoad();
		void SettingAdmin();
		void SelectIndexes();

		void KeepActive_Load_UI();
		bool KeepActive_Export();
		bool KeepActive_Enable();
		bool KeepActive_Disable();
		bool KeepActive_Toggle();

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
		void button_Tuning_Keep_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void button_Tuning_Keep_PointerPressed(IInspectable const& sender, PointerRoutedEventArgs const& e);
		void toggleswitch_OpenGLTripleBuffering_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_OpenGL10Bit_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_HagsSupport_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void combobox_FrameGenSearchMode_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void combobox_FrameGenPerfMode_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void combobox_FrameGenResponseMode_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void toggleswitch_Close_Tray_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void combobox_TextureFilteringQuality_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e);
		void toggleswitch_SurfaceFormatOptimization_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_Shortcut_Startup_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_Shortcut_StartMenu_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_Shortcut_ContextMenu_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
		void toggleswitch_StartWindowVisible_Toggled(IInspectable const& sender, RoutedEventArgs const& e);
	};
}

namespace winrt::RadeonTuner::factory_implementation
{
	struct MainPage : MainPageT<MainPage, implementation::MainPage>
	{
	};
}