#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlxVariables.h"

namespace winrt::AmdDriverTool::implementation
{
	void MainPage::ValidateFanSettings()
	{
		//Fix check valid values and adjust
	}

	void MainPage::UpdateFanGraph()
	{
		//Speed vertical Y
		//Temperature horizontal X
		PointCollection fanPoints;

		//Get minimum and maximum
		int fanSpeedMinimum = slider_Fan_Speed_0().Minimum();
		int fanSpeedMaximum = slider_Fan_Speed_0().Maximum();

		//Add fan points
		float fanSpeedStart = fanSpeedMaximum - slider_Fan_Speed_0().Value();
		float fanTempStart = 0;
		fanPoints.Append(Point{ fanTempStart, fanSpeedStart });

		float fanSpeed0 = fanSpeedMaximum - slider_Fan_Speed_0().Value();
		float fanTemp0 = slider_Fan_Temp_0().Value();
		fanPoints.Append(Point{ fanTemp0, fanSpeed0 });

		float fanSpeed1 = fanSpeedMaximum - slider_Fan_Speed_1().Value();
		float fanTemp1 = 100 + slider_Fan_Temp_1().Value();
		fanPoints.Append(Point{ fanTemp1, fanSpeed1 });

		float fanSpeed2 = fanSpeedMaximum - slider_Fan_Speed_2().Value();
		float fanTemp2 = 200 + slider_Fan_Temp_2().Value();
		fanPoints.Append(Point{ fanTemp2, fanSpeed2 });

		float fanSpeed3 = fanSpeedMaximum - slider_Fan_Speed_3().Value();
		float fanTemp3 = 300 + slider_Fan_Temp_3().Value();
		fanPoints.Append(Point{ fanTemp3, fanSpeed3 });

		float fanSpeed4 = fanSpeedMaximum - slider_Fan_Speed_4().Value();
		float fanTemp4 = 400 + slider_Fan_Temp_4().Value();
		fanPoints.Append(Point{ fanTemp4, fanSpeed4 });

		float fanSpeedEnd = fanSpeedMaximum - slider_Fan_Speed_4().Value();
		float fanTempEnd = 500;
		fanPoints.Append(Point{ fanTempEnd, fanSpeedEnd });

		//Create fan point ellipses
		grid_Fan_Dots().Children().Clear();
		auto fanPointsSize = fanPoints.Size();
		for (int i = 0; i < fanPointsSize; i++)
		{
			if (i == 0 || i == fanPointsSize - 1) { continue; }
			Point fanPoint = fanPoints.GetAt(i);
			winrt::Windows::UI::Xaml::Shapes::Ellipse ellipse = {};
			ellipse.Fill(SolidColorBrush(Windows::UI::Colors::White()));
			ellipse.Width(8);
			ellipse.Height(8);
			ellipse.Margin(Thickness(fanPoint.X, 0, 0, 102 - fanPoint.Y));
			ellipse.HorizontalAlignment(HorizontalAlignment::Left);
			ellipse.VerticalAlignment(VerticalAlignment::Bottom);
			grid_Fan_Dots().Children().Append(ellipse);
		}

		//Set fan points to polyline
		polyline_Fan_Lines().Points(fanPoints);

		//Set result
		AVDebugWriteLine("ADLX updated fan graph.");
	}
}