// Copyright (c) 2026 David A. Frischknecht
//
// SPDX-License-Identifier: Apache-2.0

#pragma once
#include <random>
#include <vector>
#include <wx/wx.h>

wxDECLARE_EVENT(MINEFIELD_GAME_OVER, wxCommandEvent);
wxDECLARE_EVENT(MINEFIELD_CELL_FLAG_TOGGLED, wxCommandEvent);
wxDECLARE_EVENT(MINEFIELD_FIRST_CELL_CLICKED, wxCommandEvent);

enum GameOverReason : uint8_t
{
	WIN,
	LOSS
};

class MineField final : public wxControl
{
public:
	explicit MineField(wxWindow* parent);
	[[nodiscard]] wxSize GetCellSize() const { return m_cellSize; }
	void SetCellSize(wxSize cellSize);
	[[nodiscard]] wxSize GetFieldSize() const { return m_fieldSize; }
	[[nodiscard]] int GetMineCount() const { return m_mineCount; }
	[[nodiscard]] int GetFlagCount() const { return m_flagCount; }
	[[nodiscard]] bool IsGameInProgress() const { return m_gameInProgress; }
	void Reset(wxSize newFieldSize = { -1, -1 }, int newMineCount = -1);

private:
	class Cell
	{
	public:
		bool m_isMine{ false };
		bool m_isFlagged{ false };
		bool m_isRevealed{ false };
		bool m_wasClicked{ false };
		int m_adjacentMineCount{ 0 };
	};

	inline static std::mt19937 m_rng{ std::random_device{}() };

	wxSize m_cellSize{ 25,25 };
	wxSize m_fieldSize{ 9,9 };
	int m_mineCount{ 10 };
	int m_flagCount{ 0 };
	std::uniform_int_distribution<> m_distX{ 0, m_fieldSize.GetWidth() - 1 };
	std::uniform_int_distribution<> m_distY{ 0, m_fieldSize.GetHeight() - 1 };
	std::vector<std::vector<std::unique_ptr<Cell>>> m_cells{};
	std::vector<wxPoint> m_mineLocations{};
	std::vector<wxPoint> m_flagLocations{};
	bool m_mouseLeftDown{ false };
	wxPoint m_hoveredCellLocation{ -1,-1 };
	bool m_gameInProgress{ true };
	bool m_firstCellClicked{ false };

	void MineField_OnPaint(wxPaintEvent& event);
	void MineField_OnRightUp(wxMouseEvent& event);
	void MineField_OnLeftDown(wxMouseEvent& event);
	void MineField_OnLeftUp(wxMouseEvent& event);
	void MineField_OnMouseMove(wxMouseEvent& event);
	void MineField_OnLeftDoubleClick(wxMouseEvent& event);
	[[nodiscard]] wxSize DoGetBestClientSize() const override;
	[[nodiscard]] wxPoint ClientCoordsToFieldCoords(wxPoint clientCoords) const;
	void InitializeField();
	void RevealCells(wxPoint cellCoords);
	void SendGameOverEvent(GameOverReason reason);
	void SendCellFlagToggledEvent();
	void SendFirstCellClickedEvent();
	void RevealMines();
};
