// Copyright (c) 2026 David A. Frischknecht
//
// SPDX-License-Identifier: Apache-2.0

#include "pch.h"
#include "App.h"
#include <fstream>
#include "MainWindow.h"
#include <wx/stdpaths.h>

wxIMPLEMENT_APP(App);

bool App::OnInit()
{
	if (!wxApp::OnInit())
	{
		return false;
	}

	SetVendorName("FishNetSoft");
	SetAppName("Minesweeper");

	wxStandardPaths::Get().UseAppInfo(wxStandardPaths::AppInfo_VendorName | wxStandardPaths::AppInfo_AppName);

	m_bestTimesFilePath = wxStandardPaths::Get().GetUserDataDir().ToStdString() + "/best_times.json";

	auto* mainWindow = new MainWindow();
	SetTopWindow(mainWindow);
	mainWindow->Show();

	return true;
}

int App::OnExit()
{
	if (!std::filesystem::exists(m_bestTimesFilePath.parent_path()))
	{
		std::filesystem::create_directories(m_bestTimesFilePath.parent_path());
	}

	std::ofstream bestTimesFile(m_bestTimesFilePath);
	bestTimesFile << m_bestTimes.toStyledString();
	bestTimesFile.close();

	return wxApp::OnExit();
}

void App::SetBestTimes(const Json::Value& bestTimes)
{
	m_bestTimes = bestTimes;
}
