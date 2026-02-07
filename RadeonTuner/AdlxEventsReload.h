#pragma once
#include "pch.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::combobox_AntiAliasingLevel_IsEnabledChanged(IInspectable const& sender, DependencyPropertyChangedEventArgs const& e)
	{
		try
		{
			//Disable saving
			disable_saving = true;

			//Get setting value
			bool newValue = sender.as<ComboBox>().IsEnabled();

			//Select current setting
			if (newValue)
			{
				//Bug in AMD driver resets Anti-Aliasing level to wrong value so reload is needed
				//When using the override setting and set it to 8xEQ without having EQAA enabled it resets to 8x instead, picking 8xEQ in the combobox should also enable EQAA but it does not
				//To manually enable EQAA you first need to select 'Enhance Application Settings' before using 'Override Application Settings' to workaround this issue

				if (adl_AppSelected().Initialized())
				{
					//Get Anti-Aliasing Level setting
					int antiAliasSmplsValue = 0;
					AdlAppProperty adlProperty = AdlAppPropertyGet(adl_AppSelected(), L"AntiAliasSmpls");
					for (AdlAppPropertyValue value : adlProperty.Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							antiAliasSmplsValue = wstring_to_int(value.Value);
							break;
						}
					}

					bool eqaaValue = false;
					adlProperty = AdlAppPropertyGet(adl_AppSelected(), L"EQAA");
					for (AdlAppPropertyValue value : adlProperty.Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							eqaaValue = (bool)wstring_to_int(value.Value);
							break;
						}
					}

					//Enumeration index correction
					if (antiAliasSmplsValue == 2 && !eqaaValue)
					{
						combobox_AntiAliasingLevel().SelectedIndex(0);
					}
					else if (antiAliasSmplsValue == 2 && eqaaValue)
					{
						combobox_AntiAliasingLevel().SelectedIndex(1);
					}
					else if (antiAliasSmplsValue == 4 && !eqaaValue)
					{
						combobox_AntiAliasingLevel().SelectedIndex(2);
					}
					else if (antiAliasSmplsValue == 4 && eqaaValue)
					{
						combobox_AntiAliasingLevel().SelectedIndex(3);
					}
					else if (antiAliasSmplsValue == 8 && !eqaaValue)
					{
						combobox_AntiAliasingLevel().SelectedIndex(4);
					}
					else if (antiAliasSmplsValue == 8 && eqaaValue)
					{
						combobox_AntiAliasingLevel().SelectedIndex(5);
					}
				}
				else
				{
					//Get Anti-Aliasing setting
					IADLX3DAntiAliasingPtr pp3DAntiAliasing;
					adlx_Res0 = pp3DSettingsServices->GetAntiAliasing(ppGpuInfo, &pp3DAntiAliasing);

					//Get Anti-Aliasing Level
					ADLX_ANTI_ALIASING_LEVEL currentLevel;
					adlx_Res0 = pp3DAntiAliasing->GetLevel(&currentLevel);

					//Enumeration index correction
					if (currentLevel == ADLX_ANTI_ALIASING_LEVEL::AA_LEVEL_2X)
					{
						combobox_AntiAliasingLevel().SelectedIndex(0);
					}
					else if (currentLevel == ADLX_ANTI_ALIASING_LEVEL::AA_LEVEL_2XEQ)
					{
						combobox_AntiAliasingLevel().SelectedIndex(1);
					}
					else if (currentLevel == ADLX_ANTI_ALIASING_LEVEL::AA_LEVEL_4X)
					{
						combobox_AntiAliasingLevel().SelectedIndex(2);
					}
					else if (currentLevel == ADLX_ANTI_ALIASING_LEVEL::AA_LEVEL_4XEQ)
					{
						combobox_AntiAliasingLevel().SelectedIndex(3);
					}
					else if (currentLevel == ADLX_ANTI_ALIASING_LEVEL::AA_LEVEL_8X)
					{
						combobox_AntiAliasingLevel().SelectedIndex(4);
					}
					else if (currentLevel == ADLX_ANTI_ALIASING_LEVEL::AA_LEVEL_8XEQ)
					{
						combobox_AntiAliasingLevel().SelectedIndex(5);
					}
				}
			}

			//Enable saving
			disable_saving = false;
		}
		catch (...) {}
	}

	void MainPage::combobox_AnisotropicTextureFiltering_Level_IsEnabledChanged(IInspectable const& sender, DependencyPropertyChangedEventArgs const& e)
	{
		try
		{
			//Disable saving
			disable_saving = true;

			//Get setting value
			bool newValue = sender.as<ComboBox>().IsEnabled();

			//Select current setting
			if (newValue)
			{
				//Bug in AMD driver resets Anisotropic level to 2x when enabled so reload is needed

				if (adl_AppSelected().Initialized())
				{
					AdlAppProperty adlProperty = AdlAppPropertyGet(adl_AppSelected(), L"AnisoDegree");
					for (AdlAppPropertyValue value : adlProperty.Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							int convertedValue = wstring_to_int(value.Value);

							//Enumeration index correction
							if (convertedValue == 0)
							{
								combobox_AnisotropicTextureFiltering_Level().SelectedIndex(-1);
							}
							else if (convertedValue == 2)
							{
								combobox_AnisotropicTextureFiltering_Level().SelectedIndex(0);
							}
							else if (convertedValue == 4)
							{
								combobox_AnisotropicTextureFiltering_Level().SelectedIndex(1);
							}
							else if (convertedValue == 8)
							{
								combobox_AnisotropicTextureFiltering_Level().SelectedIndex(2);
							}
							else if (convertedValue == 16)
							{
								combobox_AnisotropicTextureFiltering_Level().SelectedIndex(3);
							}
							break;
						}
					}
				}
				else
				{
					//Get Anisotropic Texture Filtering setting
					IADLX3DAnisotropicFilteringPtr pp3DAnisotropicFiltering;
					adlx_Res0 = pp3DSettingsServices->GetAnisotropicFiltering(ppGpuInfo, &pp3DAnisotropicFiltering);

					//Get Anisotropic Level
					ADLX_ANISOTROPIC_FILTERING_LEVEL currentLevel;
					adlx_Res0 = pp3DAnisotropicFiltering->GetLevel(&currentLevel);

					//Enumeration index correction
					if (currentLevel == ADLX_ANISOTROPIC_FILTERING_LEVEL::AF_LEVEL_INVALID)
					{
						combobox_AnisotropicTextureFiltering_Level().SelectedIndex(-1);
					}
					else if (currentLevel == ADLX_ANISOTROPIC_FILTERING_LEVEL::AF_LEVEL_X2)
					{
						combobox_AnisotropicTextureFiltering_Level().SelectedIndex(0);
					}
					else if (currentLevel == ADLX_ANISOTROPIC_FILTERING_LEVEL::AF_LEVEL_X4)
					{
						combobox_AnisotropicTextureFiltering_Level().SelectedIndex(1);
					}
					else if (currentLevel == ADLX_ANISOTROPIC_FILTERING_LEVEL::AF_LEVEL_X8)
					{
						combobox_AnisotropicTextureFiltering_Level().SelectedIndex(2);
					}
					else if (currentLevel == ADLX_ANISOTROPIC_FILTERING_LEVEL::AF_LEVEL_X16)
					{
						combobox_AnisotropicTextureFiltering_Level().SelectedIndex(3);
					}
				}
			}

			//Enable saving
			disable_saving = false;
		}
		catch (...) {}
	}
}