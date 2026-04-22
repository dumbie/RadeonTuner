#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::toggleswitch_Fan_Control_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			ToggleSwitch senderElement = sender.as<ToggleSwitch>();
			bool fanControl = senderElement.IsOn();

			//Enable or disable interface
			toggleswitch_Fan_Zero_Rpm().IsEnabled(fanControl);
			slider_Fan_Speed_0().IsEnabled(fanControl);
			slider_Fan_Temp_0().IsEnabled(fanControl);
			slider_Fan_Speed_1().IsEnabled(fanControl);
			slider_Fan_Temp_1().IsEnabled(fanControl);
			slider_Fan_Speed_2().IsEnabled(fanControl);
			slider_Fan_Temp_2().IsEnabled(fanControl);
			slider_Fan_Speed_3().IsEnabled(fanControl);
			slider_Fan_Temp_3().IsEnabled(fanControl);
			slider_Fan_Speed_4().IsEnabled(fanControl);
			slider_Fan_Temp_4().IsEnabled(fanControl);

			//Update fan graph opacity
			grid_Fan_Graph().Opacity(fanControl ? 1.0 : 0.4);
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_Fan_Zero_Rpm_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			ToggleSwitch senderElement = sender.as<ToggleSwitch>();
			if (senderElement.IsOn())
			{
				//Show or hide Zero RPM line
				grid_Fan_Zero_Rpm_Line_Profile().Visibility(Visibility::Visible);
			}
			else
			{
				//Show or hide Zero RPM line
				grid_Fan_Zero_Rpm_Line_Profile().Visibility(Visibility::Collapsed);
			}
		}
		catch (...) {}
	}

	void MainPage::slider_Fan_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Fix prevent setvalue exception without thread workaround
			std::function<void()> threadVoid = [&]()
				{
					std::function<void()> invokeVoid = [&]
						{
							ValidateFanSettings();
							UpdateFanGraphProfile();
						};
					AppVariables::App.DispatcherInvoke(invokeVoid);
				};
			std::thread thread(threadVoid);
			thread.detach();
		}
		catch (...) {}
	}

	void MainPage::ValidateFanSettings()
	{
		try
		{
			//Fix cleanup and improve method

			//Validate fan speed
			float fanSpeed0 = slider_Fan_Speed_0().Value();
			float fanSpeed1 = slider_Fan_Speed_1().Value();
			float fanSpeed2 = slider_Fan_Speed_2().Value();
			float fanSpeed3 = slider_Fan_Speed_3().Value();
			float fanSpeed4 = slider_Fan_Speed_4().Value();

			if (fanSpeed4 < fanSpeed3)
			{
				slider_Fan_Speed_4().Value(fanSpeed3);
			}
			if (fanSpeed3 < fanSpeed2)
			{
				slider_Fan_Speed_3().Value(fanSpeed2);
			}
			if (fanSpeed3 > fanSpeed4)
			{
				slider_Fan_Speed_3().Value(fanSpeed4);
			}
			if (fanSpeed2 < fanSpeed1)
			{
				slider_Fan_Speed_2().Value(fanSpeed1);
			}
			if (fanSpeed2 > fanSpeed3)
			{
				slider_Fan_Speed_2().Value(fanSpeed3);
			}
			if (fanSpeed1 < fanSpeed0)
			{
				slider_Fan_Speed_1().Value(fanSpeed0);
			}
			if (fanSpeed1 > fanSpeed2)
			{
				slider_Fan_Speed_1().Value(fanSpeed2);
			}
			if (fanSpeed0 > fanSpeed1)
			{
				slider_Fan_Speed_0().Value(fanSpeed1);
			}

			//Validate fan temperature
			float fanTempOffset = 5;
			float fanTemp0 = slider_Fan_Temp_0().Value();
			float fanTemp1 = slider_Fan_Temp_1().Value();
			float fanTemp2 = slider_Fan_Temp_2().Value();
			float fanTemp3 = slider_Fan_Temp_3().Value();
			float fanTemp4 = slider_Fan_Temp_4().Value();

			float fanTempMax0 = fanTemp1 - fanTempOffset;
			float fanTempMin1 = fanTemp0 + fanTempOffset;
			float fanTempMax1 = fanTemp2 - fanTempOffset;
			float fanTempMin2 = fanTemp1 + fanTempOffset;
			float fanTempMax2 = fanTemp3 - fanTempOffset;
			float fanTempMin3 = fanTemp2 + fanTempOffset;
			float fanTempMax3 = fanTemp4 - fanTempOffset;
			float fanTempMin4 = fanTemp3 + fanTempOffset;

			if (fanTemp4 < fanTempMin4)
			{
				slider_Fan_Temp_4().Value(fanTempMin4);
			}
			if (fanTemp3 < fanTempMin3)
			{
				slider_Fan_Temp_3().Value(fanTempMin3);
			}
			if (fanTemp3 > fanTempMax3)
			{
				slider_Fan_Temp_3().Value(fanTempMax3);
			}
			if (fanTemp2 < fanTempMin2)
			{
				slider_Fan_Temp_2().Value(fanTempMin2);
			}
			if (fanTemp2 > fanTempMax2)
			{
				slider_Fan_Temp_2().Value(fanTempMax2);
			}
			if (fanTemp1 < fanTempMin1)
			{
				slider_Fan_Temp_1().Value(fanTempMin1);
			}
			if (fanTemp1 > fanTempMax1)
			{
				slider_Fan_Temp_1().Value(fanTempMax1);
			}
			if (fanTemp0 > fanTempMax0)
			{
				slider_Fan_Temp_0().Value(fanTempMax0);
			}

			//Set result
			//AVDebugWriteLine("ADLX validated fan settings.");
		}
		catch (...) {}
	}

	void MainPage::UpdateFanGraphGpu(TuningFanSettings tuningFanSettings)
	{
		try
		{
			//Speed vertical Y
			//Temperature horizontal X
			PointCollection fanPoints;

			//Get minimum and maximum
			int fanSpeedMinimum = tuningFanSettings.FanSpeedMin0.value();
			int fanSpeedMaximum = tuningFanSettings.FanSpeedMax0.value();

			//Get graph size
			int graphWidth = 500;
			int graphHeight = 100;

			//Add fan points
			float fanSpeedStart = fanSpeedMaximum - tuningFanSettings.FanSpeed0.value();
			float fanTempStart = 0;
			fanPoints.Append(Point{ fanTempStart, fanSpeedStart });

			float fanSpeed0 = fanSpeedMaximum - tuningFanSettings.FanSpeed0.value();
			float fanTemp0 = (double)tuningFanSettings.FanTemp0.value() / 100 * graphWidth;
			fanPoints.Append(Point{ fanTemp0, fanSpeed0 });

			float fanSpeed1 = fanSpeedMaximum - tuningFanSettings.FanSpeed1.value();
			float fanTemp1 = (double)tuningFanSettings.FanTemp1.value() / 100 * graphWidth;
			fanPoints.Append(Point{ fanTemp1, fanSpeed1 });

			float fanSpeed2 = fanSpeedMaximum - tuningFanSettings.FanSpeed2.value();
			float fanTemp2 = (double)tuningFanSettings.FanTemp2.value() / 100 * graphWidth;
			fanPoints.Append(Point{ fanTemp2, fanSpeed2 });

			float fanSpeed3 = fanSpeedMaximum - tuningFanSettings.FanSpeed3.value();
			float fanTemp3 = (double)tuningFanSettings.FanTemp3.value() / 100 * graphWidth;
			fanPoints.Append(Point{ fanTemp3, fanSpeed3 });

			float fanSpeed4 = fanSpeedMaximum - tuningFanSettings.FanSpeed4.value();
			float fanTemp4 = (double)tuningFanSettings.FanTemp4.value() / 100 * graphWidth;
			fanPoints.Append(Point{ fanTemp4, fanSpeed4 });

			float fanSpeedEnd = fanSpeedMaximum - tuningFanSettings.FanSpeed4.value();
			float fanTempEnd = graphWidth;
			fanPoints.Append(Point{ fanTempEnd, fanSpeedEnd });

			//Set fan points to polyline
			polyline_Fan_Lines_Gpu().Points(fanPoints);

			//Set result
			//AVDebugWriteLine("Updated gpu fan graph.");
		}
		catch (...) {}
	}

	void MainPage::UpdateFanGraphProfile()
	{
		try
		{
			//Speed vertical Y
			//Temperature horizontal X
			PointCollection fanPoints;

			//Get minimum and maximum
			int fanSpeedMinimum = slider_Fan_Speed_0().Minimum();
			int fanSpeedMaximum = slider_Fan_Speed_0().Maximum();

			//Get graph size
			int graphWidth = 500;
			int graphHeight = 100;

			//Add fan points
			float fanSpeedStart = fanSpeedMaximum - slider_Fan_Speed_0().Value();
			float fanTempStart = 0;
			fanPoints.Append(Point{ fanTempStart, fanSpeedStart });

			float fanSpeed0 = fanSpeedMaximum - slider_Fan_Speed_0().Value();
			float fanTemp0 = slider_Fan_Temp_0().Value() / 100 * graphWidth;
			fanPoints.Append(Point{ fanTemp0, fanSpeed0 });

			float fanSpeed1 = fanSpeedMaximum - slider_Fan_Speed_1().Value();
			float fanTemp1 = slider_Fan_Temp_1().Value() / 100 * graphWidth;
			fanPoints.Append(Point{ fanTemp1, fanSpeed1 });

			float fanSpeed2 = fanSpeedMaximum - slider_Fan_Speed_2().Value();
			float fanTemp2 = slider_Fan_Temp_2().Value() / 100 * graphWidth;
			fanPoints.Append(Point{ fanTemp2, fanSpeed2 });

			float fanSpeed3 = fanSpeedMaximum - slider_Fan_Speed_3().Value();
			float fanTemp3 = slider_Fan_Temp_3().Value() / 100 * graphWidth;
			fanPoints.Append(Point{ fanTemp3, fanSpeed3 });

			float fanSpeed4 = fanSpeedMaximum - slider_Fan_Speed_4().Value();
			float fanTemp4 = slider_Fan_Temp_4().Value() / 100 * graphWidth;
			fanPoints.Append(Point{ fanTemp4, fanSpeed4 });

			float fanSpeedEnd = fanSpeedMaximum - slider_Fan_Speed_4().Value();
			float fanTempEnd = graphWidth;
			fanPoints.Append(Point{ fanTempEnd, fanSpeedEnd });

			//Set fan points to polyline
			polyline_Fan_Lines_Profile().Points(fanPoints);

			//Create fan point ellipses
			grid_Fan_Dots().Children().Clear();
			UINT fanPointsSize = fanPoints.Size();
			for (UINT i = 0; i < fanPointsSize; i++)
			{
				if (i == 0 || i == fanPointsSize - 1) { continue; }
				Point fanPoint = fanPoints.GetAt(i);
				winrt::Windows::UI::Xaml::Shapes::Ellipse ellipse = {};
				ellipse.Fill(SolidColorBrush(Windows::UI::Colors::White()));
				ellipse.Width(8);
				ellipse.Height(8);
				ellipse.Margin(Thickness(fanPoint.X + 2, fanPoint.Y + 2, 0, 0));
				ellipse.HorizontalAlignment(HorizontalAlignment::Left);
				ellipse.VerticalAlignment(VerticalAlignment::Top);
				grid_Fan_Dots().Children().Append(ellipse);
			}

			//Set result
			//AVDebugWriteLine("Updated profile fan graph.");
		}
		catch (...) {}
	}
}