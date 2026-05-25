// Copyright (c) 2026 David A. Frischknecht
//
// SPDX-License-Identifier: Apache-2.0

#pragma once
#include "MineField.h"
#include "SevenSegmentDisplay.h"
#include <wx/wx.h>

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

	void MainWindow_OnClose(wxCloseEvent& evt);
	void MenuBar_OnItemSelect(wxCommandEvent& event);
	void MineField_OnLeftDown(wxMouseEvent& event);
	void MineField_OnLeftUp(wxMouseEvent& event);
	void MineField_OnCellFlagToggled(wxCommandEvent& event);
	void MineField_OnFirstCellClicked(wxCommandEvent& event);
	void MineField_OnGameOver(wxCommandEvent& event);
};
