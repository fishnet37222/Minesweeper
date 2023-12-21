// Copyright (c) 2023 David A. Frischknecht
//
// SPDX-License-Identifier: Apache-2.0

#include "pch.h"
#include "MainWindow.h"
#include "Settings.h"

MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Minesweeper", wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{
	this->InitUi();
}

void MainWindow::InitUi()
{
	this->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_FRAMEBK));
	this->SetIcons(wxIconBundle("APP_ICON", nullptr));

	this->Fit();
	auto position = Settings::GetMainWindowPosition();

	if (position.x == -1)
	{
		position.x = (wxSystemSettings::GetMetric(wxSYS_SCREEN_X) - this->GetSize().x) / 2;
	}

	if (position.y == -1)
	{
		position.y = (wxSystemSettings::GetMetric(wxSYS_SCREEN_Y) - this->GetSize().y) / 2;
	}

	this->SetPosition(position);
}
