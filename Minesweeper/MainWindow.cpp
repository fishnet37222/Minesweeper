// Copyright (c) 2024 David A. Frischknecht
//
// SPDX-License-Identifier: Apache-2.0

#include "pch.h"
#include "MainWindow.h"

#include "Bitmaps/smile-1.xpm"
#include "Bitmaps/smile-2.xpm"
#include "Bitmaps/smile-3.xpm"
#include "Bitmaps/smile-4.xpm"

MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Minesweeper", wxDefaultPosition, wxDefaultSize,
	wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{
	wxFrame::SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_FRAMEBK));
	wxFrame::SetIcons(wxIconBundle("APP_ICON", nullptr));

	m_menuBar = new wxMenuBar();

	auto* mnuGame = new wxMenu();
	m_menuBar->Append(mnuGame, "&Game");

	auto* mnuHelp = new wxMenu();
	m_menuBar->Append(mnuHelp, "&Help");

	wxFrame::SetMenuBar(m_menuBar);

	auto* szrMainOuter = new wxBoxSizer(wxHORIZONTAL);
	szrMainOuter->AddSpacer(12);

	auto* szrMainInner = new wxBoxSizer(wxVERTICAL);
	szrMainInner->AddSpacer(5);

	auto* szrTop = new wxBoxSizer(wxHORIZONTAL);

	m_ssdMinesLeft = new SevenSegmentDisplay(this);
	szrTop->Add(m_ssdMinesLeft, wxSizerFlags(0).CenterVertical());

	szrTop->AddStretchSpacer(1);
	szrTop->AddSpacer(5);

	m_btnNewGame = new wxBitmapButton(this, wxID_ANY, wxBitmapBundle::FromBitmap(wxBitmap(smile_1_xpm)));
	szrTop->Add(m_btnNewGame, wxSizerFlags(0).CenterVertical());

	szrTop->AddSpacer(5);
	szrTop->AddStretchSpacer(1);

	m_ssdElapsedTime = new SevenSegmentDisplay(this);
	szrTop->Add(m_ssdElapsedTime, wxSizerFlags(0).CenterVertical());

	szrMainInner->Add(szrTop, wxSizerFlags(0).Expand());

	szrMainInner->AddSpacer(5);

	m_mineField = new MineField(this);
	m_mineField->Bind(mfEVT_LEFT_DOWN, &MainWindow::MineField_OnLeftDown, this);
	m_mineField->Bind(mfEVT_LEFT_UP, &MainWindow::MineField_OnLeftUp, this);
	szrMainInner->Add(m_mineField, wxSizerFlags(1).Expand());

	szrMainInner->AddSpacer(12);
	szrMainOuter->Add(szrMainInner, wxSizerFlags(1).Expand());

	szrMainOuter->AddSpacer(12);
	SetSizerAndFit(szrMainOuter);

	CenterOnScreen();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void MainWindow::MineField_OnLeftDown([[maybe_unused]] wxCommandEvent& event)
{
	m_btnNewGame->SetBitmap(wxBitmapBundle::FromBitmap(wxBitmap(smile_4_xpm)));
}

// ReSharper disable once CppMemberFunctionMayBeConst
void MainWindow::MineField_OnLeftUp([[maybe_unused]] wxCommandEvent& event)
{
	m_btnNewGame->SetBitmap(wxBitmapBundle::FromBitmap(wxBitmap(smile_1_xpm)));
}
