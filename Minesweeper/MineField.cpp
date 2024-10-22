// Copyright (c) 2024 David A. Frischknecht
//
// SPDX-License-Identifier: Apache-2.0

#include "pch.h"
#include "MineField.h"
#include <wx/dcbuffer.h>
#include <wx/graphics.h>
#include <stack>

#include "Bitmaps/flag-small.xpm"
#include "Bitmaps/explosion-small.xpm"

wxDEFINE_EVENT(mfEVT_LEFT_DOWN, wxCommandEvent);
wxDEFINE_EVENT(mfEVT_LEFT_UP, wxCommandEvent);
wxDEFINE_EVENT(mfEVT_CELL_FLAGGED, wxCommandEvent);

MineField::MineField(wxWindow* parent)
{
	wxControl::SetBackgroundStyle(wxBG_STYLE_PAINT);
	Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE | wxBORDER_NONE);
	InitializeField();
	Bind(wxEVT_PAINT, &MineField::MineField_OnPaint, this);
	Bind(wxEVT_LEFT_DOWN, &MineField::MineField_OnLeftDown, this);
	Bind(wxEVT_LEFT_UP, &MineField::MineField_OnLeftUp, this);
	Bind(wxEVT_RIGHT_UP, &MineField::MineField_OnRightUp, this);
	wxControl::SetBackgroundColour(wxTheColourDatabase->Find("LIGHT GREY"));
	wxControl::SetForegroundColour(wxTheColourDatabase->Find("BLACK"));
}

void MineField::MineField_OnPaint(wxPaintEvent& event)
{
	const wxAutoBufferedPaintDC dc(this);
	auto* gc = wxGraphicsContext::Create(dc);

	gc->SetBrush(GetBackgroundColour());
	gc->SetPen(GetBackgroundColour());

	const auto clientSize = GetClientSize();

	gc->SetFont(GetFont().Bold().Larger(), GetForegroundColour());

	gc->DrawRectangle(0, 0, clientSize.GetWidth(), clientSize.GetHeight());

	const auto highlightColor = GetBackgroundColour().ChangeLightness(150);
	const auto shadowColor = GetBackgroundColour().ChangeLightness(50);

	for (auto gridY = 0; gridY < m_gridSize.GetHeight(); gridY++)
	{
		const auto cellOriginY = m_cellSize.GetHeight() * gridY;
		for (auto gridX = 0; gridX < m_gridSize.GetWidth(); gridX++)
		{
			const auto cellOriginX = m_cellSize.GetWidth() * gridX;
			const auto cell = m_field[gridY][gridX];

			if (!cell.exposed)
			{
				for (auto i = 0; i < 3; i++)
				{
					gc->SetPen(highlightColor);
					gc->StrokeLine(cellOriginX + i, cellOriginY + i, cellOriginX + m_cellSize.GetWidth() - i, cellOriginY + i);
					gc->StrokeLine(cellOriginX + i, cellOriginY + i, cellOriginX + i, cellOriginY + m_cellSize.GetHeight() - i);
					gc->SetPen(shadowColor);
					gc->StrokeLine(cellOriginX + m_cellSize.GetWidth() - i, cellOriginY + m_cellSize.GetHeight() - i,
						cellOriginX + i, cellOriginY + m_cellSize.GetHeight() - i);
					gc->StrokeLine(cellOriginX + m_cellSize.GetWidth() - i, cellOriginY + m_cellSize.GetHeight() - i,
						cellOriginX + m_cellSize.GetWidth() - i, cellOriginY + i);
				}

				if (cell.flagged)
				{
					gc->DrawBitmap(wxBitmap(flag_small), cellOriginX + 2, cellOriginY + 2, m_cellSize.GetWidth() - 4, m_cellSize.GetHeight() - 4);
				}
			}
			else
			{
				gc->SetPen(GetForegroundColour());

				gc->DrawRectangle(cellOriginX, cellOriginY, m_cellSize.GetWidth(), m_cellSize.GetHeight());

				if (cell.adjacentMineCount > 0 && !cell.mine)
				{
					const auto text = std::to_string(cell.adjacentMineCount);

					double textWidth, textHeight;
					gc->GetTextExtent(text, &textWidth, &textHeight);
					const auto textOriginX = cellOriginX + static_cast<double>(m_cellSize.GetWidth()) / 2 - textWidth / 2;
					const auto textOriginY = cellOriginY + static_cast<double>(m_cellSize.GetHeight()) / 2 - textHeight / 2;

					gc->DrawText(text, textOriginX, textOriginY);
				}

				if (cell.mine)
				{
					gc->DrawBitmap(wxBitmap(explosion_small), cellOriginX + 1, cellOriginY + 1, m_cellSize.GetWidth() - 2, m_cellSize.GetHeight() - 2);
				}
			}
		}
	}

	delete gc;
}

