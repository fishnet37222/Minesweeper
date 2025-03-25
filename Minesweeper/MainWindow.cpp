// Copyright (c) 2025 David A. Frischknecht
//
// SPDX-License-Identifier: Apache-2.0

#include "pch.h"
#include "MainWindow.h"
#include "App.h"
#include <wx/config.h>

MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, wxGetApp().GetAppName(), wxDefaultPosition, wxDefaultSize,
	wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{
	wxFrame::SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_FRAMEBK));

	wxFrame::SetIcons(wxIconBundle("APP_ICON", nullptr));

	Bind(wxEVT_CLOSE_WINDOW, &MainWindow::MainWindow_OnClose, this);

	const auto posX = wxConfig::Get()->ReadLong("MainWindowPosX", -1);
	const auto posY = wxConfig::Get()->ReadLong("MainWindowPosY", -1);

	if (posX == -1 && posY == -1)
	{
		CenterOnScreen();
	}
	else
	{
		SetPosition({ posX, posY });
	}
}

// ReSharper disable once CppMemberFunctionMayBeConst
void MainWindow::MainWindow_OnClose(wxCloseEvent& event)
{
	wxConfig::Get()->Write("MainWindowPosX", GetPosition().x);
	wxConfig::Get()->Write("MainWindowPosY", GetPosition().y);

	event.Skip();
}
