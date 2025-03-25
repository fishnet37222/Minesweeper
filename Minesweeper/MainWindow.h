// Copyright (c) 2025 David A. Frischknecht
//
// SPDX-License-Identifier: Apache-2.0

#pragma once
#include <wx/wx.h>
#include <array>

class MainWindow final : public wxFrame
{
public:
	MainWindow();

private:
	wxMenuBar* m_menuBar{};
	uint16_t m_difficultyLevel{};
	wxSize m_customMineFieldSize{};
	int m_customMineCount{};
	std::array<uint16_t, 4> m_difficultyMenuIds;

	void MainWindow_OnClose(wxCloseEvent& event);
	void MenuBar_OnItemSelect(wxCommandEvent& event);
};
