// Copyright (c) 2024 David A. Frischknecht
//
// SPDX-License-Identifier: Apache-2.0

#pragma once
#include <wx/wx.h>
#include <vector>
#include <random>

class MineField final : public wxControl
{
public:
	explicit MineField(wxWindow* parent);

private:
	struct MineFieldCell
	{
		bool mine;
		bool flagged;
		bool exposed;
		bool clicked;
		uint8_t adjacentMineCount;
	};
	std::vector<std::vector<MineFieldCell>> m_field{};
	wxSize m_gridSize{ 9, 9 };
	wxSize m_cellSize{ 25, 25 };
	uint8_t m_mineCount{ 10 };
	std::mt19937 m_rng{ std::random_device()() };
	std::uniform_int_distribution<> m_distX{};
	std::uniform_int_distribution<> m_distY{};

	void MineField_OnPaint(wxPaintEvent& event);
	void MineField_OnLeftDown(wxMouseEvent& event);
	void MineField_OnLeftUp(wxMouseEvent& event);
	void MineField_OnRightUp(wxMouseEvent& event);
	void MineField_OnLeftDoubleClick(wxMouseEvent& event);
	void InitializeField();
	[[nodiscard]] wxSize DoGetBestClientSize() const override;
	void ExposeAdjacentCells(wxPoint cellLocation);
};

wxDECLARE_EVENT(mfEVT_LEFT_DOWN, wxCommandEvent);
wxDECLARE_EVENT(mfEVT_LEFT_UP, wxCommandEvent);
wxDECLARE_EVENT(mfEVT_CELL_FLAGGED, wxCommandEvent);