void MineField::MineField_OnLeftDown([[maybe_unused]] wxMouseEvent& event)
{
	CaptureMouse();
	wxCommandEvent evt(mfEVT_LEFT_DOWN, GetId());
	evt.SetEventObject(this);
	ProcessWindowEvent(evt);
}

// ReSharper disable once CppParameterMayBeConstPtrOrRef
void MineField::MineField_OnLeftUp(wxMouseEvent& event)
{
	if (HasCapture()) ReleaseMouse();

	wxCommandEvent evt(mfEVT_LEFT_UP, GetId());
	evt.SetEventObject(this);
	ProcessWindowEvent(evt);

	const auto mousePosition = event.GetLogicalPosition(wxWindowDC(this));
	const auto gridX = mousePosition.x / m_cellSize.GetWidth();
	const auto gridY = mousePosition.y / m_cellSize.GetHeight();

	if (gridX < 0 || gridX >= m_gridSize.GetWidth() || gridY < 0 || gridY > m_gridSize.GetHeight()) return;

	ExposeAdjacentCells({ gridX, gridY });

	Refresh();
}

void MineField::InitializeField()
{
	const std::vector row{ static_cast<size_t>(m_gridSize.GetWidth()), MineFieldCell{} };
	m_field = std::vector{ static_cast<size_t>(m_gridSize.GetHeight()), row };

	m_distX = std::uniform_int_distribution<>{ 0, m_gridSize.GetWidth() - 1 };
	m_distY = std::uniform_int_distribution<>{ 0, m_gridSize.GetHeight() - 1 };

	for (auto i = 0; i < m_mineCount; i++)
	{
		int x, y;

		do
		{
			x = m_distX(m_rng);
			y = m_distY(m_rng);

		} while (m_field[y][x].mine);

		m_field[y][x].mine = true;

		for (auto tmpY = y - 1; tmpY <= y + 1; tmpY++)
		{
			if (tmpY < 0 || tmpY >= m_gridSize.GetHeight()) continue;
			for (auto tmpX = x - 1; tmpX <= x + 1; tmpX++)
			{
				if (tmpX < 0 || tmpX >= m_gridSize.GetWidth()) continue;
				if (tmpX == x && tmpY == y) continue;
				m_field[tmpY][tmpX].adjacentMineCount++;
			}
		}
	}
}

wxSize MineField::DoGetBestClientSize() const
{
	return { m_gridSize.GetWidth() * m_cellSize.GetWidth() + 1, m_gridSize.GetHeight() * m_cellSize.GetHeight() + 1 };
}

// ReSharper disable once CppParameterMayBeConstPtrOrRef
void MineField::MineField_OnRightUp(wxMouseEvent& event)
{
	const auto mousePosition = event.GetLogicalPosition(wxWindowDC(this));
	const auto gridX = mousePosition.x / m_cellSize.GetWidth();
	const auto gridY = mousePosition.y / m_cellSize.GetHeight();

	if (gridX < 0 || gridX >= m_gridSize.GetWidth() || gridY < 0 || gridY > m_gridSize.GetHeight()) return;

	auto& [mine, flagged, exposed, clicked, adjacentMineCount] = m_field[gridY][gridX];

	if (exposed) return;

	flagged = !flagged;

	Refresh();

	wxCommandEvent evt(mfEVT_CELL_FLAGGED, GetId());
	evt.SetEventObject(this);
	evt.SetClientData(&flagged);
	ProcessWindowEvent(evt);
}

void MineField::ExposeAdjacentCells(const wxPoint cellLocation)
{
	std::stack<wxPoint> cellsToExpose{};
	cellsToExpose.push(cellLocation);

	auto hitMine = false;

	while (!cellsToExpose.empty())
	{
		auto currentCell = cellsToExpose.top();
		cellsToExpose.pop();

		m_field[currentCell.y][currentCell.x].exposed = true;

		if (m_field[currentCell.y][currentCell.x].mine)
		{
			hitMine = true;
			continue;
		}

		if (m_field[currentCell.y][currentCell.x].adjacentMineCount > 0) continue;

		for (auto gridY = currentCell.y - 1; gridY <= currentCell.y + 1; gridY++)
		{
			if (gridY < 0 || gridY >= m_gridSize.GetHeight()) continue;
			for (auto gridX = currentCell.x - 1; gridX <= currentCell.x + 1; gridX++)
			{
				if (gridX < 0 || gridX >= m_gridSize.GetWidth()) continue;
				if (gridX == currentCell.x && gridY == currentCell.y) continue;
				if (m_field[gridY][gridX].exposed || m_field[gridY][gridX].flagged || m_field[gridY][gridX].mine) continue;

				cellsToExpose.emplace(gridX, gridY);
			}
		}
	}

	if (!hitMine) return;
}
