// Copyright (c) 2026 David A. Frischknecht
//
// SPDX-License-Identifier: Apache-2.0

#include "App.h"
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

#ifdef __linux__
	wxStandardPaths::Get().SetFileLayout(wxStandardPathsBase::FileLayout_XDG);
#endif

	auto* mainWindow = new MainWindow();
	SetTopWindow(mainWindow);
	mainWindow->Show();

	return true;
}
