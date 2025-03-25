// Copyright (c) 2025 David A. Frischknecht
//
// SPDX-License-Identifier: Apache-2.0

#include "pch.h"
#include "MainWindow.h"
#include "App.h"
#include <wx/config.h>

enum MenuId : uint16_t
{
	ID_GAME_NEW = wxID_HIGHEST + 1,
	ID_GAME_BEGINNER,
	ID_GAME_INTERMEDIATE,
	ID_GAME_EXPERT,
	ID_GAME_CUSTOM,
	ID_GAME_BEST_TIMES,
	ID_GAME_EXIT,
	ID_HELP_HOW_TO_PLAY,
	ID_HELP_ABOUT
};

MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, wxGetApp().GetAppName(), wxDefaultPosition, wxDefaultSize,
	wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{
	wxFrame::SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_FRAMEBK));

	wxFrame::SetIcons(wxIconBundle("APP_ICON", nullptr));

	m_menuBar = new wxMenuBar();

	auto* mnuGame = new wxMenu();
	mnuGame->Append(ID_GAME_NEW, "&New\tF2");
	mnuGame->AppendSeparator();
	mnuGame->AppendCheckItem(ID_GAME_BEGINNER, "&Beginner");
	mnuGame->AppendCheckItem(ID_GAME_INTERMEDIATE, "&Intermediate");
	mnuGame->AppendCheckItem(ID_GAME_EXPERT, "&Expert");
	mnuGame->AppendCheckItem(ID_GAME_CUSTOM, "&Custom...");
	mnuGame->AppendSeparator();
	mnuGame->Append(ID_GAME_BEST_TIMES, "Best &Times...");
	mnuGame->AppendSeparator();
	mnuGame->Append(ID_GAME_EXIT, "E&xit");
	m_menuBar->Append(mnuGame, "&Game");

	auto* mnuHelp = new wxMenu();
	mnuHelp->Append(ID_HELP_HOW_TO_PLAY, "How to &Play...");
	mnuHelp->AppendSeparator();
	mnuHelp->Append(ID_HELP_ABOUT, "About Minesweeper...");
	m_menuBar->Append(mnuHelp, "&Help");

	m_menuBar->Bind(wxEVT_MENU, &MainWindow::MenuBar_OnItemSelect, this);

	wxFrame::SetMenuBar(m_menuBar);

	Bind(wxEVT_CLOSE_WINDOW, &MainWindow::MainWindow_OnClose, this);

	const auto posX = wxConfig::Get()->ReadLong("MainWindowPosX", -1);
	// ReSharper disable once CppTooWideScopeInitStatement
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

// ReSharper disable once CppParameterMayBeConstPtrOrRef
void MainWindow::MenuBar_OnItemSelect(wxCommandEvent& event)
{
	switch (event.GetId())
	{
		case ID_GAME_EXIT:
		{
			Close();

			break;
		}

		default:
			break;
	}
}
