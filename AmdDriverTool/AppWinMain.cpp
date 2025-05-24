#pragma once
#include "pch.h"
#include "AppVariables.h"

int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	AppVariables::App.Initialize(hInstance);
	return 0;
}