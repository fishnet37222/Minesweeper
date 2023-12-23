// Copyright (c) 2023 David A. Frischknecht
//
// SPDX-License-Identifier: Apache-2.0

#include "pch.h"
#include "MainWindow.h"
#include "Settings.h"

enum class MenuId
{
	ID_GAME_NEW = wxID_HIGHEST + 1,
	ID_GAME_BEGINNER,
	ID_GAME_INTERMEDIATE,
	ID_GAME_EXPERT,
	ID_GAME_CUSTOM,
	ID_GAME_BEST_TIMES,
	ID_HELP_HOW_TO_PLAY,
	ID_HELP_ABOUT,
};

MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, L"Minesweeper", wxDefaultPosition, wxDefaultSize,
	wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{
	this->InitUi();
}

void MainWindow::InitUi()
{
	this->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_FRAMEBK));
	this->SetIcons(wxIconBundle("APP_ICON", nullptr));

	using enum MenuId;
	this->menuBar = new wxMenuBar();
	auto* mnuGame = new wxMenu();
	mnuGame->Append(static_cast<int>(ID_GAME_NEW), L"&New\tF2");
	mnuGame->AppendSeparator();
	mnuGame->AppendCheckItem(static_cast<int>(ID_GAME_BEGINNER), L"&Beginner");
	mnuGame->AppendCheckItem(static_cast<int>(ID_GAME_INTERMEDIATE), L"&Intermediate");
	mnuGame->AppendCheckItem(static_cast<int>(ID_GAME_EXPERT), L"&Expert");
	mnuGame->AppendCheckItem(static_cast<int>(ID_GAME_CUSTOM), L"&Custom...");
	mnuGame->AppendSeparator();
	mnuGame->Append(static_cast<int>(ID_GAME_BEST_TIMES), L"Best &Times...");
	this->menuBar->Append(mnuGame, L"&Game");
	auto* mnuHelp = new wxMenu();
	mnuHelp->Append(static_cast<int>(ID_HELP_HOW_TO_PLAY), L"How to &Play...");
	mnuHelp->AppendSeparator();
	mnuHelp->Append(static_cast<int>(ID_HELP_ABOUT), L"&About...");
	this->menuBar->Append(mnuHelp, L"&Help");
	this->menuBar->Bind(wxEVT_MENU, &MainWindow::MenuBar_OnItemSelect, this);
	this->SetMenuBar(this->menuBar);

	auto* szrMainOuter = new wxBoxSizer(wxHORIZONTAL);
	szrMainOuter->AddSpacer(12);
	auto* szrMainInner = new wxBoxSizer(wxVERTICAL);
	szrMainInner->AddSpacer(5);
	szrMainInner->AddSpacer(12);
	szrMainOuter->Add(szrMainInner, wxSizerFlags(1).Expand());
	szrMainOuter->AddSpacer(12);
	this->SetSizerAndFit(szrMainOuter);

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

void MainWindow::MenuBar_OnItemSelect(wxCommandEvent& event)
{
}
