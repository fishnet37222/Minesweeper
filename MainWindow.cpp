// Copyright (c) 2026 David A. Frischknecht
//
// SPDX-License-Identifier: Apache-2.0

#include "AboutDialog.h"
#include "MainWindow.h"
#include <wx/config.h>

#ifdef __linux__
#include "bitmaps/bomb-128.xpm"
#include "bitmaps/bomb-16.xpm"
#include "bitmaps/bomb-256.xpm"
#include "bitmaps/bomb-32.xpm"
#include "bitmaps/bomb-64.xpm"
#endif

#include "bitmaps/smile-1.xpm"
#include "bitmaps/smile-2.xpm"
#include "bitmaps/smile-3.xpm"
#include "bitmaps/smile-4.xpm"

enum : uint16_t
{
	ID_GAME_NEW = wxID_HIGHEST + 1,
	ID_GAME_BEGINNER,
	ID_GAME_INTERMEDIATE,
	ID_GAME_EXPERT,
	ID_GAME_CUSTOM,
	ID_GAME_BEST_TIMES,
	ID_GAME_EXIT,
	ID_HELP_ABOUT
};

MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Minesweeper", wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{
	wxFrame::SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_FRAMEBK));

	wxIconBundle icons;

#ifdef _WINDOWS
	icons = wxIconBundle("APP_ICON", nullptr);
#elif defined(__linux__)
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
	mnuHelp->Append(ID_HELP_ABOUT, "&About Minesweeper");
	m_menuBar->Append(mnuHelp, "&Help");
	wxFrame::SetMenuBar(m_menuBar);
	m_menuBar->Bind(wxEVT_MENU, &MainWindow::MenuBar_OnItemSelect, this);

	auto* szrMainOuter = new wxBoxSizer(wxHORIZONTAL);
	szrMainOuter->AddSpacer(10);
	auto* szrMainInner = new wxBoxSizer(wxVERTICAL);
	szrMainInner->AddSpacer(5);
	auto* szrTop = new wxBoxSizer(wxHORIZONTAL);
	m_ssdUnflaggedMineCount = new SevenSegmentDisplay(this);
	szrTop->Add(m_ssdUnflaggedMineCount, wxSizerFlags(0).CenterVertical());
	szrTop->AddStretchSpacer(1);
	szrTop->AddSpacer(5);
	m_btnNewGame = new wxBitmapButton(this, wxID_ANY, wxBitmap(smile_1_xpm));
	szrTop->Add(m_btnNewGame, wxSizerFlags(0).CenterVertical());
	szrTop->AddSpacer(5);
	szrTop->AddStretchSpacer(1);
	m_ssdElapsedSeconds = new SevenSegmentDisplay(this);
	szrTop->Add(m_ssdElapsedSeconds, wxSizerFlags(0).CenterVertical());
	szrMainInner->Add(szrTop, wxSizerFlags(0).Expand());
	szrMainInner->AddSpacer(5);
	m_mineField = new MineField(this);
	m_mineField->Bind(wxEVT_LEFT_DOWN, &MainWindow::MineField_OnLeftDown, this);
	m_mineField->Bind(wxEVT_LEFT_UP, &MainWindow::MineField_OnLeftUp, this);
	m_mineField->Bind(MINEFIELD_CELL_FLAG_TOGGLED, &MainWindow::MineField_OnCellFlagToggled, this);
	m_mineField->Bind(MINEFIELD_FIRST_CELL_CLICKED, &MainWindow::MineField_OnFirstCellClicked, this);
	m_mineField->Bind(MINEFIELD_GAME_OVER, &MainWindow::MineField_OnGameOver, this);
	szrMainInner->Add(m_mineField, wxSizerFlags(1).CenterHorizontal());
	szrMainInner->AddSpacer(10);
	szrMainOuter->Add(szrMainInner, wxSizerFlags(1).Expand());
	szrMainOuter->AddSpacer(10);
	SetSizerAndFit(szrMainOuter);

	const auto savedPositionX = static_cast<int>(wxConfig::Get()->ReadLong("MainWindowPositionX", -1));
	// ReSharper disable once CppTooWideScopeInitStatement
	const auto savedPositionY = static_cast<int>(wxConfig::Get()->ReadLong("MainWindowPositionY", -1));

	if (savedPositionX != -1 && savedPositionY != -1)
	{
		SetPosition(wxPoint(savedPositionX, savedPositionY));
	}
	else
	{
		CenterOnScreen();
	}

	Bind(wxEVT_CLOSE_WINDOW, &MainWindow::MainWindow_OnClose, this);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void MainWindow::MainWindow_OnClose(wxCloseEvent& evt)
{
	const auto position = GetPosition();
	wxConfig::Get()->Write("MainWindowPositionX", position.x);
	wxConfig::Get()->Write("MainWindowPositionY", position.y);
	wxConfig::Get()->Flush();
	evt.Skip();
}

// ReSharper disable once CppParameterMayBeConstPtrOrRef
void MainWindow::MenuBar_OnItemSelect([[maybe_unused]] wxCommandEvent& event)
{
	switch (event.GetId())
	{
		case ID_GAME_EXIT:
		{
			Close();
			break;
		}

		case ID_HELP_ABOUT:
		{
			AboutDialog dlg(this);
			dlg.ShowModal();

			break;
		}

		default:
			break;
	}

}

// ReSharper disable once CppMemberFunctionMayBeConst
void MainWindow::MineField_OnLeftDown(wxMouseEvent& event)
{
	if (m_mineField->IsGameInProgress())
	{
		m_btnNewGame->SetBitmap(wxBitmap(smile_4_xpm));
	}

	event.Skip();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void MainWindow::MineField_OnLeftUp(wxMouseEvent& event)
{
	if (m_mineField->IsGameInProgress())
	{
		m_btnNewGame->SetBitmap(wxBitmap(smile_1_xpm));
	}

	event.Skip();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void MainWindow::MineField_OnCellFlagToggled([[maybe_unused]] wxCommandEvent& event)
{
	m_ssdUnflaggedMineCount->SetValue(m_mineField->GetMineCount() - m_mineField->GetFlagCount());
}
