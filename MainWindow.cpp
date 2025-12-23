// Copyright (c) 2025 David A. Frischknecht
//
// SPDX-License-Identifier: Apache-2.0

#include "MainWindow.h"

#ifdef __linux__
#include "bitmaps/bomb-16.xpm"
#include "bitmaps/bomb-32.xpm"
#include "bitmaps/bomb-64.xpm"
#include "bitmaps/bomb-128.xpm"
#include "bitmaps/bomb-256.xpm"
#endif

enum : uint16_t
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

MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Minesweeper", wxDefaultPosition, wxDefaultSize,
	wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{
	wxFrame::SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_FRAMEBK));

#ifdef _WINDOWS
	const wxIconBundle icons("APP_ICON", nullptr);
#elif defined(__linux__)
	wxIconBundle icons;
	icons.AddIcon(wxIcon(bomb_16_xpm));
	icons.AddIcon(wxIcon(bomb_32_xpm));
	icons.AddIcon(wxIcon(bomb_64_xpm));
	icons.AddIcon(wxIcon(bomb_128_xpm));
	icons.AddIcon(wxIcon(bomb_256_xpm));
#endif

	wxFrame::SetIcons(icons);

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
	mnuHelp->Append(ID_HELP_HOW_TO_PLAY, "&How to Play");
	mnuHelp->AppendSeparator();
	mnuHelp->Append(ID_HELP_ABOUT, "&About Minesweeper");
	m_menuBar->Append(mnuHelp, "&Help");
	wxFrame::SetMenuBar(m_menuBar);
	m_menuBar->Bind(wxEVT_MENU, &MainWindow::MenuBar_OnItemSelect, this);

	CenterOnScreen();
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
