// Copyright (c) 2026 David A. Frischknecht
//
// SPDX-License-Identifier: Apache-2.0

#pragma once
#include "MineField.h"
#include "SevenSegmentDisplay.h"
#include <wx/wx.h>

enum GameDifficulty : uint8_t
{
	BEGINNER,
	INTERMEDIATE,
	EXPERT,
	CUSTOM
};

class MainWindow final : public wxFrame
{
public:
	MainWindow();

private:
	wxMenuBar* m_menuBar{};
	wxBitmapButton* m_btnNewGame{};
	SevenSegmentDisplay* m_ssdUnflaggedMineCount{};
	SevenSegmentDisplay* m_ssdElapsedSeconds{};
	MineField* m_mineField{};
	wxTimer m_timer{};
	GameDifficulty m_difficulty{ BEGINNER };
	wxSize m_customFieldSize{ 16, 16 };
	int m_customMineCount = 40;
	std::string m_difficultyName{};

	void MainWindow_OnClose(wxCloseEvent& event);
	void MenuBar_OnItemSelect(wxCommandEvent& event);
	void MineField_OnLeftDown(wxMouseEvent& event);
	void MineField_OnLeftUp(wxMouseEvent& event);
	void MineField_OnCellFlagToggled(wxCommandEvent& event);
	void MineField_OnFirstCellClicked(wxCommandEvent& event);
	void MineField_OnGameOver(wxCommandEvent& event);
	void StartNewGame();
	void BtnNewGame_OnClick(wxCommandEvent& event);
	void Timer_OnTick(wxTimerEvent& event);
};
