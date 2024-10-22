// Copyright (c) 2024 David A. Frischknecht
//
// SPDX-License-Identifier: Apache-2.0

#pragma once
#include <wx/wx.h>
#include "SevenSegmentDisplay.h"
#include "MineField.h"

class MainWindow final : public wxFrame
{
public:
	MainWindow();

private:
	wxMenuBar* m_menuBar{};
	wxBitmapButton* m_btnNewGame{};
	SevenSegmentDisplay* m_ssdMinesLeft{};
	SevenSegmentDisplay* m_ssdElapsedTime{};
	MineField* m_mineField{};

	void MineField_OnLeftDown(wxCommandEvent& event);
	void MineField_OnLeftUp(wxCommandEvent& event);
};
